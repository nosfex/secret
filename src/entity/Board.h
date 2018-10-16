#ifndef _BOARD_H_
#define _BOARD_H_
#include "Entity.h"
#include <vector>
#include <memory>
#include <king/Engine.h>
#include <iostream>
#include "../helpers/HelperRandom.h"
#include "../helpers/HelperMath.h"
#include "../state/StateMachine.h"
#include "../helpers/Timer.h"
#include "Jewel.h"
namespace entity
{
	class Board : public Entity
	{

	public:
		Board();
		Board(const glm::vec2& pos, const King::Engine::Texture& tex);
		virtual ~Board();
		void Start(const glm::vec2& offset = glm::vec2(0.0f, 0.0f));
		void Update() override;
		void Update(const float &dt) override;
		void CollapseBoardJewels();
		void CheckVerticalLine(const int& startidx) const;
		void CheckHorizontalLine(const int& startidx) const;
		void CheckClearLine(const std::vector<std::shared_ptr<Jewel>>& line) const;
		void ProcessUserSwap(const glm::vec2& inputPosition);
		void Cleanup();
		bool lockBoard;
		bool DoNothing();
		bool WaitForSwitch();
		bool IntroSequence();

		static const int GRID_AXIS_COUNT = 8;
		static const float GRID_SIZE;
	private:
		glm::vec2 mGridOffset;
		std::vector<int> mPreviousInput;
		std::vector<std::shared_ptr<Jewel>> mGridContainer;
		std::unique_ptr<HelperRandom> mRandom;
		std::unique_ptr<Timer> mTimeWaitSwitch;
		std::unique_ptr<Timer> mResetWait;
		mutable int mLineCount;
		
		int introCounter;
		
		
		void SwapJewels(std::shared_ptr<Jewel>& a, std::shared_ptr<Jewel>& b) const;
		void SwapJewels(const int&a, const int& b) ;

		bool ResetDeadJewels();
		const int& GetNearestToPoint(const glm::vec2& point) const;

		enum class BoardState
		{
			INIT = 0,
			END_INIT,
			CHECK_FOR_LINES,
			UPDATE,
			WAIT_FOR_SWITCH,
			UNDO_SWAP,
			REFILL_BOARD
		};
		std::shared_ptr<Entity> mCursor;
		int mSelectedGrid;
		StateMachine<std::function<bool()>, BoardState>* sm;
	};
}
#endif // !_BOARD_H_