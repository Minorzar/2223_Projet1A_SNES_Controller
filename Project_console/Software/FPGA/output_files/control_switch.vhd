library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity control_switch is
    Port(
        Btn: in STD_LOGIC_VECTOR (9 downto 0);
        Led: out STD_LOGIC_VECTOR (9 downto 0)
    );
end control_switch;

architecture Behavioral of control_switch is
begin
    Led <= Btn;
end Behavioral;