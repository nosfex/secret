#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_
#include <functional>
#include <king/Updater.h>
#include <unordered_map>
#include "../entity/Entity.h"
template <class func, class state>
struct StateData
{
	func mAction;
	state mNextState;
};

template <class func, class state>
class StateMachine : public King::Updater
{
public:
	StateMachine() = default;
	virtual ~StateMachine() = default;
	
	void Update() override
	{
		if (mStateContainer[mCurrentState].mAction())
		{
			mCurrentState = mStateContainer[mCurrentState].mNextState;
		}
	}
	void AddState(state stateID, func action, state nextStateID)
	{
		StateData<func, state> stateData;
		stateData.mAction = action;
		stateData.mNextState = nextStateID;
		mCurrentState = stateID;
		mStateContainer[stateID] = stateData;
	}
	
	void SetCurrentState(const state& current) { mCurrentState = current; }
	const state GetCurrentState() const { return mCurrentState; }
private:
	state mCurrentState;
	std::unordered_map<state, StateData<func, state>> mStateContainer;
};
#endif // !_STATEMACHINE_H_