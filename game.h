#ifndef _GAME_H_
#define _GAME_H_

#include <assert.h>
#include <time.h>
#include "Snake.h"
#include <stdlib.h>

Game *CreatGame();
void StartGame(Game * pGame);
void DestroyGame(Game * pGame);

#endif 