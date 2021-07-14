#pragma once

#include "Register.hh"
#include <vector>
#include <functional>
#include <type_traits>

namespace Kz64
{
	enum Instructions : std::uint8_t
	{
		Nop,
		Store64,
		Store32,
		Store16,
		Store8,
		Halt,
		PrintReg,
		Add,
		Sub,
		Mul,
		Div,
		Mod,
		Or,
		And,
		Xor,
		NOr,
		NAnd,
		NXor,
		LGP,	// Load General Protection structure
	};
	enum Registers : std::uint8_t
	{
		Null,
		R0 = 0,
		R1,
		R2,
		R3,
		R4,
		R5,
		R6,
		R7,
		R8,
		R9,
		R10,
		R11,
		R12,
		R13,
		R14,
		R15,
		F0,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		C0,
		C1,
		C2,
		C3,
		ST,
		SB,
		FR,
		IP,
	};
#pragma pack(push, 1)
	struct GPDescriptor
	{
		uint8_t FMA : 1;	// Full memory access
		uint8_t FSA : 1;	// Full stack access (overriden by FMA)
		uint8_t PK : 1;		// Permission Fork
		uint8_t IVK : 1;	// Interrupt Vector Fork
		uint8_t FE : 1;		// Fork Exit
		uint8_t UNUSED_ : 3;// unused
		uint8_t UNUSED : 8;	// unused
		uint8_t PS;			// Parent Selector
		uint8_t CS;			// Current Selector (selector for this GP)
		GPDescriptor(uint32_t rawDescriptor) { assert(sizeof(GPDescriptor) == sizeof(uint32_t));
		memcpy(this, &rawDescriptor, sizeof(GPDescriptor)); }
		GPDescriptor() {}
		operator uint32_t() { uint32_t result; memcpy(&result, this, sizeof(uint32_t)); return result; }
	};
#pragma pack(pop)
	class Kz64
	{
	private:
		Register Registers[32] = {};
		GPDescriptor GeneralProtectionStructures[256];
		std::uint8_t CurrentGPSelector = 255;
		std::vector<std::uint8_t> Code;
		void Next();
		bool Halted = false;
	public:
		Kz64(const std::vector<std::uint8_t> code) { Code = code; }
		~Kz64() {}
		void Execute()
		{
			while (!Halted)
				Next();
		}
		Register &GetRegister(std::uint8_t i) { return Registers[i]; }
		Register &GetR0() { return Registers[0]; }
		Register &GetR1() { return Registers[1]; }
		Register &GetR2() { return Registers[2]; }
		Register &GetR3() { return Registers[3]; }
		Register &GetR4() { return Registers[4]; }
		Register &GetR5() { return Registers[5]; }
		Register &GetR6() { return Registers[6]; }
		Register &GetR7() { return Registers[7]; }
		Register &GetR8() { return Registers[8]; }
		Register &GetR9() { return Registers[9]; }
		Register &GetR10() { return Registers[10]; }
		Register &GetR11() { return Registers[11]; }
		Register &GetR12() { return Registers[12]; }
		Register &GetR13() { return Registers[13]; }
		Register &GetR14() { return Registers[14]; }
		Register &GetR15() { return Registers[15]; }
		Register &GetF0() { return Registers[16]; }
		Register &GetF1() { return Registers[17]; }
		Register &GetF2() { return Registers[18]; }
		Register &GetF3() { return Registers[19]; }
		Register &GetF4() { return Registers[20]; }
		Register &GetF5() { return Registers[21]; }
		Register &GetF6() { return Registers[22]; }
		Register &GetF7() { return Registers[23]; }
		Register &GetC0() { return Registers[24]; }
		Register &GetC1() { return Registers[25]; }
		Register &GetC2() { return Registers[26]; }
		Register &GetC3() { return Registers[27]; }
		Register &GetST() { return Registers[28]; }
		Register &GetSB() { return Registers[29]; }
		Register &GetFR() { return Registers[30]; }
		Register &GetIP() { return Registers[31]; }
	};
}
