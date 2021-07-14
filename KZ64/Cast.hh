#pragma once

#include <cstdint>
#include <cstring>

namespace Kz64
{
#pragma pack(push, 1)
	union IntCast
	{
		std::uint8_t Bytes[8];
		std::uint16_t Shorts[4];
		std::uint32_t Longs[2];
		std::uint64_t LLong;
		IntCast(std::uint8_t bytes[8]) { std::memcpy(Bytes, bytes, 8); }
		IntCast(std::uint16_t shorts[4]) { std::memcpy(Shorts, shorts, 8); }
		IntCast(std::uint32_t longs[2]) { std::memcpy(Longs, longs, 8); }
		IntCast(std::uint64_t llong) { LLong = llong; }
		operator uint8_t *() { return Bytes; }
		operator uint16_t *() { return Shorts; }
		operator uint32_t *() { return Longs; }
		operator uint8_t() { return Bytes[0]; }
		operator uint16_t() { return Shorts[0]; }
		operator uint32_t() { return Longs[0]; }
		operator uint64_t() { return LLong; }
	};
#pragma pop
}
