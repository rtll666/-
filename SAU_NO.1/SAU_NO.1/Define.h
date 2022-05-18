#pragma once
#ifndef	_DEFINE_H_
#define	_DEFINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <windows.h>


#define GRID_NUM 11			//棋盘行数，其中1..9为棋的坐标，其他为边界
#define GRID_COUNT 81		//可放棋子总数
#define BLACK 	1			//黑棋		黑白棋转换时,可对求异或
#define WHITE 	2			//白棋
#define BORDER	3			//边界
#define NOSTONE 	0		//空子无棋
#define ADDSTONE   5             //智能加子

#define MCMAX		 10000	//蒙特卡洛次数
#define believePoint 4000		//信任值
#define Hash_Believe   80
#define JIN  4

#define HASH_SCANF_NUM   9 

typedef struct _stoneposition//下棋的位置
{
	char x;
	char y;
	int	score;//棋盘的分
}SMove;				    	//招法

typedef struct SGroup//群
{
	int count;
	float eyes;//气
	char color;
}SGroup;

typedef struct SPlayer
{
	int total;//双方走子总数
	int know;//知道对方的子数
}SPlayer;

extern char		board[GRID_NUM][GRID_NUM];		//棋盘表示
extern char		board_know[GRID_NUM][GRID_NUM]; //试探棋盘
extern char		chessColor;						//自己棋的颜色
extern SMove	bestMove;						//最优棋

extern SPlayer  player[3];			        	//白和黑棋,记录各方的走子总数和知道对方的子数

extern int boardBaseScore[GRID_NUM][GRID_NUM];

void 	InitGame();
void	record();
void	Undo();

void PrintBoard();

#include "Engine.h"

#endif
