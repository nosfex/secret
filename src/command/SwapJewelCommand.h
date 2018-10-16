#ifndef _SWAPJEWELCOMMAND_H_
#define _SWAPJEWELCOMMAND_H_
#include "Command.h"
#include "../entity/Board.h"
class Game;
class SwapJewelCommand : public Command
{
public:
	SwapJewelCommand();
	SwapJewelCommand(const std::shared_ptr<entity::Board>& board);
	virtual ~SwapJewelCommand();
	void Execute(const glm::vec2& inputPosition) override;
	void Undo() override;
private:
	std::shared_ptr<entity::Board> mBoard;
};
#endif // !_SWAPJEWELCOMMAND_H_