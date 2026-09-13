library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity focus_comparator is
    port(
        clk : in std_logic;
        rstas: in std_logic;
        focus_in : in std_logic_vector(7 downto 0);
        notFocus_in : in std_logic_vector(7 downto 0);
        data_valid : in std_logic;
        ledFocus : out std_logic;
        ledNotFocus : out std_logic
    );
end entity;

architecture ctrl of focus_comparator is
    type state_t is (state_focus, state_not_focus);
    signal state : state_t;

    constant threshold_focus : integer := 15;
    constant threshold_not_focus : integer := 5;

    signal diff : integer;

begin

    diff <= to_integer(unsigned(focus_in)) - to_integer(unsigned(notFocus_in));

    process(clk, rstas)
    begin
        if rstas = '0' then
            state <= state_not_focus;
        elsif rising_edge(clk) then
            if data_valid = '1' then
                case state is
                    when state_not_focus =>
                    if diff > threshold_focus then
                        state <= state_focus;
                    end if;
                    when state_focus =>
                        if diff < threshold_not_focus then
                            state <= state_not_focus;
                        end if;
                    end case;
            end if;
        end if;
    end process;

    ledFocus <= '1' when state = state_focus else '0';
    ledNotFocus <= '1' when state = state_not_focus else '0';

end architecture;
