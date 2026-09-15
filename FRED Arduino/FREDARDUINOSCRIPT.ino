#include <Arduino.h>
#include <math.h>
#include <LiquidCrystal.h>


// LCD (16x2, 4-bit mode)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


// PARAMETERS
const uint16_t windowSize = 256;
const float samplingFrequency = 256.0;

// SIMULATION MODALITY
const bool simulationMode = true;

// FREQUENCY OF THE SIMULATED SIGNAL
// 2 Hz  -> Delta
// 6 Hz  -> Theta
// 10 Hz -> Alpha
// 20 Hz -> Beta
// 40 Hz -> Gamma
const float simulatedFrequency = 20.0;

// AMPLITUDE OF THE SIMULATED SIGNAL
const float simulatedAmplitude = 100.0;

// AMPLITUDE OF THE SIMULATED NOISE
const float noiseAmplitude = 10.0;

// BUFFER
// Buffer used by the Interrupt
volatile uint16_t sampleBuffer[windowSize];

// Copy of the processing used window
uint16_t processingBuffer[windowSize];

volatile uint16_t sampleIndex = 0;
volatile bool windowReady = false;

// TIMER 1
void setupTimer1() {

  noInterrupts();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 16 MHz / 64 / (976 + 1) = 256 Hz
  OCR1A = 976;

  // CTC mode
  TCCR1B |= (1 << WGM12);

  // Prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // Interrupt
  TIMSK1 |= (1 << OCIE1A);

  interrupts();
}

// INTERRUPT
ISR(TIMER1_COMPA_vect) {

  if (sampleIndex < windowSize) {
    if (simulationMode) {
      // Sample Time
      float t =
        (float)sampleIndex / samplingFrequency;

      // Sinusoidal Signal
      float signal =
        simulatedAmplitude *
        sin(2.0 * PI * simulatedFrequency * t);

      // Random Noise
      float noise =
        ((float)random(-100, 101) / 100.0)
        * noiseAmplitude;

      // Centered Signal at half ADC scale
      float value =
        512.0 + signal + noise;

      // Limits of ADC
      if (value < 0)
        value = 0;

      if (value > 1023)
        value = 1023;

      sampleBuffer[sampleIndex] =
        (uint16_t)value;

    }
    else {
      // Real EEG
      sampleBuffer[sampleIndex] =
        analogRead(A0);
    }

    sampleIndex++;
  }
  else {
    windowReady = true;
  }
}

// GOERTZEL
float goertzelPower(
  uint16_t targetFrequency,
  float mean
) {

  float omega =
    (2.0 * PI * targetFrequency)
    / windowSize;

  float coeff =
    2.0 * cos(omega);

  float q0;
  float q1 = 0.0;
  float q2 = 0.0;

  for (uint16_t i = 0; i < windowSize; i++) {
    float sample =
      (float)processingBuffer[i] - mean;

    q0 =
      coeff * q1
      - q2
      + sample;

    q2 = q1;
    q1 = q0;
  }

  return
    q1 * q1
    + q2 * q2
    - coeff * q1 * q2;
}

// AVERAGE BAND POWER
float calculateBandPower(
  uint16_t lowFrequency,
  uint16_t highFrequency,
  float mean
) {

  float totalPower = 0.0;
  uint16_t numberOfBins =
    highFrequency - lowFrequency + 1;

  for (
    uint16_t f = lowFrequency;
    f <= highFrequency;
    f++
  ) {
    totalPower +=
      goertzelPower(f, mean);
  }

  // Normalisation based on the frequency number
  return totalPower / numberOfBins;
}

// SETUP
void setup() {

  Serial.begin(115200);

  randomSeed(analogRead(A5));

  Serial.println();
  Serial.println("EEG BAND ANALYSIS");
  Serial.println("Arduino Uno R3");

  Serial.print("Sampling frequency: ");
  Serial.print(samplingFrequency);
  Serial.println(" Hz");

  Serial.print("Window size: ");
  Serial.println(windowSize);

  Serial.print("Frequency resolution: ");
  Serial.print(
    samplingFrequency / windowSize
  );
  Serial.println(" Hz");

  Serial.println();

  if (simulationMode) {
    Serial.println("MODE: SIMULATION");

    Serial.print("Simulated frequency: ");
    Serial.print(simulatedFrequency);
    Serial.println(" Hz");

    Serial.print("Signal amplitude: ");
    Serial.println(simulatedAmplitude);

    Serial.println();
  }
  else {
    Serial.println("MODE: REAL EEG - A0");
    Serial.println();
  }

  setupTimer1();
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("EEG Analysis");
  lcd.setCursor(0, 1);
  lcd.print("Init...");
}

// LOOP
void loop() {

  if (windowReady) {
    // INTERRUPTS STOP
    noInterrupts();

    // Copy of the sampled window
    for (uint16_t i = 0; i < windowSize; i++) {
      processingBuffer[i] =
        sampleBuffer[i];
    }

    // The window has been sampled
    windowReady = false;

    // Reset of idx for the next window
    sampleIndex = 0;

    interrupts();

    // AVERAGE CALCULUS
    uint32_t sum = 0;

    for (uint16_t i = 0; i < windowSize; i++) {
      sum += processingBuffer[i];
    }

    float mean =
      (float)sum / windowSize;

    // BAND CALCULUS
    float deltaPower =
      calculateBandPower(1, 4, mean);

    float thetaPower =
      calculateBandPower(4, 8, mean);

    float alphaPower =
      calculateBandPower(8, 14, mean);

    float betaPower =
      calculateBandPower(14, 30, mean);

    float gammaPower =
      calculateBandPower(30, 80, mean);

    // OUTPUT
    Serial.println();
    Serial.println("EEG BAND POWER");

    Serial.print("Delta (0.5-4 Hz): ");
    Serial.println(deltaPower);

    Serial.print("Theta (4-8 Hz):   ");
    Serial.println(thetaPower);

    Serial.print("Alpha (8-14 Hz):  ");
    Serial.println(alphaPower);

    Serial.print("Beta (14-30 Hz):  ");
    Serial.println(betaPower);

    Serial.print("Gamma (30-80 Hz): ");
    Serial.println(gammaPower);

    
    // DOMINANT BAND
    float maxPower = deltaPower;
    const char* dominantBand = "DELTA";

    if (thetaPower > maxPower) {
      maxPower = thetaPower;
      dominantBand = "THETA";
    }

    if (alphaPower > maxPower) {
      maxPower = alphaPower;
      dominantBand = "ALPHA";
    }

    if (betaPower > maxPower) {
      maxPower = betaPower;
      dominantBand = "BETA";
    }

    if (gammaPower > maxPower) {
      maxPower = gammaPower;
      dominantBand = "GAMMA";
    }


    Serial.print("Dominant band: ");
    Serial.println(dominantBand);

    // FOCUS / NOT FOCUS
    bool focused = (betaPower >= maxPower);

    if (focused) {
      Serial.println("FOCUS");
    }
    else {
      Serial.println("NOT FOCUS");
    }

    // LCD UPDATE
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Band: ");
    lcd.print(dominantBand);

    lcd.setCursor(0, 1);
    if (focused) {
      lcd.print("FOCUS");
    }
    else {
      lcd.print("NOT FOCUS");
    }
  }
}