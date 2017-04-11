#include "Player.h"
#include "PoolManager.h"
#include<random>
#include "Bullet.h"
#include "Gun.h"

Player::Player(vector2f pos, float speed, float hp)
	:Object(pos, speed), m_hp(hp)
{
}


Player::~Player()
{
	detroy();
}

void Player::detroy()
{
	m_guns.clear();
}

void Player::Init(){
	m_shapDef.c.x = SCREEN_WIDTH / 2.0f;
	m_shapDef.c.y = SCREEN_HEIGHT / 2.0f;
	m_shapDef.r = SCREEN_WIDTH*0.01;
	m_speed = 100;
	m_hp = 100;
	m_guns.resize(4);
	for (unsigned int i = 0; i < m_guns.size(); i++)
	{
		m_guns[i].Init((GunType)i);
	}
	m_gunCurrent = &m_guns[0];
}

void Player::handleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt){
	if (keyInput.a_is_press)
	{
		m_shapDef.c.x += -m_speed * dt;
	}
	if (keyInput.d_is_press)
	{
		m_shapDef.c.x += m_speed * dt;
	}
	if (keyInput.w_is_press)
	{
		m_shapDef.c.y += -m_speed * dt;
	}
	if (keyInput.s_is_press)
	{
		m_shapDef.c.y += m_speed * dt;
	}
	if (keyInput.g_is_release)
	{
		static unsigned int indexGun = 0;
		indexGun++;
		if (indexGun>=m_guns.size())
		{
			indexGun = 0;
		}
		m_gunCurrent = &m_guns[indexGun];
	}
	m_gunCurrent->handleInput(mouseInput, keyInput, dt);
}

void Player::update(const float &dt){
	m_gunCurrent->setPosition(this->m_shapDef.c);
	m_gunCurrent->update(dt);
}

void Player::draw(){
	circle(m_shapDef.c.x, m_shapDef.c.y, m_shapDef.r);
}