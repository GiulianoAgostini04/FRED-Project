library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity focus_comparator_tb is
end entity;

architecture sim of focus_comparator_tb is

    signal clk_tb : std_logic := '0';
    signal rstas_tb : std_logic;
    signal focus_in_tb : std_logic_vector(7 downto 0);
    signal notFocus_in_tb : std_logic_vector(7 downto 0);
    signal data_valid_tb : std_logic;
    signal ledFocus_tb : std_logic;
    signal ledNotFocus_tb : std_logic;
    
begin

    clk_tb <= not clk_tb after 10 ns;

    dut: entity work.focus_comparator
    port map (
        clk => clk_tb,
        rstas => rstas_tb,
        focus_in => focus_in_tb,
        notFocus_in => notFocus_in_tb,
        data_valid => data_valid_tb,
        ledFocus => ledFocus_tb,
        ledNotFocus => ledNotFocus_tb
    );

process
begin
    -- Initial reset
    rstas_tb <= '0';
    data_valid_tb <= '0';
    focus_in_tb <= std_logic_vector(to_unsigned(0,8));
    notFocus_in_tb <= std_logic_vector(to_unsigned(0,8));
    wait for 25 ns;
    rstas_tb <= '1';
    wait for 20 ns;

    -- Under the threshold
    focus_in_tb <= std_logic_vector(to_unsigned(50,8));
    notFocus_in_tb <= std_logic_vector(to_unsigned(48,8));
    data_valid_tb <= '1';
    wait for 20 ns;
    data_valid_tb <= '0';
    wait for 20 ns;

    -- Over the threshold
    focus_in_tb <= std_logic_vector(to_unsigned(70,8));
    notFocus_in_tb <= std_logic_vector(to_unsigned(50,8));
    data_valid_tb <= '1';
    wait for 20 ns;
    data_valid_tb <= '0';
    wait for 20 ns;

    -- Intermediate zone
    focus_in_tb <= std_logic_vector(to_unsigned(58,8));
    notFocus_in_tb <= std_logic_vector(to_unsigned(50,8));
    data_valid_tb <= '1';
    wait for 20 ns;
    data_valid_tb <= '0';
    wait for 20 ns;

    -- Under low threshold
    focus_in_tb <= std_logic_vector(to_unsigned(52,8));
    notFocus_in_tb <= std_logic_vector(to_unsigned(50,8));
    data_valid_tb <= '1';
    wait for 20 ns;
    data_valid_tb <= '0';
    wait for 20 ns;

    wait;
end process;

end architecture;
