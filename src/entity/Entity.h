#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <king/Updater.h>
#include <glm/vec2.hpp>
#include "Drawable.h"
namespace entity
{
	
	class Entity : public King::Updater, public entity::Drawable
	{
	public:
		Entity();
		Entity(const glm::vec2 pos, const King::Engine::Texture& tex);
		Entity(const Entity& other);
		virtual ~Entity() = default;

		virtual void Update() override {}
		virtual void Update(const float &dt) { Update(); }
		virtual const King::Engine::Texture& GetTexture() const override;
		virtual void SetTexture(const King::Engine::Texture& tex) override;

		glm::vec2 mPosition;
		bool mIsAlive;
	protected:
		King::Engine::Texture mTexture;
	};
}
#endif // _ENTITY_H_