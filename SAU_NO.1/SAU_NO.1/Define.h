#pragma once
#ifndef	_DEFINE_H_
#define	_DEFINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <windows.h>


#define GRID_NUM 11			//��������������1..9Ϊ������꣬����Ϊ�߽�
#define GRID_COUNT 81		//�ɷ���������
#define BLACK 	1			//����		�ڰ���ת��ʱ,�ɶ������
#define WHITE 	2			//����
#define BORDER	3			//�߽�
#define NOSTONE 	0		//��������
#define ADDSTONE   5             //���ܼ���

#define MCMAX		 10000	//���ؿ������
#define believePoint 4000		//����ֵ
#define Hash_Believe   80
#define JIN  4

#define HASH_SCANF_NUM   9 

typedef struct _stoneposition//�����λ��
{
	char x;
	char y;
	int	score;//���̵ķ�
}SMove;				    	//�з�

typedef struct SGroup//Ⱥ
{
	int count;
	float eyes;//��
	char color;
}SGroup;

typedef struct SPlayer
{
	int total;//˫����������
	int know;//֪���Է�������
}SPlayer;

extern char		board[GRID_NUM][GRID_NUM];		//���̱�ʾ
extern char		board_know[GRID_NUM][GRID_NUM]; //��̽����
extern char		chessColor;						//�Լ������ɫ
extern SMove	bestMove;						//������

extern SPlayer  player[3];			        	//�׺ͺ���,��¼����������������֪���Է�������

extern int boardBaseScore[GRID_NUM][GRID_NUM];

void 	InitGame();
void	record();
void	Undo();

void PrintBoard();

#include "Engine.h"

#endif
