#ifndef _BOARD_H_
#define _BOARD_H_
#include "Entity.h"
#include <vector>
#include <memory>
#include <king/Engine.h>
#include <iostream>
#include "../helpers/HelperRandom.h"
#include "../helpers/HelperMath.h"
#include "Jewel.h"
namespace entity
{
	struct GridData
	{
	public:
		int mIndex;
		JewelType mCurrentType;

		std::shared_ptr<Jewel> mJewelRef;
	};
	class GridEntity : public Entity
	{
	public:
		GridEntity() {}
		GridEntity(const glm::vec2& pos, const King::Engine::Texture& tex) :Entity(pos, tex){}

		
	};
	class Board : public Entity
	{
	public:
		Board();
		Board(const glm::vec2& pos, const King::Engine::Texture& tex);
	//	Board(const Board& other) = delete;
		virtual ~Board();
		
		void Start(const glm::vec2& offset = glm::vec2(0.0f, 0.0f));
		void Update() override;
		void Update(const float &dt) override;
		void ScrambleBoard();
		void CheckVerticalLine(const int startidx);
		void CheckHorizontalLine(const int startidx);
		void ClearLine(const std::vector<GridData>& line) const;
		void Cleanup();
		static const int GRID_AXIS_COUNT = 8;
		static const float GRID_SIZE;
	private:
		std::vector<GridData> mGridContainer;
		glm::vec2 mGridOffset;

		std::unique_ptr<HelperRandom> mRandom;
		float maxSequenceTimer;
		float currentSequenceTimer;
		//int introCounter;
		const bool IntroSequence() const;
	};
}
#endif // !_BOARD_H_