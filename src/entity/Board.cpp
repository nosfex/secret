#include "Board.h"
#include "helpers/Factory.h"
#include <windows.h>
namespace entity
{
	const float Board::GRID_SIZE = 36.0f;
	Board::Board():Entity()
	{}
	Board::Board(const glm::vec2& pos, const King::Engine::Texture& tex): Entity(pos, tex)
	{
	}
	Board::~Board()
	{
	}
	void Board::Start(const glm::vec2& offset)
	{
		mRandom = std::make_unique<HelperRandom>();
		mGridOffset = offset;
		size_t maxGrids = GRID_AXIS_COUNT * GRID_AXIS_COUNT;
		mGridContainer.reserve(maxGrids);
		std::cout << "MAX GRIDS: " << maxGrids << std::endl;
		for (size_t i = 0; i < maxGrids; i++)
		{
			int y = i / GRID_AXIS_COUNT;
			int x = i % GRID_AXIS_COUNT;
			(Factory::CreateDefaultEntity<GridEntity>({ offset.x + (GRID_SIZE * x), offset.y + (GRID_SIZE * y)}, King::Engine::Texture::TEXTURE_GRID));
			std::shared_ptr<entity::Jewel> jewel = (Factory::CreateDefaultEntity<Jewel>({ offset.x + (GRID_SIZE * x), 0.0f }, King::Engine::Texture::TEXTURE_BLUE));
			JewelType type = /*(x > 3) ? JewelType::RED : JewelType::YELLOW */mRandom->GetRangeForJewelType();
		/*	if (x == 4)
			{
				type = JewelType::BLUE;
			}*/
				jewel->UpdateType(type);
			jewel->mGridPosition = { offset.x + (GRID_SIZE * x), offset.y + (GRID_SIZE * y) };
			jewel->mDropSpeed += 2.0f;
			mGridContainer.push_back({ int(i), type, (jewel)});
			jewel->mIsAlive = false;
		}		
		maxSequenceTimer = 0.05120f;
		currentSequenceTimer = 0.0f;
		
	}
	void Board::Update()
	{
	
	}
	void Board::Update(const float& dt)
	{
	//	Update();
		currentSequenceTimer += dt;
		if (currentSequenceTimer >= maxSequenceTimer && IntroSequence())
		{
			currentSequenceTimer = 0.0f;
		}
		if (IntroSequence() == false)
		{
		//	Sleep(5000);
			if (mGridContainer[0].mJewelRef->mIsAlive)
			{
				CheckVerticalLine(0);
				mGridContainer[0].mJewelRef->mIsAlive = false;
			}
		}
	}
	void Board::ScrambleBoard()
	{
	}
	
	void Board::CheckVerticalLine(const int startidx)
	{	
		TODOFIXME
		std::vector<GridData> clear;
		clear.reserve(GRID_AXIS_COUNT);
		GridData pivot = mGridContainer[startidx];
		int max = (GRID_AXIS_COUNT);
		int next = 0;
		while (next < max)
		{
			GridData header = mGridContainer[startidx + (next * GRID_AXIS_COUNT)];
			next++;
			if (pivot.mCurrentType == header.mCurrentType)
			{
				clear.push_back(header);
				if (next == max)
				{
					ClearLine(clear);
					clear.clear();
				}
			}
			else
			{
				ClearLine(clear);
				clear.clear();
				next = header.mIndex;
				pivot = header;
			}
		}
		if (startidx + 1 < (GRID_AXIS_COUNT))
		{
			CheckVerticalLine(startidx + 1);
		}
	}

	void Board::CheckHorizontalLine( const int startidx)
	{
		int next = startidx;
		std::vector<GridData> clear;
		clear.reserve(GRID_AXIS_COUNT);
		GridData pivot = mGridContainer[startidx];
		int max = (GRID_AXIS_COUNT + startidx);
		while (next < max)
		{
			GridData header = mGridContainer[next];
			next++;
			if (pivot.mCurrentType == header.mCurrentType)
			{
				clear.push_back(header);
				if (next == max)
				{
					ClearLine(clear);
					clear.clear();
				}
			}
			else
			{
				ClearLine(clear);
				clear.clear();
				next = header.mIndex;
				pivot = header;
			}	 	
		}
		if (max < (GRID_AXIS_COUNT * GRID_AXIS_COUNT))
		{
			CheckHorizontalLine(max);
		}
	}
	
	void Board::ClearLine(const std::vector<GridData>& line) const
	{
		if (line.size() >= 3)
		{
			for (auto g : line)
			{
				g.mJewelRef->mIsAlive = false;
			}
		}
	}
	void Board::Cleanup()
	{
		std::cout << "cleanup" << std::endl;
		for (auto container : mGridContainer)
		{
		}
		mGridContainer.erase(mGridContainer.begin(), mGridContainer.end());
	}

	const bool Board::IntroSequence() const
	{
		static int introCounter = 64;
		introCounter--;
		if (introCounter >= 0)
		{
			mGridContainer[introCounter].mJewelRef->mIsAlive = true;
			return true;
		}
		else return false;
	
		//return true;
	}
}