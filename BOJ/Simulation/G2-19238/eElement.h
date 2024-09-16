#pragma once

#include <cstdint>

enum class eElement : uint8_t
{
	Road = 0x00,
	Wall = 0x01,
	Person = 0x02,
	Destination = 0x03
};