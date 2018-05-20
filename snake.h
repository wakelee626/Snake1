#ifndef _SNAKE_H_
#define _SNAKE_H_

//位置坐标
typedef struct Position {
	int x;
	int y;
}Position;

//蛇节点
typedef struct node {
	Position position;
	struct node * pNext;
}SnakeNode;

//蛇朝向
typedef enum orientation {
	UP,
	DOWN,
	LEFT,
	RIGHT
}Orientation;

//蛇
typedef struct snake {
	SnakeNode * pBody;
	Orientation orientation;
}Snake;

typedef struct game {
	Snake snake;

	//游戏区域宽和高
	int gamewidth;
	int gameheight;

	int score;  //当前分数
	int scorePerFood;
	Position foodcoord; //食物坐标
}Game;





#endif //_SNAKE_H_