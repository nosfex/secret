#include "Game.h"
#include "helpers/Factory.h"
//-----------------------------------------------------------------------------
Game::Game() : mEngine("./assets")
{
}
//-----------------------------------------------------------------------------
Game::~Game()
{
}
//-----------------------------------------------------------------------------
void Game::Start()
{
	Factory::mContext = this;

	mBoard = Factory::CreateDefaultEntity<entity::Board>(glm::vec2(22.5f, 0.0f), King::Engine::Texture::TEXTURE_BACKGROUND);
	mEntityContainer.reserve((entity::Board::GRID_AXIS_COUNT * entity::Board::GRID_AXIS_COUNT) * mEntityBuffer );
	glm::vec2 boardOffset = glm::vec2(22.5f + entity::Board::GRID_SIZE * 10, entity::Board::GRID_SIZE * 3);
	mBoard->Start(boardOffset);
	mBoard->Cleanup();
	mEngine.Start(*this);
}
//-----------------------------------------------------------------------------
void Game::Update()
{
	for (size_t i = 0; i < mEntityContainer.size() ; i++)
	{
		if (mEntityContainer[i]->mIsAlive)
		{
			mEntityContainer[i]->Update(mEngine.GetLastFrameSeconds());
			mEngine.Render(mEntityContainer[i]->GetTexture(),
				mEntityContainer[i]->mPosition.x,
				mEntityContainer[i]->mPosition.y);
		}
	}
}
//-----------------------------------------------------------------------------
void Game::AddEntity( const std::shared_ptr<entity::Entity>& ent)
{
	mEntityContainer.push_back(ent);
}
//-----------------------------------------------------------------------------
void Game::CheckAlive()
{
	std::vector<int> removeIndices;
	for (size_t i = 0; i < mEntityContainer.size() ; i++)
	{
		if (mEntityContainer[i]->mIsAlive == false)
		{
			removeIndices.push_back(i);
		}
	}

	for (auto idx : removeIndices)
	{
		mEntityContainer.erase(mEntityContainer.begin() + idx);
	}
}
//-----------------------------------------------------------------------------