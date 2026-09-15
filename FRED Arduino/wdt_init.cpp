#include <avr/io.h>
#include <avr/wdt.h>

uint8_t mcusr_mirror __attribute__((section(".noinit")));

void wdt_init(void) __attribute__((naked))
__attribute__((used))
__attribute__((section(".init3")));

void wdt_init(void) {
  mcusr_mirror = MCUSR;
  MCUSR = 0;
  wdt_disable();
}