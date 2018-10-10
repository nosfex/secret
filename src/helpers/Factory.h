#ifndef _FACTORY_H_
#define _FACTORY_H_
#include <glm/vec2.hpp>
#include <king/Engine.h>
#include "entity/Entity.h"
#include "../Game.h"

class entity::Board;
class entity::Entity;
class entity::GridEntity;
class entity::Jewel;
class Factory
{
	
public:
	
	template <typename T>
	static std::shared_ptr<T> CreateDefaultEntity(const glm::vec2& pos, const King::Engine::Texture& tex)
	{
		std::shared_ptr<T> obj = std::make_shared<T>(pos, tex);
		mContext->AddEntity(obj);
		return obj;
	}

	static Game* mContext;
	 
};
#endif // _FACTORY_H_