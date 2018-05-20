#ifndef _SNAKE_H_
#define _SNAKE_H_

//λ������
typedef struct Position {
	int x;
	int y;
}Position;

//�߽ڵ�
typedef struct node {
	Position position;
	struct node * pNext;
}SnakeNode;

//�߳���
typedef enum orientation {
	UP,
	DOWN,
	LEFT,
	RIGHT
}Orientation;

//��
typedef struct snake {
	SnakeNode * pBody;
	Orientation orientation;
}Snake;

typedef struct game {
	Snake snake;

	//��Ϸ�����͸�
	int gamewidth;
	int gameheight;

	int score;  //��ǰ����
	int scorePerFood;
	Position foodcoord; //ʳ������
}Game;





#endif //_SNAKE_H_