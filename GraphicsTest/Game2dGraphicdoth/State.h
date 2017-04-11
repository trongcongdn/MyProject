#pragma once
#include <Vector2.h>
#include "InputManger.h"

enum class StateType
{
	kNone,
	kGameMenu,
	kGamePlay,
	kGameOver,
	kHighSoccer
};

class State
{
public:
	State();
	virtual ~State();
	virtual void Init() = 0;
	virtual void HandleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt) = 0;
	virtual void Update(const float &dt) = 0;
	virtual void Draw() = 0;
	virtual void Detroy() = 0;
	StateType isChangeState(){ return m_isChangeState; }
	StateType getStateType(){ return m_stateType; }
protected:
	StateType m_isChangeState;
	StateType m_stateType;
};

