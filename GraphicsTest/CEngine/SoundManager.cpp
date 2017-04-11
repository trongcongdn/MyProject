#include "SoundManager.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

SoundManager* SoundManager::_instance = nullptr;

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

SoundManager* SoundManager::getInstance(){
	if (!_instance)
	{
		_instance = new SoundManager();
		_instance->init();
		return _instance;
	}
	return _instance;
}

void SoundManager::detroyInstance(){
	if (_instance)
	{
		delete _instance;
	}
	_instance = nullptr;
}

void SoundManager::init()
{
	char gamePath[_MAX_PATH + 1];
	GetModuleFileName(NULL, gamePath, _MAX_PATH);
	std::string appName = "Game2dGraphicdoth.exe";
	std::string PathStr = gamePath;
	
	auto f = PathStr.find(appName);
	if (f != std::string::npos)
	{
		m_gamePath = PathStr.substr(0, f);
	}
	m_gamePath += "\\data\\";
}

void SoundManager::playSound(std::string fileName)
{
	static std::string filePath;
	filePath = m_gamePath + fileName;
	PlaySoundA((LPCSTR)filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}

void SoundManager::playSounds(std::string fileName)
{
	static std::string filePath;
	filePath = m_gamePath + fileName;
	PlaySoundA((LPCSTR)filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void SoundManager::stopSound()
{
	PlaySoundA(NULL, NULL, SND_ASYNC);
}