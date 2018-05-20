#include "game.h"
#include "UI.h"
static void _Initsnake(Snake * pSnake);
static void _DisplaySnake(UI* pUI, Snake * psnack);

static void _GenerateFood(Game * pGame);
static int _IsSnakeNode(Snake * pSnake, int x, int y);

static int _IsFood(Game * pGame, Position NextBlock);
static Position _NextBlockPosition(Snake * psnack);
static void _UpdataScoreAndDisplay(UI * pUI, Game * pGame);

static void _SnakeIncreaseAndMove(UI * pUI, Game * pGame, Position NextBlock);
static void _SnakeMove(UI * pUI, Game * pGame, Position NextBlock);

static void _HandleDirection(Snake * pSnake);
static void _Pause();
static int _IsGameOver(Game * pGame);



Game *CreatGame()
{
	Game * pGame = (Game *)malloc(sizeof(Game));
	pGame->gameheight = 28;
	pGame->gamewidth = 37;
	pGame->score = 0;
	pGame->scorePerFood = 2;
	pGame->snake.orientation = RIGHT;
	_Initsnake(&pGame->snake);
	_GenerateFood(pGame);
	return pGame;
}
void StartGame(Game * pGame)
{
	UI * pUI = UIinitialize(pGame->gamewidth, pGame->gameheight);
	UIdisplaywizard(pUI);
	UIdisplaygamewindows(pUI, pGame->score, pGame->scorePerFood);
	_DisplaySnake(pUI, &pGame->snake);
	UIdisplayfoodblock(pUI, pGame->foodcoord.x, pGame->foodcoord.y);
	size_t sl = 400;
	while (1)
	{
		//方向
		_HandleDirection(&pGame->snake);
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			_Pause();
		}

		//下一个方块
		Position NextBlock = _NextBlockPosition(&pGame->snake);

		if (_IsFood(pGame, NextBlock))
		{
			_UpdataScoreAndDisplay(pUI, pGame);

			_SnakeIncreaseAndMove(pUI, pGame, NextBlock);

			_GenerateFood(pGame);
			UIdisplayfoodblock(pUI, pGame->foodcoord.x, pGame->foodcoord.y);
		}
		else
		{
			_SnakeMove(pUI, pGame, NextBlock);
		}
		if (_IsGameOver(pGame))
		{
			break;
		}
		if (GetAsyncKeyState(VK_F1))
		{
			if (sl > 100)
			{
				sl -= 100;
				pGame->scorePerFood *= 2;
				UIdisplayscore(pUI, pGame->score, pGame->scorePerFood);
			}
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sl < 800)
			{
				sl += 100;
				pGame->scorePerFood /= 2;
				UIdisplayscore(pUI, pGame->score, pGame->scorePerFood);
			}
		}
		Sleep(sl);
	}
	UIShowMessage(pUI, "游戏结束");
	UIDeinitialize(pUI);
}
void DestroyGame(Game * pGame)
{
	SnakeNode * next = pGame->snake.pBody->pNext;
	for (SnakeNode * cur = pGame->snake.pBody;
		cur->pNext != NULL; next = next->pNext)
	{
		free(cur);
		cur = next;
	}
	free(pGame);
}

static int _IsSnakeNode(Snake * pSnake, int x, int y)
{
	SnakeNode * cur = pSnake->pBody;
	while (cur != NULL)
	{
		if (x == cur->position.x && y == cur->position.y)
		{
			return 1;
		}
		cur = cur->pNext;
	}
	return 0;
}


static void _GenerateFood(Game * pGame)
{
	int x = 0, y = 0;
	do
	{
		x = rand() % pGame->gamewidth;
		y = rand() % pGame->gameheight;
	} while (_IsSnakeNode(&pGame->snake, x, y));
	pGame->foodcoord.x = x;
	pGame->foodcoord.y = y;
}

static void _Initsnake(Snake * pSnake)
{
	int x = 5, y = 5;
	pSnake->pBody = NULL;

	for (int i = 0; i < 3; i++)
	{
		SnakeNode * pNode = (SnakeNode *)malloc(sizeof(SnakeNode));
		pNode->position.x = i + x;
		pNode->position.y = y;
		pNode->pNext = pSnake->pBody;
		pSnake->pBody = pNode;
	}
}
static void _DisplaySnake(UI* pUI, Snake * psnake)
{
	SnakeNode * cur = psnake->pBody;
	while (cur != NULL)
	{
		UIdisplaysnake(pUI, cur->position.x, cur->position.y);
		cur = cur->pNext;
	}
}

static Position _NextBlockPosition(Snake * psnake)
{
	Position NextPosition = { 0, 0 };
	switch (psnake->orientation)
	{
	case UP:NextPosition.x = psnake->pBody->position.x;
		NextPosition.y = psnake->pBody->position.y - 1;
		break;
	case DOWN:NextPosition.x = psnake->pBody->position.x;
		NextPosition.y = psnake->pBody->position.y + 1;
		break;
	case LEFT:NextPosition.x = psnake->pBody->position.x - 1;
		NextPosition.y = psnake->pBody->position.y;
		break;
	case RIGHT:NextPosition.x = psnake->pBody->position.x + 1;
		NextPosition.y = psnake->pBody->position.y;
		break;
	default:break;
	}
	return NextPosition;
}

static int _IsFood(Game * pGame, Position NextBlock)
{
	if (NextBlock.x == pGame->foodcoord.x && NextBlock.y == pGame->foodcoord.y)
	{
		return 1;
	}
	return 0;
}
static void _UpdataScoreAndDisplay(UI * pUI, Game * pGame)
{
	pGame->score += pGame->scorePerFood;
	UIdisplayscore(pUI, pGame->score, pGame->scorePerFood);
}
static void _SnakeIncreaseAndMove(UI * pUI, Game * pGame, Position NextBlock)
{
	SnakeNode * Node = (SnakeNode *)malloc(sizeof(SnakeNode));
	Node->position = NextBlock;

	Node->pNext = pGame->snake.pBody;
	pGame->snake.pBody = Node;

	NextBlock = _NextBlockPosition(&pGame->snake);
	_SnakeMove(pUI, pGame, NextBlock);
}
static void _SnakeMove(UI * pUI, Game * pGame, Position NextBlock)
{
	SnakeNode * cur = pGame->snake.pBody;
	while (cur->pNext->pNext != NULL)
	{
		cur = cur->pNext;
	}
	UiCleanBlockAtXY(pUI, cur->pNext->position.x, cur->pNext->position.y);

	cur->pNext->pNext = pGame->snake.pBody;
	pGame->snake.pBody = cur->pNext;
	cur->pNext = NULL;

	pGame->snake.pBody->position = NextBlock;
	UIdisplaysnake(pUI, NextBlock.x, NextBlock.y);
}

static int _IsGameOver(Game * pGame)
{
	Position SnakePos = pGame->snake.pBody->position;
	SnakeNode * cur = pGame->snake.pBody->pNext;
	//撞墙
	if (SnakePos.x < 0 || SnakePos.x >= pGame->gamewidth
		|| SnakePos.y < 0 || SnakePos.y >= pGame->gameheight)
	{
		return 1;
	}
	//撞自己
	while (cur != NULL)
	{
		if (SnakePos.x == cur->position.x && SnakePos.y == cur->position.y)
		{
			return 1;
		}
		cur = cur->pNext;
	}
	return 0;
}

static void _HandleDirection(Snake * pSnake)
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (pSnake->orientation != DOWN)
		{
			pSnake->orientation = UP;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (pSnake->orientation != UP)
		{
			pSnake->orientation = DOWN;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (pSnake->orientation != RIGHT)
		{
			pSnake->orientation = LEFT;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (pSnake->orientation != LEFT)
		{
			pSnake->orientation = RIGHT;
		}
	}
}

static void _Pause()
{
	while (1)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
		Sleep(300);
	}
}