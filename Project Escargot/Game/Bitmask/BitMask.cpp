#include "stdafx.h"
#include "BitMask.h"
namespace Snail {

	Bitmask::Bitmask()
	{

	}
	Bitmask::~Bitmask()
	{

	}

	// return and change a bitmask
	int Bitmask::returnBitMask(typeBitMask type, numBitMask bitmask)
	{
		return TabBitmask[type][bitmask];
	}
	void Bitmask::changeEtatBitMask(typeBitMask type, numBitMask bitmask, int bits)
	{
		if (type == TypeDirectionCollide && bits <= 15) {
			TabBitmask[TypeDirectionCollide][bitmask] = bits;
			std::cout << "Changement fait à: TypeDirectionCollide \n bitmask choisie : " << bitmask << "\n ints: "<< bits << "\n";
		}
		else if (type == TypeCollide && bits <= 63) {
			TabBitmask[TypeCollide][bitmask] = bits;
			std::cout << "Changement fait à: TypeCollide \n bitmask choisie : " << bitmask << "\n ints: " << bits<<"\n";
		}
		/*else if (type == TypeCollider && bits <= 63) {
			TabBitmask[TypeCollider][bitmask] = bits;
			std::cout << "Changement fait à: TypeCollider \n bitmask choisie : " << bitmask << "\n ints: " << bits << "\n";
		}*/
		else {
			std::cout << "impossible de changer veuiller refaire le changement\n ";
		}
	}

	int Bitmask::GetLayersObject(LayersObject nameLayers)
	{
		return Layers[nameLayers];
	}

	//logicAnd return -> int 
	int Bitmask::logicAnd(typeBitMask type1, numBitMask bitmask1, typeBitMask type2, numBitMask bitmask2)
	{
		return TabBitmask[type1][bitmask1] & TabBitmask[type2][bitmask2];
	}
	int Bitmask::logicAnd(int bits, typeBitMask type2, numBitMask bitmask2)
	{
		return bits & TabBitmask[type2][bitmask2];
	}
	int Bitmask::logicAnd(int bits, int bits2)
	{
		return bits & bits2;
	}

	//logicXor return-> int 
	int Bitmask::logicXor(typeBitMask type1, numBitMask bitmask1, typeBitMask type2, numBitMask bitmask2)
	{
		return TabBitmask[type1][bitmask1] ^ TabBitmask[type2][bitmask2];
	}
	int Bitmask::logicXor(int bits, typeBitMask type2, numBitMask bitmask2)
	{
		return bits ^ TabBitmask[type2][bitmask2];
	}
	int Bitmask::logicXor(int bits, int bits2)
	{
		return bits ^ bits2;
	}

	//LogicOr return-> int
	int Bitmask::logicOr(typeBitMask type1, numBitMask bitmask1, typeBitMask type2, numBitMask bitmask2)
	{
		return TabBitmask[type1][bitmask1] | TabBitmask[type2][bitmask2];
	}
	int Bitmask::logicOr(int bits, typeBitMask type2, numBitMask bitmask2)
	{
		return bits | TabBitmask[type2][bitmask2];
	}
	int Bitmask::logicOr(int bits, int bits2)
	{
		return bits | bits2;
	}

	// logicAnd return -> bool
	bool Bitmask::logicAndBool(typeBitMask type1, numBitMask bitmask1, typeBitMask type2, numBitMask bitmask2)
	{
		if (logicAnd(type1, bitmask1, type2, bitmask2) == 0)
			return false;
		else
			return true;
	}
	bool Bitmask::logicAndBool(int bits, typeBitMask type2, numBitMask bitmask2)
	{
		if (logicAnd(bits, type2, bitmask2) == 0)
			return false;
		else
			return true;
	}
	bool Bitmask::logicAndBool(int bits, int bits2)
	{
		if (logicAnd(bits, bits2) == 0)
			return false;
		else
			return true;
	}

	//logicXor return -> bool 
	bool Bitmask::logicXorBool(typeBitMask type1, numBitMask bitmask1, typeBitMask type2, numBitMask bitmask2)
	{
		if (logicXor(type1, bitmask1, type2, bitmask2) == 0)
			return false;
		else
			return true;
	}
	bool Bitmask::logicXorBool(int bits, typeBitMask type2, numBitMask bitmask2)
	{
		if (logicXor(bits, type2, bitmask2) == 0)
			return false;
		else
			return true;
	}
	bool Bitmask::logicXorBool(int bits, int bits2)
	{
		if (logicXor(bits, bits2) == 0)
			return false;
		else
			return true;
	}

	//logicOr return->bool
	bool Bitmask::logicOrBool(typeBitMask type1, numBitMask bitmask1, typeBitMask type2, numBitMask bitmask2)
	{
		if (logicOr(type1, bitmask1, type2, bitmask2) == 0)
			return false;
		else
			return true;
	}
	bool Bitmask::logicOrBool(int bits, typeBitMask type2, numBitMask bitmask2)
	{
		if (logicOr(bits, type2, bitmask2) == 0)
			return false;
		else
			return true;
	}
	bool Bitmask::logicOrBool(int bits, int bits2)
	{
		if (logicOr(bits,bits2) == 0)
			return false;
		else
			return true;
	}
}
