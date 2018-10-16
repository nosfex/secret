#ifndef _GAME_H_
#define _GAME_H_

#include <king/Engine.h>
#include <king/Updater.h>
#include <vector>
#include "entity/Entity.h"
#include "entity/Board.h"
class SwapJewelCommand;
class Factory;
class Game : public King::Updater
{
public:
	Game();
	Game(const Game & other) = delete;
	virtual ~Game();
	void Start();
	void Update() override;
	void AddEntity(const std::shared_ptr<entity::Entity>& ent);
	void CheckAlive();
private:
	King::Engine mEngine;
	std::shared_ptr<entity::Board> mBoard;
	std::vector< std::shared_ptr<entity::Entity>> mEntityContainer;
	
	std::unique_ptr<SwapJewelCommand> mSwapCommand;
	static const int mEntityBuffer = 3;
};
#endif //_GAME_H_