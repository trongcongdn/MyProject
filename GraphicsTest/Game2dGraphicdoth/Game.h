#pragma once
#include <chrono>
#include "State.h"

const unsigned int FPS = 32;

class Game
{
public:
	Game();
	~Game();
	void Init();
	void run();
	void Detroy();

	static MouseInput m_mouseInput;

private:
	void setInput();
	bool checkNewState();
	bool m_isRunning;
	std::chrono::time_point<std::chrono::system_clock> m_lastTime;
	std::chrono::time_point<std::chrono::system_clock> m_currentTime;
	State *m_currentState;
	KeyInput m_keyInput;
};

