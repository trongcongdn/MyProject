#pragma once
#include "Object.h"
const int MIN_SIZE_VERTEX = 3;
const int MAX_SIZE_VERTEX = 8;
class Player;
class DarkShape :
	public Object
{
public:
	DarkShape(vector2f pos = (0.0f, 0.0f), float speed = 0.0f, float hp = 0.0f);
	virtual ~DarkShape();

	void Init() override;
	void handleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt) override;
	void update(const float &dt, Player *player);
	void draw() override;

	/*void setPosition(const vector2f &pos) {
		m_circleDef.c = pos;
	}
	vector2f getPosition() { return m_circleDef.c; }*/

	void goBack();

	void setHp(const float &hp){
		m_hp = hp;
	}
	float getHp() { return m_hp; }

private:
	float m_hp;
	std::vector<vector2f> m_lastPosVer;
	vector2f m_lastPosC;
};

