#include "Game.h"
#include "graphics.h"
#include <ctime>
#include "GameMenuState.h"
#include "GamePlayState.h"
#include "GameOverState.h"
#include "HighSoccerState.h"
#include "ScreenInfor.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

MouseInput Game::m_mouseInput;

Game::Game()
	:m_isRunning(true), m_lastTime(std::chrono::system_clock::now()), m_currentState(nullptr)
{
}


Game::~Game()
{
}

void mouseLeftDown(int x, int y)
{
	Game::m_mouseInput.pos.x = x;
	Game::m_mouseInput.pos.y = y;
	Game::m_mouseInput.isPress = true;
	Game::m_mouseInput.isPressing = true;
}

void mouseLeftUp(int x, int y)
{
	Game::m_mouseInput.pos.x = x;
	Game::m_mouseInput.pos.y = y;
	Game::m_mouseInput.isRlease = true;
	Game::m_mouseInput.isPressing = false;
}
void mouseMove(int x, int y)
{
	Game::m_mouseInput.pos.x = x;
	Game::m_mouseInput.pos.y = y;
	Game::m_mouseInput.isMoving = true;
}

void Game::Init()
{
	initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DarkSharp", 10, 20);
	registermousehandler(WM_LBUTTONDOWN, mouseLeftDown);
	registermousehandler(WM_MOUSEMOVE, mouseMove);
	registermousehandler(WM_LBUTTONUP, mouseLeftUp);
	setcolor(RED);
	srand(time(NULL));
	m_currentState = new GamePlayState();
	m_currentState->Init();
}
void Game::run()
{
	int page1 = 0, page2 = 1;
	float dt = 0.0f;
	float SPF = 1.0f / FPS;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
	while (m_isRunning)
	{
		setvisualpage(page1);
		setactivepage(page2);
		cleardevice();
		start = m_currentTime = std::chrono::system_clock::now();
		elapsed_seconds = m_currentTime - m_lastTime;
		dt = elapsed_seconds.count();
		m_lastTime = m_currentTime;
		setInput();
		m_currentState->HandleInput(m_mouseInput, m_keyInput, dt);
		m_mouseInput.resetInput();
		m_currentState->Update(dt);
		if (checkNewState())
			continue;
		m_currentState->Draw();
		page1 = 1 - page1;
		page2 = 1 - page2;
		end = m_currentTime = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		if (elapsed_seconds.count() < SPF)
		{
			delay((SPF - elapsed_seconds.count()) * 1000);
		}
	}
}
void Game::setInput()
{
	if (GetAsyncKeyState(kcA))
		m_keyInput.a_is_press = true;
	else
		m_keyInput.a_is_press = false;
	if (GetAsyncKeyState(kcS))
		m_keyInput.s_is_press = true;
	else
		m_keyInput.s_is_press = false;
	if (GetAsyncKeyState(kcD))
		m_keyInput.d_is_press = true;
	else
		m_keyInput.d_is_press = false;
	if (GetAsyncKeyState(kcW))
		m_keyInput.w_is_press = true;
	else
		m_keyInput.w_is_press = false;
	if (GetAsyncKeyState(kcF))
	{
		m_keyInput.a_is_press = true;
		m_keyInput.f_is_release = false;
	}
	else
	{
		m_keyInput.f_is_release = false;
		if (m_keyInput.f_is_press)
			m_keyInput.f_is_release = true;
		m_keyInput.f_is_press = false;
	}
	if (GetAsyncKeyState(kcG))
	{
		m_keyInput.g_is_press = true;
		m_keyInput.g_is_release = false;
	}
	else
	{
		m_keyInput.g_is_release = false;
		if (m_keyInput.g_is_press)
			m_keyInput.g_is_release = true;
		m_keyInput.g_is_press = false;
	}
}
bool Game::checkNewState()
{
	StateType changeState = m_currentState->isChangeState();
	if (changeState != StateType::kNone)
	{
		delete m_currentState;
		m_currentState = nullptr;
		switch (changeState)
		{
		case StateType::kGameMenu:
			//m_currentState = new GameMenuState();
			break;
		case StateType::kGamePlay:
			m_currentState = new GamePlayState();
			break;
		case StateType::kGameOver:
			//m_currentState = new GameOverState();
			break;
		case StateType::kHighSoccer:
			//m_currentState = new HighSoccerState();
			break;
		default:
			break;
		}
		if (m_currentState)
		{
			m_currentState->Init();
			return true;
		}
		else
			m_isRunning = false;
	}
	return false;
}
void Game::Detroy()
{

}
