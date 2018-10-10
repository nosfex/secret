#include "Entity.h"
namespace entity
{
	//-----------------------------------------------------------------------------
	Entity::Entity() : mPosition({0.0f}), mTexture(King::Engine::Texture::TEXTURE_BLUE)
	{
	}
	//-----------------------------------------------------------------------------
	Entity::Entity(const glm::vec2 _pos, const King::Engine::Texture& _tex) : mPosition(_pos), mTexture(_tex), mIsAlive(true)
	{
	}
	//-----------------------------------------------------------------------------
	Entity::Entity(const Entity& other)
	{
		mPosition = other.mPosition;
		mTexture = other.mTexture;
		mIsAlive = other.mIsAlive;
	}
	//-----------------------------------------------------------------------------
	//Entity::~Entity()
	//{
	//}
	//-----------------------------------------------------------------------------
	const King::Engine::Texture& Entity::GetTexture() const
	{
		return mTexture;
	}
	//-----------------------------------------------------------------------------
	void Entity::SetTexture(const King::Engine::Texture& _tex)
	{
		mTexture = _tex;
	}
	//-----------------------------------------------------------------------------
}