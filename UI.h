#ifndef _UI_H_
#define _UI_H_

#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct UI {
	int windowswidth;
	int windowsheight;

	int marginleft;
	int marginup;

	int gameWidth;
	int gameHeight;

	int Blocksize;
	char * foodBlock;
	char * snakeBlock;
	char * wallBlock;
}UI;

UI* UIinitialize(int gameWeight, int gameHeight);
void UIdisplaygamewindows(const UI* pUI, int score, int scorePerFood);
void UIdisplayfoodblock(const UI * pUI, int x, int y);
void UIdisplaysnake(const UI * pUI, int x, int y);
void UiCleanBlockAtXY(const UI* pUI, int x, int y);
void UIdisplayscore(const UI *pUI, int score, int scorePerFood);
void UIDeinitialize(UI * pUI);
void UIdisplaywizard(const UI * pUI);
void UIShowMessage(const UI * pUI, const char * message);


#endif //_UI_H