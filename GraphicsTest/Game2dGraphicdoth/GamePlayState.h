#pragma once
#include "State.h"
#include <vector>
class Player;
class DarkShape;

class GamePlayState :
	public State
{
public:
	GamePlayState();
	virtual ~GamePlayState();
	void Init() override;
	void HandleInput(const MouseInput &mouseInput, const KeyInput &keyInput, const float &dt) override;
	void Update(const float &dt) override;
	void Draw() override;
	void Detroy() override;
	static Player* getPlayer(){
		return m_player;
	}
private:
	static Player *m_player;
};

