#include "stdafx.h"
#include "BitMask.h"
namespace Snail {

	Bitmask::Bitmask()
	{

	}
	Bitmask::~Bitmask()
	{

	}
	int Bitmask::returnBitMask(typeBitMask type, numBitMask bitmask)
	{
		return TabBitmask[type][bitmask];
	}
	void Bitmask::changeEtatBitMask(typeBitMask type, numBitMask bitmask, int bits)
	{
		TabBitmask[type][bitmask] = bits;
	}
	int Bitmask::logicAnd(typeBitMask type1, numBitMask bitmask1, typeBitMask type2, numBitMask bitmask2)
	{
		return TabBitmask[type1][bitmask1] & TabBitmask[type2][bitmask2];
	}
	int Bitmask::logicXor(typeBitMask type1, numBitMask bitmask1, typeBitMask type2, numBitMask bitmask2)
	{
		return TabBitmask[type1][bitmask1] ^ TabBitmask[type2][bitmask2];
	}
	int Bitmask::logicOr(typeBitMask type1, numBitMask bitmask1, typeBitMask type2, numBitMask bitmask2)
	{
		return TabBitmask[type1][bitmask1] | TabBitmask[type2][bitmask2];
	}
}
