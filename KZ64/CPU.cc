#include "CPU.hh"
#include "Cast.hh"
#include <iostream>
#include <bitset>

#define LAST(k, n) ((k) & ((1 << (n)) -1))
#define MID(k, m, n) LAST((k) >> (m), ((n) - (m)))

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
			[this, &ip](Register &r)	// LGP
			{
				uint32_t gps = (uint32_t)r;
				uint32_t mustBeZero0 = MID(gps, 5, 11);
				if (mustBeZero0)
				{
					// TODO: fire Invalid Structure interrupt
					std::cout << "Invalid General Protection structure: Zero fields are not zero" << std::endl;
					std::cout << std::bitset<8>(mustBeZero0) << std::endl;
					Halted = true;
					return;
				}
				GPDescriptor descriptor = gps;
				if (CurrentGPSelector != 255) // there is a current descriptor
				{
					uint32_t structurei = GeneralProtectionStructures[CurrentGPSelector];
					if (!structurei)
					{
						std::cout << "Usage of invalid general protection structure " << CurrentGPSelector << std::endl;
						Halted = true;
						return;
					}
					GPDescriptor *_descriptor = &(GeneralProtectionStructures[CurrentGPSelector]);
					if (!_descriptor->PK) // FSA is disabled
					{
						std::cout << "Cannot override general protection, PK is disabled" << std::endl;
						Halted = true;
						return;
					}
					if (descriptor.CS == CurrentGPSelector)
					{
						std::cout << "Warning: Destination GP selector is the same as the current one. This will result in a loss of permissions." << std::endl;
					}
					if (GeneralProtectionStructures[descriptor.CS])
					{
						std::cout << "Cannot override non-parent general protection structure" << std::endl;
						Halted = true;
						return;
					}
					if (descriptor.PS != CurrentGPSelector)
					{
						std::cout << "Parent selector is the same as the current selector" << std::endl;
						Halted = true;
						return;
					}
				}
				if (descriptor.CS == 255)
				{
					std::cout << "255 is an invalid general protection selector" << std::endl;
					Halted = true;
					return;
				}
				std::cout << (bool)descriptor.FMA << std::endl;
				std::cout << (bool)descriptor.FSA << std::endl;
				std::cout << (bool)descriptor.PK << std::endl;
				std::cout << (bool)descriptor.IVK << std::endl;
				std::cout << (bool)descriptor.FE << std::endl;
				GeneralProtectionStructures[descriptor.CS] = descriptor;
			},
		};
		uint8_t instruction = Code[ip++];
		uint8_t reg_index = Code[ip++];
		dispatchTable[instruction](GetRegister(reg_index));
	}
}