#include "CPU.hh"
#include <iostream>

int main(void)
{
	std::vector<std::uint8_t> code = std::vector<std::uint8_t>
	{
		Kz64::Instructions::Store8, Kz64::Registers::R0, 3,
		Kz64::Instructions::Store8, Kz64::Registers::R1, 5,
		Kz64::Instructions::Mul, Kz64::Registers::R0, Kz64::Registers::R1,
		Kz64::Instructions::PrintReg, Kz64::Registers::R0,
		Kz64::Instructions::Halt, Kz64::Registers::Null,
	};
	Kz64::Kz64 kz64(code);
	kz64.Execute();
}