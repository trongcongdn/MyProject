#include "GamePlayState.h"
#include "graphics.h"
#include "Player.h"
#include "DarkShape.h"
#include "PoolManager.h"
#include "Bullet.h"

Player * GamePlayState::m_player = nullptr;

GamePlayState::GamePlayState()
{
}


GamePlayState::~GamePlayState()
{
	Detroy();
}

void GamePlayState::Init()
{
	m_player = new Player();
	m_player->Init();
	DarkShape *darkShape;
	for (size_t i = 0; i < PoolManager::getInstance()->m_poolDarkShapes.size(); i++)
	{
		darkShape = PoolManager::getInstance()->m_poolDarkShapes.getElement();
		if (darkShape)
			darkShape->Init();
	}
}

void GamePlayState::HandleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt)
{
	m_player->handleInput(mouseInput, keyInput, dt);
}

void GamePlayState::Update(const float &dt)
{
	m_player->update(dt);
	PoolManager::getInstance()->update(dt);
}

void GamePlayState::Draw()
{
	m_player->draw();
	PoolManager::getInstance()->draw();
}

void GamePlayState::Detroy()
{
	delete m_player;
	PoolManager::detroyInstance();
}