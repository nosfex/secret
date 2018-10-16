#include "Board.h"
#include "helpers/Factory.h"
#include <windows.h>
namespace entity
{
	//----------------------------------------------------------------------------
	const float Board::GRID_SIZE = 36.0f;
	//----------------------------------------------------------------------------
	Board::Board() :Entity()
	{
	}
	//----------------------------------------------------------------------------
	Board::Board(const glm::vec2& pos, const King::Engine::Texture& tex) : Entity(pos, tex)
	{
	}
	//----------------------------------------------------------------------------
	Board::~Board()
	{
	}
	//----------------------------------------------------------------------------
	void Board::Start(const glm::vec2& offset)
	{
		mRandom = std::make_unique<HelperRandom>();
		
		mGridOffset = offset;
		size_t maxGrids = GRID_AXIS_COUNT * GRID_AXIS_COUNT;
		mGridContainer.reserve(maxGrids);

		// Add all the grids to the shared container
		for (size_t i = 0; i < maxGrids; i++)
		{
			// How many GRID_AXIS_COUNT we have on I?
			int y = i / GRID_AXIS_COUNT;
			// modulate the current X axis (module returns 0 on equal GRID_AXIS_COUNT or 0)
			int x = i % GRID_AXIS_COUNT;
			std::shared_ptr<entity::Jewel> jewel = (Factory::CreateDefaultEntity<Jewel>({ offset.x + (GRID_SIZE * x), 0.0f }, King::Engine::Texture::TEXTURE_BLUE));
			JewelType type = mRandom->GetRangeForJewelType();
			jewel->UpdateType(type);
			jewel->mGridPosition = { offset.x + (GRID_SIZE * x), offset.y + (GRID_SIZE * y) };
			jewel->mDropSpeed += 5.0f;
			mGridContainer.push_back(jewel);
			jewel->mIsAlive = false;
		}

		lockBoard = true;
		introCounter = GRID_AXIS_COUNT * GRID_AXIS_COUNT;
		// Store the flow control of the Board in the StateMachine
		sm = new StateMachine<std::function<bool()>, BoardState>();

		sm->AddState(BoardState::INIT, std::bind(&Board::IntroSequence, this), BoardState::UPDATE);
		sm->AddState(BoardState::UPDATE, std::bind(&Board::DoNothing, this), BoardState::WAIT_FOR_SWITCH);
		sm->AddState(BoardState::WAIT_FOR_SWITCH, std::bind(&Board::WaitForSwitch, this), BoardState::CHECK_FOR_LINES);
		sm->AddState(BoardState::CHECK_FOR_LINES, []() { return false; }, BoardState::REFILL_BOARD);
		sm->AddState(BoardState::REFILL_BOARD, std::bind(&Board::ResetDeadJewels, this), BoardState::CHECK_FOR_LINES);

		sm->SetCurrentState(BoardState::INIT);
		// Create the cursor
		mCursor = Factory::CreateDefaultEntity<Entity>(glm::vec2(), King::Engine::TEXTURE_GRID);
		mCursor->mIsAlive = false;
		mSelectedGrid = -1;
		mLineCount = 0;
		// Create the timer for the timeWaitSwitch state
		mTimeWaitSwitch = std::make_unique<Timer>(0.5f);
		mResetWait = std::make_unique<Timer>(1.0f);
	}
	//----------------------------------------------------------------------------
	void Board::Update()
	{
		sm->Update();

		switch (sm->GetCurrentState())
		{
		case BoardState::INIT:
			break;

		case BoardState::UPDATE:
		
			break;
		case BoardState::WAIT_FOR_SWITCH:
			 
			break;
		case BoardState::CHECK_FOR_LINES:
			mLineCount = 0;
			CheckVerticalLine(0);
			CheckHorizontalLine(0); 
			introCounter = GRID_AXIS_COUNT * GRID_AXIS_COUNT;
			if (mLineCount != 0)
			{
				mPreviousInput.clear();
				sm->SetCurrentState(BoardState::REFILL_BOARD);
				mSelectedGrid = -1;
			}
			else
			{
				lockBoard = false;
				if (mPreviousInput.size())
				{
					SwapJewels(mPreviousInput[1], mPreviousInput[0]);
					lockBoard = true;
					mSelectedGrid = -1;
					mPreviousInput.clear();
				}
				sm->SetCurrentState(BoardState::UPDATE);
			}
			break;
		case BoardState::REFILL_BOARD:
			break;
		}
		CollapseBoardJewels();
	}
	//----------------------------------------------------------------------------
	void Board::Update(const float& dt)
	{
		Update();
		mResetWait->Update(dt);
		mTimeWaitSwitch->Update(dt);
	}
	//----------------------------------------------------------------------------
	void Board::CollapseBoardJewels()
	{
		size_t max = (GRID_AXIS_COUNT * GRID_AXIS_COUNT) - 1;
		for (size_t i = max; i >= GRID_AXIS_COUNT; i--)
		{
			if (mGridContainer[i]->mIsAlive == false &&
				mGridContainer[i - GRID_AXIS_COUNT]->mIsAlive == true)
			{
				SwapJewels(i, i - GRID_AXIS_COUNT);
			}
		}
	}
	//----------------------------------------------------------------------------
	void Board::CheckVerticalLine(const int& startidx) const
	{
		std::vector<std::shared_ptr<Jewel>> clear;
		clear.reserve(GRID_AXIS_COUNT);
		std::shared_ptr<Jewel> pivot = mGridContainer[startidx];

		int max = GRID_AXIS_COUNT;
		int next = 0;
		while (next < max)
		{
			std::shared_ptr<Jewel> header = mGridContainer[startidx + (next * GRID_AXIS_COUNT)];
			int prev = next;
			next++;
			if (pivot->GetType() == header->GetType())
			{
				clear.push_back(header);
				if (next == max)
				{
					CheckClearLine(clear);
					clear.clear();
				}
			}
			else
			{
				CheckClearLine(clear);
				clear.clear();
				next	 = prev;
				pivot	 = header;
			}
		}
		if (startidx + 1 < (GRID_AXIS_COUNT))
		{
			CheckVerticalLine(startidx + 1);
		}
	}
	//----------------------------------------------------------------------------
	void Board::CheckHorizontalLine(const int& startidx) const
	{
		int next = startidx;
		std::vector<std::shared_ptr<Jewel>> clear;
		clear.reserve(GRID_AXIS_COUNT);
		std::shared_ptr<Jewel> pivot = mGridContainer[startidx];
		
		int max = (GRID_AXIS_COUNT + startidx);
		while (next < max)
		{
			std::shared_ptr<Jewel> header = mGridContainer[next];
			int prev = next;
			next++;
			if (pivot->GetType() == header->GetType())
			{
				clear.push_back(header);
				if (next == max)
				{
					CheckClearLine(clear);
					clear.clear();
				}
			}
			else
			{
				CheckClearLine(clear);
				clear.clear();
				next = prev;
				pivot = header;
			}
		}
		if (max < (GRID_AXIS_COUNT * GRID_AXIS_COUNT))
		{
			CheckHorizontalLine(max);
		}
	}
	//----------------------------------------------------------------------------
	void Board::CheckClearLine(const std::vector<std::shared_ptr<Jewel>>& line) const
	{
		// Minimum vector length for a clear line
		if (line.size() >= 3)
		{
			for (auto g : line)
			{
				g->mIsAlive = false;
			}
			mLineCount++;
		}	
	}
	//----------------------------------------------------------------------------
	void Board::ProcessUserSwap(const glm::vec2& inputPosition)
	{
		// Does imaginary rect contains the mouse point?
		if ((inputPosition.x < mGridOffset.x + GRID_SIZE * GRID_AXIS_COUNT && inputPosition.x > mGridOffset.x) &&
			(inputPosition.y < mGridOffset.y + GRID_SIZE * GRID_AXIS_COUNT && inputPosition.y > mGridOffset.y))
		{
		
			int temp = GetNearestToPoint(inputPosition);
			// If we don't have a currently selected grid, try to pick one that is available
			if (mSelectedGrid == -1 && mGridContainer[temp]->mIsAlive)
			{
				mSelectedGrid		= temp;
				// Enable the cursor for the first time
				mCursor->mIsAlive	= true;
				mCursor->mPosition	= mGridContainer[mSelectedGrid]->mPosition;
			}
			else if(mGridContainer[temp]->mIsAlive)
			{
				// Check distance between latest picked grid and the previously selected one
				int x = std::abs(mGridContainer[temp]->mPosition.x - mGridContainer[mSelectedGrid]->mPosition.x);
				int y = std::abs(mGridContainer[temp]->mPosition.y - mGridContainer[mSelectedGrid]->mPosition.y);
				
				// If the sum of both components is higher than the grid size,
				// then this is a diagonal pick case (abs case ignores sign, no need to check direction)
				//  -36, 36 | 0,36  | 36,36
				//	-36,0   | 0,0   | 36,0
				//  -36,-36 | 0,-36 | 36,-36
				// Any case bigger than the grid size, or <= 0 is an invalid position
				int sum = x + y;
				if ( sum <= GRID_SIZE && sum > 0)
				{
					// Lock the input while we check if we have a valid clear
					lockBoard = true;
					SwapJewels(mSelectedGrid, temp);
					mPreviousInput = { mSelectedGrid, temp };
				}
				else
				{
					// If we don't have a valid swapable combination,
					// Set the far grid as our current one
					mSelectedGrid = temp;
					mCursor->mIsAlive = true;
					mCursor->mPosition = mGridContainer[mSelectedGrid]->mPosition;
				}
			}
		
		}
	}
	//----------------------------------------------------------------------------
	void Board::Cleanup()
	{
		for (auto container : mGridContainer)
		{
			container.reset();

		}
		mGridContainer.erase(mGridContainer.begin(), mGridContainer.end());
		mGridContainer.clear();
	
	}
	//----------------------------------------------------------------------------
	bool Board::DoNothing()
	{
		return lockBoard;
	}
	//----------------------------------------------------------------------------
	bool Board::WaitForSwitch()
	{
		if (mTimeWaitSwitch->IsRunning() == false)
		{
			mTimeWaitSwitch->Start();
		}	
		lockBoard = !mTimeWaitSwitch->IsTimeFinished();
		return mTimeWaitSwitch->IsTimeFinished();
	}
	//----------------------------------------------------------------------------
	bool Board::IntroSequence()
	{
		// Activate each jewel
		introCounter--;
		if (introCounter >= 0)
		{
			mGridContainer[introCounter]->mIsAlive = true;
			return false;
		}
		else return true;
	}
	//----------------------------------------------------------------------------
	void Board::SwapJewels(std::shared_ptr<Jewel>& a, std::shared_ptr<Jewel>& b) const
	{
		// Store each side
		auto temp_a = a;
		auto temp_b = b;
		// Store each position
		glm::vec2 pos_a = temp_b->mGridPosition;
		glm::vec2 pos_b = temp_a->mGridPosition;
		// Switch position
		temp_a->mGridPosition = pos_a;
		temp_b->mGridPosition = pos_b;
		// Switch data
		b = std::move(temp_a);
		a = std::move(temp_b);	
	}

	//----------------------------------------------------------------------------
	void Board::SwapJewels(const int& a, const int& b)
	{
		glm::vec2 pos_a = mGridContainer[a]->mGridPosition;
		glm::vec2 pos_b = mGridContainer[b]->mGridPosition;

		std::shared_ptr<Jewel> temp_a = mGridContainer[a];
		std::shared_ptr<Jewel> temp_b = mGridContainer[b];
		mGridContainer[a]->mGridPosition = pos_b;
		mGridContainer[b]->mGridPosition = pos_a;
	
		std::swap(mGridContainer[a], mGridContainer[b]);
	}
	//----------------------------------------------------------------------------
	bool Board::ResetDeadJewels()
	{
		if (mResetWait->IsRunning() == false)
		{
			mResetWait->Start();
		}
				
		introCounter--;
		if(introCounter >=0)
		{
			if (mGridContainer[introCounter]->mIsAlive == false)
			{
				mGridContainer[introCounter]->mPosition.y = 0.0f;
				mGridContainer[introCounter]->UpdateType(mRandom->GetRangeForJewelType());
				mGridContainer[introCounter]->mIsAlive = true;
			}
			return false;
		} 
		else return true & mResetWait->IsTimeFinished();
	}
	//----------------------------------------------------------------------------
	const int& Board::GetNearestToPoint(const glm::vec2& point) const
	{
		// snap point to grid
		// Initial grid positioning does not care for gridOffset,
		// have to manually remove that from equation
		int x = int((point.x - mGridOffset.x) / GRID_SIZE);
		int y = int((point.y - mGridOffset.y) / GRID_SIZE);
		// convert from xy coords to continuous index
		int index = x + (y * GRID_AXIS_COUNT);
		return index;
	}
	//----------------------------------------------------------------------------
}