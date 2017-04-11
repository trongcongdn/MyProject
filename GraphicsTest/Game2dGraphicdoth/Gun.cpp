#include "Gun.h"
#include "PoolManager.h"
#include "Bullet.h"
#include "random"
#include <SoundManager.h>
Gun::Gun()
{
}


Gun::~Gun()
{
}

void Gun::Init(const GunType& gunType)
{
	switch (gunType)
	{
	case GunType::kPistol:
		_fireRate = 0.425f;
		_spread = 5.0f;
		_bulletSpeed = 1500.0f;
		_bulletDamageMax = 120.0f;
		_bulletDamageMin = 55.0f;
		_maxBullet = 12;
		_maxDistance = 95.0f;
		_minDistance = 85.6f;
		_reloadTime = 2.75f;
		break;
	case GunType::kMachineGun:
		_fireRate = 0.125f;
		_spread = 15.0f;
		_bulletSpeed = 1500.0f;
		_bulletDamageMax = 55.0f;
		_bulletDamageMin = 20.0f;
		_maxBullet = 65;
		_maxDistance = 75.5f;
		_minDistance = 55.75f;
		_reloadTime = 2.97f;
		break;
	case GunType::kShotgun:
		_fireRate = 0.625f;
		_spread = 2.5f;
		_bulletSpeed = 1950.0f;
		_bulletDamageMax = 95.0f;
		_bulletDamageMin = 75.0f;
		_maxBullet = 25;
		_maxDistance = 195.5f;
		_minDistance = 175.75f;
		_reloadTime = 2.6f;
		break;
	case GunType::ksniper:
		_fireRate = 2.9524f;
		_spread = 0.0f;
		_bulletSpeed = 2500.0f;
		_bulletDamageMax = 470.0f;
		_bulletDamageMin = 325.0f;
		_maxBullet = 3;
		_maxDistance = 450.5f;
		_minDistance = 350.75f;
		_reloadTime = 2.45f;
		break;
	case GunType::kRocket:
		_fireRate = 1.3524f;
		_spread = 5.0f;
		_bulletSpeed = 1250.0f;
		_bulletDamageMax = 470.0f;
		_bulletDamageMin = 295.0f;
		_maxBullet = 3;
		_maxDistance = 43.5f;
		_minDistance = 35.75f;
		_reloadTime = 2.85f;
		break;
	default:
		break;
	}
	_maxDistance *= 3;
	_minDistance *= 3;
	_numberBullet = _maxBullet;
	_bulletsPerShot = 1;
	_timeCounter = _fireRate;
	_isDone = false;
	_isShoted = false;
	_isReloading = false;
	_gunType = gunType;
}

void Gun::handleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt)
{
	bool isShot = false;
	if (mouseInput.isPressing && _gunType == GunType::kMachineGun){
		isShot = true;
	}
	if (mouseInput.isRlease){
		if (_gunType == GunType::kMachineGun && _isShoted && !_isReloading)
		{
			SoundManager::getInstance()->stopSound();
			_isShoted = false;
		}
	}
	if (mouseInput.isPress && _gunType != GunType::kMachineGun){
		isShot = true;
	}
	if (isShot)
	{
		if (_timeCounter >= _fireRate && _numberBullet > 0)
		{
			switch (_gunType)
			{
			case GunType::kPistol:
				SoundManager::getInstance()->playSounds("Pistolshot.wav");
				break;
			case GunType::kMachineGun:
				_isShoted = true;
				SoundManager::getInstance()->playSound("MachineGunShot.wav");
				break;
			case GunType::kShotgun:
				SoundManager::getInstance()->playSounds("Shotgunshot.wav");
				break;
			case GunType::ksniper:
				SoundManager::getInstance()->playSounds("SniperShotLoading.wav");
				break;
			case GunType::kRocket:
				break;
			default:
				break;
			}
			static std::mt19937 randomEngine(time(nullptr));
			std::uniform_real_distribution<float> ranDame(_bulletDamageMin, _bulletDamageMax);
			std::uniform_real_distribution<float> ranDistance(_minDistance, _maxDistance);
			std::uniform_real_distribution<float> ranAccuracy(-_spread, _spread);
			auto bullet = PoolManager::getInstance()->m_poolBullets.getElement();
			BulletInfo bulletInfor;
			bulletInfor.dame = ranDame(randomEngine);
			bulletInfor.direction = ((mouseInput.pos - this->m_pos_local).getRotateA(ranAccuracy(randomEngine), vector2f(0.0f, 0.0f))).get_normalize();
			bulletInfor.distance = ranDistance(randomEngine);
			bulletInfor.firstPostion = this->m_pos_local;
			bulletInfor.radian = 2;
			bulletInfor.speed = _bulletSpeed;
			if (bullet)
				bullet->Init(bulletInfor);
			_numberBullet--;
			_timeCounter = 0.0f;
		}
	}
}

void Gun::update(const float &dt)
{
	static float timeloadCurrent = 0.0f;
	static float timedelayCurrent = 0.0f;
	static bool isPlayedreload = false;
	_timeCounter += dt;
	if (_numberBullet <= 0)
	{
		timedelayCurrent += dt;
		if (timedelayCurrent>= _fireRate)
		{
			_isReloading = true;
			if (!isPlayedreload)
			{
				switch (_gunType)
				{
				case GunType::kPistol:
					SoundManager::getInstance()->playSounds("Pistolreload.wav");
					break;
				case GunType::kMachineGun:
					SoundManager::getInstance()->playSounds("Machinegunreloading.wav");
					break;
				case GunType::kShotgun:
					SoundManager::getInstance()->playSounds("Shotgunreloading.wav");
					break;
				case GunType::ksniper:
					SoundManager::getInstance()->playSounds("Sniperreloading.wav");
					break;
				case GunType::kRocket:
					break;
				default:
					break;
				}
				isPlayedreload = true;
			}
			_isShoted = false;
			timeloadCurrent += dt;
			if (timeloadCurrent > _reloadTime)
			{
				_numberBullet = _maxBullet;
				timeloadCurrent = 0.0f;
				timedelayCurrent = 0.0f;
				isPlayedreload = false;
				_isReloading = false;
			}
		}
		
		
	}
}

void Gun::draw()
{}