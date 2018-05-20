#include "UI.h"


static void _SetPos(int x, int y);
static void _DisplayWall(const UI* pUI);
static void _DisplayDesc(const UI * pUI);
static void _ResetCursorPosition(const UI * pUI);
static void _CoordinatePosAtXY(const UI * pUI, int * x, int * y);


UI* UIinitialize(int gameWeight, int gameHeight)
{
	UI * pUI = (UI *)malloc(sizeof(UI));
	pUI->windowsheight = 36;
	pUI->windowswidth = 125;
	pUI->gameHeight = gameHeight;
	pUI->gameWidth = gameWeight;
	pUI->wallBlock = pUI->foodBlock = pUI->snakeBlock = "█";
	pUI->marginleft = 6;
	pUI->marginup = 4;
	pUI->Blocksize = strlen(pUI->foodBlock);
	return pUI;
}



void UIdisplaywizard(const UI * pUI)
{
	const char* messages[] = {
		"欢迎来到贪吃蛇游戏",
		"用↑↓←→控制蛇的移动，F1为加速，F2为减速",
		"加速可以获得更高的分数"
	};
	for (int i = 0; i < sizeof(messages) / sizeof(char *); i++)
	{
		int x = (pUI->windowswidth >> 1) - (strlen(messages[i]) >> 1);
		int y = (pUI->windowsheight >> 1) - 1 + i;
		_SetPos(x, y);
		printf("%s", messages[i]);
		if (0 == i || 2 == i)
		{
			_SetPos(x + 2, y + 1);
			system("pause");
			system("CLS");
		}
	}
}
void UIdisplaygamewindows(const UI* pUI, int score, int scorePerFood)
{
	_DisplayWall(pUI);
	UIdisplayscore(pUI, score, scorePerFood);
	_DisplayDesc(pUI);
	_ResetCursorPosition(pUI);
}
void UIdisplayfoodblock(const UI * pUI, int x, int y)
{
	_CoordinatePosAtXY(pUI, &x, &y);
	_SetPos(x, y);
	printf("%s", pUI->foodBlock);

	_ResetCursorPosition(pUI);
}
void UIdisplaysnake(const UI * pUI, int x, int y)
{
	_CoordinatePosAtXY(pUI, &x, &y);
	_SetPos(x, y);
	printf("%s", pUI->snakeBlock);

	_ResetCursorPosition(pUI);
}
void UiCleanBlockAtXY(const UI* pUI, int x, int y)
{
	_CoordinatePosAtXY(pUI, &x, &y);
	_SetPos(x, y);
	for (int i = 0; i < pUI->Blocksize; i++)
	{
		printf(" ");
	}

	_ResetCursorPosition(pUI);
}
void UIdisplayscore(const UI *pUI, int score, int scorePerFood)
{
	int x = pUI->marginleft + (pUI->gameWidth + 2) * pUI->Blocksize + 4;
	int y = pUI->marginup + 6;
	_SetPos(x, y);
	printf("分数:%3d  单个食物分数:%3d", score, scorePerFood);

	_ResetCursorPosition(pUI);
}
void UIDeinitialize(UI * pUI)
{
	free(pUI);
}

void UIShowMessage(const UI * pUI, const char * message)
{
	int x = pUI->marginleft + (pUI->gameWidth >> 1) * pUI->Blocksize - (strlen(message) >> 1);
	int y = pUI->marginup + (pUI->gameHeight >> 1) - 1;
	_SetPos(x, y);
	printf("%s", message);
	_ResetCursorPosition(pUI);
}

static void _DisplayWall(const UI* pUI)
{
	//打印上下左右墙
	//上
	int x = 0;
	int y = 0;
	for (int i = 0; i < pUI->gameWidth + 2; i++)
	{
		x = pUI->marginleft + i * pUI->Blocksize;
		y = pUI->marginup;
		_SetPos(x, y);
		printf("%s", pUI->wallBlock);
	}
	//down
	for (int i = 0; i < pUI->gameWidth + 2; i++)
	{
		x = pUI->marginleft + i * pUI->Blocksize;
		y = pUI->marginup + pUI->gameHeight + 1;
		_SetPos(x, y);
		printf("%s", pUI->wallBlock);
	}
	//left
	for (int i = 0; i < pUI->gameHeight + 2; i++)
	{
		x = pUI->marginleft;
		y = pUI->marginup + i;
		_SetPos(x, y);
		printf("%s", pUI->wallBlock);
	}
	//right
	for (int i = 0; i < pUI->gameHeight + 2; i++)
	{
		x = pUI->marginleft + (pUI->gameWidth + 1) * pUI->Blocksize;
		y = pUI->marginup + i;
		_SetPos(x, y);
		printf("%s", pUI->wallBlock);
	}
}

static void _SetPos(int x, int y)
{
	COORD position = { x, y };
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, position);
}

static void _DisplayDesc(const UI * pUI)
{
	const char * explain[] = {
		"不能穿墙， 不能咬到自己。",
		"用↑↓←→分别控制蛇的移动",
		"F1为加速， F2为减速",
		"ESC 退出游戏。SPACE 暂停游戏。"
	};
	int x = (pUI->gameWidth + 2) * pUI->Blocksize + pUI->marginleft + 4;
	int size_explain = sizeof(explain) / sizeof(char *);
	int y = (((pUI->gameHeight + 2) + pUI->marginup) >> 1) - (size_explain >> 1);
	for (int i = 0; i < size_explain; i++)
	{
		_SetPos(x, y + i);
		printf("%s", explain[i]);
	}
}

static void _CoordinatePosAtXY(const UI * pUI, int * x, int * y)
{
	*x = pUI->marginleft + (*x + 1) * pUI->Blocksize;
	*y = pUI->marginup + *y + 1;
}

static void _ResetCursorPosition(const UI * pUI)
{
	_SetPos(0, pUI->windowsheight);
}