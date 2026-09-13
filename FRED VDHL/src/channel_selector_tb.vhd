library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity channel_selector_tb is
end entity;

architecture sim of channel_selector_tb is
    signal sw_tb : std_logic_vector(1 downto 0);
    signal btn_tb : std_logic;
    signal q_tb : std_logic_vector(1 downto 0);
    signal led_tb : std_logic_vector(3 downto 0);
    signal channel_num : integer;
begin
    dut: entity work.channel_selector
    port map (
        sw => sw_tb,
        btn => btn_tb,
        q => q_tb,
        led => led_tb
    );

    channel_num <= to_integer(unsigned(q_tb));

    process
    begin
        sw_tb <= "00";
        btn_tb <= '0';
        wait for 10 ns;

        btn_tb <= '1';
        wait for 10 ns;

        sw_tb <= "01";
        btn_tb <= '0';
        wait for 10 ns;

        btn_tb <= '1';
        wait for 10 ns;

        sw_tb <= "10";
        btn_tb <= '0';
        wait for 10 ns;

        btn_tb <= '1';
        wait for 10 ns;

        sw_tb <= "11";
        btn_tb <= '0';
        wait for 10 ns;

        btn_tb <= '1';
        wait for 10 ns;

        wait;


    end process;

end architecture;
