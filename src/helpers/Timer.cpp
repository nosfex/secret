#include "Timer.h"
#include <iostream>
//-----------------------------------------------------------------------------
Timer::Timer() :mTick(0.0f), mMaxTick(0.0f), mIsRunning(false)
{
}
//-----------------------------------------------------------------------------
Timer::Timer(float maxTick) : mTick(0.0f), mMaxTick(maxTick), mIsRunning(false)
{
}
//-----------------------------------------------------------------------------
void Timer::Start()
{
	if (!IsRunning() && IsTimeFinished())
	{
		mTick = 0.0f;
	}
	mIsRunning = true;
}
//-----------------------------------------------------------------------------
void Timer::Update(const float& dt)
{
	if (mTick >= mMaxTick)
	{
		mIsRunning = false;
	}
	if (mIsRunning)
	{
		mTick += dt;
	}
}
//-----------------------------------------------------------------------------
const bool& Timer::IsTimeFinished() const
{
	if (mTick >= mMaxTick)
	{
		std::cout << "time over" << std::endl;
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
const bool& Timer::IsRunning() const
{
	return mIsRunning;
}
//-----------------------------------------------------------------------------