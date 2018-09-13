#pragma once
#ifndef _Game_H_
#define _Game_H_

class Game
{
private:

public:
	Game();
	~Game();

	void Init(); 
	void ProcessInput();
	void Update();
	void Render();

	void StartGame(); //go to the main loop
};


#endif // !_Game_H_
