#include "DarkShape.h"
#include <random>
#include "Player.h"
#include "GamePlayState.h"
#include "PoolManager.h"
#include "Bullet.h"

DarkShape::DarkShape(vector2f pos, float speed, float hp)
	:Object(pos, speed), m_hp(hp)
{
	m_shapDef.Vertexs.resize(MAX_SIZE_VERTEX);
	m_lastPosVer.resize(MAX_SIZE_VERTEX);
}


DarkShape::~DarkShape()
{
}

void DarkShape::Init(){
	static std::mt19937 randomEngine((unsigned int) time(nullptr));
	std::uniform_int_distribution<int> randShap(0, 1);
	std::uniform_int_distribution<int> randVern(MIN_SIZE_VERTEX, MAX_SIZE_VERTEX);
	std::uniform_real_distribution<float> randPos(0.1f, 0.9f);
	std::uniform_real_distribution<float> randSize(0.0035f, 0.015f);
	std::uniform_real_distribution<float> randPosNext(-0.025f, 0.025f);
	m_shapDef.type = (MathHelper::ShapeType) randShap(randomEngine);
	m_shapDef.n = randVern(randomEngine);
	if (m_shapDef.type == MathHelper::ShapeType::kPolygon)
	{
		m_shapDef.Vertexs[0].x = SCREEN_WIDTH * randPos(randomEngine);
		m_shapDef.Vertexs[0].y = SCREEN_HEIGHT * randPos(randomEngine);
		float maxX, minX, maxY, minY;
		maxX = minX = m_shapDef.Vertexs[0].x;
		maxY = minY = m_shapDef.Vertexs[0].y;
		for (int i = 1; i < m_shapDef.n; i++)
		{
			m_shapDef.Vertexs[i].x = m_shapDef.Vertexs[i - 1].x + randPosNext(randomEngine) / 2.0f * SCREEN_WIDTH;
			m_shapDef.Vertexs[i].y = m_shapDef.Vertexs[i - 1].y + randPosNext(randomEngine) / 2.0f * SCREEN_HEIGHT;
			if (maxX < m_shapDef.Vertexs[i].x)
			{
				maxX = m_shapDef.Vertexs[i].x;
			}
			else if (minX > m_shapDef.Vertexs[i].x)
			{
				minX = m_shapDef.Vertexs[i].x;
			}

			if (maxY < m_shapDef.Vertexs[i].y)
			{
				maxY = m_shapDef.Vertexs[i].y;
			}
			else if (minY > m_shapDef.Vertexs[i].y)
			{
				minY = m_shapDef.Vertexs[i].y;
			}
		}
		m_shapDef.c.x = (maxX - minX) / 2.0f + minX;
		m_shapDef.c.y = (maxY - minY) / 2.0f + minY;
		m_lastPosVer = m_shapDef.Vertexs;
		m_lastPosC = m_shapDef.c;
	}
	else
	{
		m_shapDef.c.x = SCREEN_WIDTH * randPos(randomEngine);
		m_shapDef.c.y = SCREEN_HEIGHT * randPos(randomEngine);
		m_shapDef.r = SCREEN_WIDTH * randSize(randomEngine);
		m_lastPosC = m_shapDef.c;
	}
	m_speed = 20;
	m_hp = 200;
}

void DarkShape::handleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt){
}

void DarkShape::goBack(){
	if (m_shapDef.type == MathHelper::ShapeType::kPolygon)
	{
		m_shapDef.Vertexs = m_lastPosVer;
		m_shapDef.c = m_lastPosC;
	}
	else
	{
		m_shapDef.c = m_lastPosC;
	}
}

void DarkShape::update(const float &dt){
	vector2f playerPos = GamePlayState::getPlayer()->getPosition();
	if (m_shapDef.type == MathHelper::ShapeType::kPolygon)
	{
		m_lastPosVer = m_shapDef.Vertexs;
		m_lastPosC = m_shapDef.c;
		vector2f v = vector2f::normalize_vector2f(playerPos - m_shapDef.c) * m_speed * dt;
		for (int i = 0; i < m_shapDef.n; i++)
		{
			m_shapDef.Vertexs[i] += v;
		}
		m_shapDef.c += v;
	}
	else
	{
		m_lastPosC = m_shapDef.c;
		vector2f v = vector2f::normalize_vector2f(playerPos - m_shapDef.c) * m_speed * dt;
		m_shapDef.c += v;
	}
	for (auto bullet : PoolManager::getInstance()->m_poolBullets.getListInUse()){
		if (this->m_shapDef.containtLine(bullet->m_properties.firstPostion, bullet->getPosition())){
			PoolManager::getInstance()->m_poolDarkShapes.setElement(this);
			PoolManager::getInstance()->m_poolBullets.setElement(bullet);
			break;
		}
	}
}

void DarkShape::draw(){
	if (m_shapDef.type == MathHelper::ShapeType::kPolygon)
	{
		for (int i = 0; i < m_shapDef.n - 1; i++)
		{
			line(m_shapDef.Vertexs[i].x, m_shapDef.Vertexs[i].y, m_shapDef.Vertexs[i + 1].x, m_shapDef.Vertexs[i + 1].y);
		}
		line(m_shapDef.Vertexs[m_shapDef.n - 1].x, m_shapDef.Vertexs[m_shapDef.n - 1].y, m_shapDef.Vertexs[0].x, m_shapDef.Vertexs[0].y);
	}
	else
	{
		circle(m_shapDef.c.x, m_shapDef.c.y, m_shapDef.r);
	}
}