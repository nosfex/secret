#include "Jewel.h"
#include "../helpers/HelperMath.h"
#include <iostream>
namespace entity
{
	//-----------------------------------------------------------------------------
	Jewel::Jewel() : Entity()
	{
		mDropSpeed = 0.0f;
	}
	//-----------------------------------------------------------------------------
	Jewel::Jewel(const glm::vec2 pos, const King::Engine::Texture& tex) :Entity(pos, tex)
	{
		mDropSpeed = 0.0f;
	}
	//-----------------------------------------------------------------------------
	Jewel::Jewel(const Jewel& other) :Entity(other)
	{
		UpdateType(other.GetType());
		mDropSpeed = 0.0f;
	}
	//-----------------------------------------------------------------------------
	Jewel::~Jewel()
	{
	}
	//-----------------------------------------------------------------------------
	void Jewel::Update()
	{
		Entity::Update();
	}
	//-----------------------------------------------------------------------------
	void Jewel::Update(const float& dt)
	{
		Update();
		
		mPosition = HelperMath::Lerp(mPosition, mGridPosition, mDropSpeed * dt);
	}
	//-----------------------------------------------------------------------------
	void Jewel::UpdateType(const JewelType& type)
	{
		mType = type;
		switch (mType)
		{
			case JewelType::BLUE:
				SetTexture(King::Engine::Texture::TEXTURE_BLUE);
			break;
			case JewelType::GREEN:
				SetTexture(King::Engine::Texture::TEXTURE_GREEN);
			break;
			case JewelType::PURPLE:
				SetTexture(King::Engine::Texture::TEXTURE_PURPLE);
			break;
			case JewelType::RED:
				SetTexture(King::Engine::Texture::TEXTURE_RED);
			break;
			case JewelType::YELLOW:
				SetTexture(King::Engine::Texture::TEXTURE_YELLOW);
			break;
		}
	}
	//-----------------------------------------------------------------------------
}