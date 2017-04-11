#pragma once
#include "Object.h"

enum class GunType
{
	kPistol,
	kMachineGun,
	kShotgun,
	ksniper,
	kRocket
};
class Gun : public Object
{
public:
	Gun();
	~Gun();


	void Init(const GunType& gunType);
	void handleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt) override;
	void update(const float &dt) override;
	void draw() override;
private:

	float _fireRate;
	float _bulletsPerShot;
	float _spread;
	float _bulletSpeed;
	float _bulletDamageMax;
	float _bulletDamageMin;
	int _maxBullet;
	int _numberBullet;
	float _maxDistance;
	float _minDistance;
	float _timeCounter;
	float _reloadTime;
	bool _isDone;

	bool _isShoted;
	bool _isReloading;
	GunType _gunType;
};
