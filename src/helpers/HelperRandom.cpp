#include "HelperRandom.h"
HelperRandom::HelperRandom()
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	mEngine = std::mt19937(seed);
 
	mJewelTypes = { JewelType::BLUE, JewelType::GREEN, JewelType::PURPLE, JewelType::RED, JewelType::YELLOW };
	mJewelCount = mJewelTypes.size();
}

HelperRandom::~HelperRandom()
{
}

const JewelType& HelperRandom::GetRangeForJewelType() 
{
	return mJewelTypes[GetJewelType()];
}

const int HelperRandom::GetJewelType() 
{
	std::uniform_int_distribution<int> dis(0, 4);
	return dis(mEngine);
}