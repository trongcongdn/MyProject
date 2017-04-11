#pragma once
#include <vector>
#include <list>
class DarkShape;
class Bullet;

template <class P> class Pool
{
public:
	friend class PoolManager;
	Pool();
	~Pool();
	void init(const int &sizePool);
	void detroy();
	std::list<P*> getListInUse(){
		return m_PoolInUse;
	}
	P* getElement()
	{
		if (m_PoolNotInUse.size() == 0)
			return nullptr;
		P* tmp = m_PoolNotInUse.front();
		m_PoolNotInUse.pop_front();
		m_PoolInUse.emplace_back(tmp);
		return tmp;
	}
	void setElement(P* p){
		m_PoolInUse.remove(p);
		m_PoolNotInUse.emplace_back(p);
	}
	unsigned int size() { return m_size; }
private:
	std::vector<P> m_pool;
	std::list<P*> m_PoolInUse;
	std::list<P*> m_PoolNotInUse;
	unsigned int m_size;
};

class PoolManager
{
public:
	friend class GamePlayState;
	friend class Player;
	friend class DarkShape;
	friend class Bullet;
	friend class Gun;

	PoolManager();
	virtual ~PoolManager();

	static PoolManager* _instance;
	static PoolManager* getInstance();
	static void detroyInstance();

private:
	void initPool();
	void detroyPool();
	void update(const float &dt);
	void draw();

	Pool<DarkShape> m_poolDarkShapes;
	Pool<Bullet> m_poolBullets;
};

