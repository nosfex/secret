#include "SwapJewelCommand.h"
#include "../Game.h"
SwapJewelCommand::SwapJewelCommand()
{}

SwapJewelCommand::SwapJewelCommand(const std::shared_ptr<entity::Board>& board)
{
	mBoard = board;
}

SwapJewelCommand::~SwapJewelCommand()
{

}

void SwapJewelCommand::Execute(const glm::vec2& inputPosition)
{
	mBoard->ProcessUserSwap(inputPosition);
}

void SwapJewelCommand::Undo()
{
}