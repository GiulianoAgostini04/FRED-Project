library ieee;
use ieee.std_logic_1164.all;

entity channel_selector is
    port (
        sw : in std_logic_vector(1 downto 0);
        btn : in std_logic;
        q : out std_logic_vector(1 downto 0);
        led : out std_logic_vector(3 downto 0)
    );
end entity;

architecture rtl of channel_selector is
    signal q_int : std_logic_vector(1 downto 0);
begin

    process(btn)
    begin
        if rising_edge(btn) then
            q_int <= sw;
        end if;
    end process;
    
    led(0) <= (not q_int(1)) and (not q_int(0));
    led(1) <= (not q_int(1)) and q_int(0);
    led(2) <= (q_int(1) and (not q_int(0)));
    led(3) <= (q_int(1) and q_int(0));

    q <= q_int;
    
end architecture;
