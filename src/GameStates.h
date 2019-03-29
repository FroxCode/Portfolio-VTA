#pragma once

class gameStates
{
public:
	enum states
	{
		START,
		GAME,
		GAMEOVER,
		BOSS_DEFEATED,
		OPTIONS,
		MULTIPLAYER,
		CREDITS,
		PAUSE
	};
	int currentState;
	enum MultiplayerState { MP_LOBBY, MP_PLAYING, MP_GAMEOVER };
	MultiplayerState mpState = MultiplayerState::MP_LOBBY;
	int lastState = -1;
};
