#pragma once
#include "Object.h"

struct BulletInfo
{
	float speed;
	float distance;
	float dame;
	float radian;
	vector2f direction;
	vector2f firstPostion;
};
class Bullet : public Object
{
	friend class Player;
	friend class DarkShape;
public:
	Bullet();
	virtual ~Bullet();

	void Init(BulletInfo properties);
	void handleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt) override;
	void update(const float &dt) override;
	void draw() override;

	void setPosition(const vector2f &pos) { m_shapDef.c = pos; }
	vector2f getPosition() { return m_shapDef.c; }

private:
	BulletInfo m_properties;
	bool m_isDone;
};

