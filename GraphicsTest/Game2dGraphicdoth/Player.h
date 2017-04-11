#pragma once
#include "Object.h"

class Gun;

class Player :
	public Object
{
public:
	Player(vector2f pos = (0.0f, 0.0f), float speed = 0.0f, float hp = 0.0f);
	virtual ~Player();

	void Init() override;
	void handleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt) override;
	void update(const float &dt) override;
	void draw() override;
	void detroy() override;

	void setPosition(const vector2f &pos) {
		m_shapDef.c = pos;
	}
	vector2f getPosition() { return m_shapDef.c; }

	void setHp(const float &hp){
		m_hp = hp;
	}
	float getHp() { return m_hp; }

private:
	float m_hp;
	std::vector<Gun> m_guns;
	Gun* m_gunCurrent;
};

