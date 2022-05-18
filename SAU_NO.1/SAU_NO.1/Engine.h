#pragma once
#ifndef	_ENGINE_H_
#define	_ENGINE_H_

#include "Define.h"

bool	SearchMove(SMove* pMove, int flag);	//��pass������false�����򷵻�true�Լ��з�
bool	MonteCarlo(SMove* pMove);     //���ؿ��������з�
bool	GetGoMove(SMove* pMove);	//��ͨ�Ĳ����з�����pass������false�����򷵻�true�Լ��з�
int     GetScore(int x, int y);
int     GetWallyScore(int x, int y);
int     clean(SMove pMove, char color, char temp_board[][GRID_NUM]);
bool    isEye(SMove pMove, char temp_board[][GRID_NUM]);

#endif
