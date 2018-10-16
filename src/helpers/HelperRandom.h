#ifndef _RANDOM_H_
#define _RANDOM_H_
#include <random>
#include <functional>
#include <memory>
#include <chrono>
#include "../entity/JewelType.h"
class HelperRandom
{
public:
	HelperRandom();
	HelperRandom(const HelperRandom& other) = delete;
	~HelperRandom();

	const JewelType& GetRangeForJewelType() ;
private:
	std::mt19937 mEngine;
	std::vector<JewelType> mJewelTypes;
	mutable int mJewelCount;
	const int GetJewelType();
};
#endif // _RANDOM_H_