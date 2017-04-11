#pragma once
#include <vector2.h>
#include "InputManger.h"
#include <MathHelper.h>
#include "ScreenInfor.h"
#include <vector>
#include <ctime>
#include "graphics.h"
class Object
{
public:
	Object(vector2f pos = (0.0f,0.0f), float speed = 0.0f);
	virtual ~Object();

	virtual void Init() {};
	virtual void handleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt) {};
	virtual void update(const float &dt) {};
	virtual void draw() {};
	virtual void detroy() {};

	virtual void setPosition(const vector2f &pos){ m_pos_local = pos;}
	virtual vector2f getPosition() { return m_pos_local; }
	virtual void setSpeed(const float &speed){ m_speed = speed; }
	virtual float getSpeed() { return m_speed; }

	MathHelper::ShapeDef getSharpDef() const { return m_shapDef; }

protected:
	vector2f m_pos_local;
	vector2f m_pos_gobal;
	float m_speed;
	std::vector<Object> children;
	MathHelper::ShapeDef m_shapDef;
};

