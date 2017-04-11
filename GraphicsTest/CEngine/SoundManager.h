#pragma once
#include <string>
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	static SoundManager* _instance;
	static SoundManager* getInstance();
	static void detroyInstance();
	void playSound(std::string fileName);
	void playSounds(std::string fileName);
	void stopSound();
private:
	void init();
	std::string m_gamePath;
};

