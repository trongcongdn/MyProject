#include "Bullet.h"
#include "PoolManager.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}


void Bullet::Init(BulletInfo properties){
	m_properties = properties;
	m_shapDef.c = properties.firstPostion;
	m_shapDef.r = properties.radian;
	m_isDone = false;
}

void Bullet::handleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt){
}

void Bullet::update(const float &dt){
	if (!m_isDone)
	{
		if (m_shapDef.c.distance_square_with(m_properties.firstPostion) < m_properties.distance * m_properties.distance){
			m_shapDef.c += m_properties.direction * m_properties.speed * dt;
		}
		else{
			PoolManager::getInstance()->m_poolBullets.setElement(this);
			m_isDone = true;
		}
	}
	else
	{
		PoolManager::getInstance()->m_poolBullets.setElement(this);
	}
}

void Bullet::draw(){
	circle(m_shapDef.c.x, m_shapDef.c.y, m_shapDef.r);
}