#ifndef _TIMER_H_
#define _TIMER_H_
class Timer
{
public:
	
	Timer();
	Timer(float maxTick);
	virtual ~Timer() = default;
	void Start();
	void Update(const float& dt);
	const bool& IsTimeFinished() const;
	const bool& IsRunning() const;

private:
	bool mIsRunning;
	float mTick;
	float mMaxTick;
};
#endif //!_TIMER_H_