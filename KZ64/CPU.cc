#include "CPU.hh"
#include "Cast.hh"
#include <iostream>

namespace Kz64
{
	void Kz64::Next()
	{
		Register &ip = GetIP();
		std::function<void(Register &)> dispatchTable[] = {
			[](Register &r) {},	// NOP
			[this, &ip](Register &r)	// STORE64
			{
				std::uint8_t _bytes[8] = {
					Code[ip++],
					Code[ip++],
					Code[ip++],
					Code[ip++],
					Code[ip++],
					Code[ip++],
					Code[ip++],
					Code[ip++],
				};
				IntCast cast = _bytes;
				r = (uint64_t)cast;
			},
			[this, &ip](Register &r)	// STORE32
			{
				std::uint8_t _bytes[8] = {
					Code[ip++],
					Code[ip++],
					Code[ip++],
					Code[ip++],
					0,
					0,
					0,
					0
				};
				IntCast cast = _bytes;
				r = (uint32_t)cast;
			},
			[this, &ip](Register &r)	// STORE16
			{
				std::uint8_t _bytes[8] = {
					Code[ip++],
					Code[ip++],
					0,
					0,
					0,
					0,
					0,
					0
				};
				IntCast cast = _bytes;
				r = (uint16_t)cast;
			},
			[this, &ip](Register &r)	// STORE8
			{
				r = (std::uint8_t)Code[ip++];
			},
			[this, &ip](Register &r)	// HALT
			{
				Halted = true;
			},
			[this, &ip](Register &r)	// PRINTREG
			{
				std::cout << (uint64_t)r << std::endl;
			},
			[this, &ip](Register &r)	// ADD
			{
				Register &b = GetRegister(Code[ip++]);
				r += b;
			},
			[this, &ip](Register &r)	// SUB
			{
				Register &b = GetRegister(Code[ip++]);
				r -= b;
			},
			[this, &ip](Register &r)	// MUL
			{
				Register &b = GetRegister(Code[ip++]);
				r *= b;
			},
			[this, &ip](Register &r)	// DIV
			{
				Register &b = GetRegister(Code[ip++]);
				r /= b;
			},
			[this, &ip](Register &r)	// MOD
			{
				Register &b = GetRegister(Code[ip++]);
				r %= b;
			},
			[this, &ip](Register &r)	// OR
			{
				Register &b = GetRegister(Code[ip++]);
				r |= b;
			},
			[this, &ip](Register &r)	// AND
			{
				Register &b = GetRegister(Code[ip++]);
				r &= b;
			},
			[this, &ip](Register &r)	// XOR
			{
				Register &b = GetRegister(Code[ip++]);
				r ^= b;
			},
			[this, &ip](Register &r)	// NOR
			{
				Register &b = GetRegister(Code[ip++]);
				r = r.Nor(b);
			},
			[this, &ip](Register &r)	// NAND
			{
				Register &b = GetRegister(Code[ip++]);
				r = r.Nand(b);
			},
			[this, &ip](Register &r)	// NXOR
			{
				Register &b = GetRegister(Code[ip++]);
				r = r.Nxor(b);
			},
		};
		uint8_t instruction = Code[ip++];
		uint8_t reg_index = Code[ip++];
		dispatchTable[instruction](GetRegister(reg_index));
	}
}