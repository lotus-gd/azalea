#include "pch.h"

#include "replay.h"

Replay::Replay(size_t size)
	: bitSize(size)
{
	size_t intSize = size / 8;
	if (size % 8 != 0) ++intSize;
	data.resize(intSize);
	memset(data.data(), 0, intSize);
}

bool Replay::operator[](size_t index) const
{
	if (index >= bitSize) return false;
	size_t dataIndex = index / 8;
	unsigned char intData = data[dataIndex];
	bool val = intData & (1 << 7 - (index % 8));
	return val;
}

void Replay::Set(size_t index, bool val)
{
	if (index >= bitSize) return;
	if (operator[](index) == val) return;
	size_t dataIndex = index / 8;
	unsigned char& intData = data[dataIndex];
	intData ^= 1 << 7 - (index % 8);
}

std::string Replay::ToString(bool decoration) const
{
	std::stringstream out;
	for (size_t i = 0; i < bitSize; ++i)
	{
		out << operator[](i) ? '1' : '0';
		if (decoration && (i + 1) % 8 == 0) out << ' ';
	}
	if (decoration && bitSize < data.size() * 8)
	{
		int deadBytes = data.size() * 8 - bitSize;
		out << " + " << deadBytes << " DEAD BYTE";
		if (deadBytes != 1) out << "S";
	}
	return out.str();
}
