#pragma once

#include <cstdint>
#include <cassert>
#include <cstring>

namespace Kz64
{
#pragma pack(push, 1)
	union Register
	{
		struct {
			std::uint8_t lll;
			std::uint8_t llh;
			std::uint8_t lhl;
			std::uint8_t lhh;
			std::uint8_t hll;
			std::uint8_t hlh;
			std::uint8_t hhl;
			std::uint8_t hhh;
		} AsU8;
		struct {
			std::uint16_t ll;
			std::uint16_t lh;
			std::uint16_t hl;
			std::uint16_t hh;
		} AsU16;
		struct {
			std::uint32_t l;
			std::uint32_t h;
		} AsU32;
		struct {
			float l;
			float h;
		} AsF32;
		std::uint64_t AsU64;
		double AsF64;
		operator std::uint8_t() { return this->AsU8.lll; }
		operator std::uint16_t() { return this->AsU16.ll; }
		operator std::uint32_t() { return this->AsU32.l; }
		operator std::uint64_t() { return this->AsU64; }
		operator double() { return this->AsF64; }
		operator float() { return this->AsF32.l; }
		Register &operator =(std::uint64_t from) { AsU64 = from; return *this; }
		Register &operator =(double from) { AsF64 = from; return *this; }
		Register &operator =(std::uint32_t from) { AsU32.l = from; return *this; }
		Register &operator =(float from) { AsF32.l = from; return *this; }
		Register &operator =(std::uint16_t from) { AsU16.ll = from; return *this; }
		Register &operator =(std::uint8_t from) { AsU8.lll = from; return *this; }
		Register &operator +(Register &right) { AsU64 += right.AsU64; return *this; }
		Register &operator -(Register &right) { AsU64 -= right.AsU64; return *this; }
		Register &operator *(Register &right) { AsU64 *= right.AsU64; return *this; }
		Register &operator /(Register &right) { AsU64 /= right.AsU64; return *this; }
		Register &operator %(Register &right) { AsU64 %= right.AsU64; return *this; }
		Register &operator ~() { AsU64 = ~AsU64; return *this; }
		Register &operator |(Register &right) { AsU64 |= right.AsU64; return *this; }
		Register &operator &(Register &right) { AsU64 &= right.AsU64; return *this; }
		Register &operator ^(Register &right) { AsU64 ^= right.AsU64; return *this; }
		Register &operator +=(Register &right) { return *this + right; }
		Register &operator -=(Register &right) { return *this - right; }
		Register &operator *=(Register &right) { return *this * right; }
		Register &operator /=(Register &right) { return *this / right; }
		Register &operator %=(Register &right) { return *this % right; }
		Register &operator |=(Register &right) { return *this | right; }
		Register &operator &=(Register &right) { return *this & right; }
		Register &operator ^=(Register &right) { return *this ^ right; }
		Register &operator ++() { AsU64++; return *this; }
		Register &operator --() { AsU64--; return *this; }
		Register &operator ++(int) { Register old = *this; AsU64++; return old; }
		Register &operator --(int) { Register old = *this; AsU64--; return old; }
		Register &Nor(Register &right) { AsU64 = ~(AsU64 | right.AsU64); return *this; }
		Register &Nand(Register &right) { AsU64 = ~(AsU64 & right.AsU64); return *this; }
		Register &Nxor(Register &right) { AsU64 = ~(AsU64 ^ right.AsU64); return *this; }
	};
#pragma pack(pop)
}