#include "PoolManager.h"
#include "DarkShape.h"
#include "Bullet.h"

PoolManager* PoolManager::_instance = nullptr;

PoolManager::PoolManager()
{
}


PoolManager::~PoolManager()
{
	detroyPool();
}

PoolManager* PoolManager::getInstance(){
	if (!_instance)
	{
		_instance = new PoolManager();
		_instance->initPool();
		return _instance;
	}
	return _instance;
}
void PoolManager::detroyInstance(){
	if (_instance)
	{
		_instance->detroyPool();
		delete _instance;
	}
	_instance = nullptr;
}

void PoolManager::initPool(){
	m_poolDarkShapes.init(20);
	m_poolBullets.init(200);
}

void PoolManager::update(const float &dt){
	for (auto shape : m_poolDarkShapes.getListInUse())
	{
		shape->update(dt);
	}
	for (auto bullet : m_poolBullets.getListInUse())
	{
		bullet->update(dt);
	}

	std::list<DarkShape*>::iterator ipointer = m_poolDarkShapes.m_PoolInUse.begin();
	std::list<DarkShape*>::iterator jpointer;
	int sizePool = m_poolDarkShapes.getListInUse().size();
	for (unsigned int i = 0; i < sizePool - 1; i++)
	{
		auto tmp = ipointer;
		ipointer++;
		jpointer = ipointer;
		ipointer = tmp;
		for (unsigned int j = i + 1; j < sizePool; j++)
		{
			if ((*ipointer)->getSharpDef().collisionWithShape((*jpointer)->getSharpDef()))
			{
				(*ipointer)->goBack();
			}
			jpointer++;
		}
		ipointer++;
	}
}

void PoolManager::draw(){
	for (auto shape : m_poolDarkShapes.getListInUse())
	{
		shape->draw();
	}
	for (auto bullet : m_poolBullets.getListInUse())
	{
		bullet->draw();
	}
}

void PoolManager::detroyPool(){
	m_poolDarkShapes.detroy();
	m_poolBullets.detroy();
}

template <class P> Pool<P>::Pool()
	:m_size(0)
{
}

template <class P> Pool<P>::~Pool()
{
	detroy();
}

template <class P> void Pool<P>::init(const int &sizePool){
	m_size = sizePool;
	m_pool.resize(sizePool);
	for (unsigned int i = 0; i < m_pool.size(); i++)
	{
		m_PoolNotInUse.push_back(&(m_pool[i]));
	}
}
template <class P> void Pool<P>::detroy(){
	m_pool.clear();
	m_PoolNotInUse.clear();
	m_PoolInUse.clear();
}

//template <class P> P* Pool<P>::getElement(){
	//if (m_PoolNotInUse.size() == 0)
		//return nullptr;
	//P* tmp = m_PoolNotInUse.front();
	//m_PoolNotInUse.pop_front();
	//m_PoolInUse.emplace_back(tmp);
	//return tmp;
//}

//template <class P> void Pool<P>::setElement(P* p){
//	m_PoolInUse.remove(p);
//	m_PoolNotInUse.emplace_back(p);
//}