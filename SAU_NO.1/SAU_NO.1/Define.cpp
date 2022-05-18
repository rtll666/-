#ifndef	_DEFINE_CPP_
#define	_DEFINE_CPP_

#include "Define.h"


char		board[GRID_NUM][GRID_NUM];		//���̱�ʾ
char		board_know[GRID_NUM][GRID_NUM]; //��̽����
int			mark[GRID_NUM][GRID_NUM];		//MonteCarlo��������
char		chessColor;				    	//�Լ������ɫ
SMove		bestMove;						//������


int boardBaseScore[GRID_NUM][GRID_NUM] = 			//���̵Ļ�������
{
	0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,1,1,0,
	0,1,2,2,2,2,2,2,2,1,0,
	0,1,2,3,3,3,3,3,2,1,0,
	0,1,2,3,4,4,4,3,2,1,0,
	0,1,2,3,4,5,4,3,2,1,0,
	0,1,2,3,4,4,4,3,2,1,0,
	0,1,2,3,3,3,3,3,2,1,0,
	0,1,2,2,2,2,2,2,2,1,0,
	0,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0
};

SPlayer player[3];

#endif