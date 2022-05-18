#ifndef	_ENGINE_CPP_
#define	_ENGINE_CPP_
//#include"MonteCarlo.cpp"
#include "Engine.h"
#include "time.h"


extern int wally(void);
extern int wx;
extern int wy;
extern int sfdy;
extern  int enginenum;
extern int dsxz;//定式选择，0为正常，1为定式1，共1-6；
int     mtime, fla, i, j, scoretemp = 0, k[2] = { 0 };

bool dingshi(SMove* pMove, int flak);
bool dingshi1(SMove* pMove, int flak);
bool dingshi2(SMove* pMove, int flak);//中心开花
bool dingshi3(SMove* pMove, int flak);//竖直长弓
bool dingshi4(SMove* pMove, int flak);//双龙眼
bool dingshi5(SMove* pMove, int flak);//狗头阵

int flak = 1, dir1[3][2] = { {1,0},{0,-1},{0,1} }, dir2[3][2] = { {0,1},{-1,0},{1,0} }, dir3[3][2] = { {1,0},{0,1},{0,-1} }, dir4[3][2] = { {0,1},{1,0},{-1,0} };

SMove pretemp;
SMove hashtemp[1000];

int dschange = 0;

bool	SearchMove(SMove* pMove, int flag)//招法安排
{
	flak = player[chessColor].total + 1;//flak为步数；；；；flag为模式
	if (flag == 1)
	{
		wally();//黑棋产生招法成功，返回平台

		if (wy + 1 > 0 && wy + 1 < 10 && wx + 1 > 0 && wx + 1 < 10 && board[wy + 1][wx + 1] == 0 && GetWallyScore(wy + 1, wx + 1) > 0)
		{
			pMove->x = (wy + 1);
			pMove->y = (wx + 1);
			return true;
		}
		else
		{
			sfdy = 1;
			return GetGoMove(pMove);
		}
	}
	if (flag == 2)
	{
		if (MonteCarlo(pMove))
			return true;
		else
		{
			return GetGoMove(pMove);
		}
	}
	if (flag == 3)
	{
		return GetGoMove(pMove);
	}
	if (flag == 4)
	{
		if (flak < 11)
		{
			if (dsxz == 1)
			{
				if (dingshi(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 2)
			{
				if (dingshi1(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 3)
			{
				if (dingshi2(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 4)
			{
				if (dingshi3(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 5)
			{
				if (dingshi4(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 6)
			{
				if (dingshi5(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else
			{
				if (chessColor == BLACK && dingshi(pMove, flak))
				{
					return true;
				}
				else if (chessColor == WHITE && dingshi1(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
		}
		if (flak >= 11)
		{

			return GetGoMove(pMove);

		}
	}
	else
	{
		if (flak < 11)
		{
			if (dsxz == 1)
			{
				if (dingshi(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 2)
			{
				if (dingshi1(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 3)
			{
				if (dingshi2(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 4)
			{
				if (dingshi3(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 5)
			{
				if (dingshi4(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else if (dsxz == 6)
			{
				if (dingshi5(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
			else
			{
				if (chessColor == BLACK && dingshi(pMove, flak))
				{
					return true;
				}
				else if (chessColor == WHITE && dingshi1(pMove, flak))
				{
					return true;
				}
				else
				{
					if (MonteCarlo(pMove))
						return true;
					else
					{
						return GetGoMove(pMove);
					}
				}
			}
		}
		if (flak >= 11)
		{
			if (flak <= 20)
			{
				wally();//产生招法成功，返回平台
				printf("wally to %d %c", (wy + 1), ((wx + 1) + '@'));
				//if (wy + 1 > 0 && wy + 1 < 10 && wx + 1 > 0 && wx + 1 < 10 && board[wy + 1][wx + 1] == 0 && GetWallyScore(wy + 1, wx + 1) > 0)
				{
					pMove->x = (wy + 1);
					pMove->y = (wx + 1);
					return true;
				}
				/*else
				{
					sfdy = 1;
					return GetGoMove(pMove);
				}*/
			}
			if (flak > 20)
			{
				return GetGoMove(pMove);
			}
		}
	}
}

bool dingshi(SMove* pMove, int flak)
{
	if (flak == 1)
	{
		pMove->x = 3;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 3;
			pMove->y = 6;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
	if (flak == 2)
	{
		pMove->x = 4;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 4;
			pMove->y = 6;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
	if (flak == 3)
	{
		pMove->x = 5;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 5;
			pMove->y = 6;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
	if (flak == 4)
	{
		pMove->x = 6;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 6;
			pMove->y = 6;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
	if (flak == 5)
	{
		pMove->x = 7;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 7;
			pMove->y = 5;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
	if (flak == 6)
	{
		pMove->x = 7;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 3;
			pMove->y = 6;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
	if (flak == 7)
	{
		pMove->x = 7;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 3;
			pMove->y = 5;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
	if (flak == 8)
	{
		pMove->x = 7;
		pMove->y = 4;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 3;
			pMove->y = 4;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
	if (flak == 9)
	{
		pMove->x = 7;
		pMove->y = 3;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 3;
			pMove->y = 3;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
	if (flak == 10)
	{
		pMove->x = 8;
		pMove->y = 3;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
		{
			pMove->x = 2;
			pMove->y = 3;
			if (board[pMove->x][pMove->y] == NOSTONE)
				return true;
			else
				return false;
		}
	}
}
bool dingshi1(SMove* pMove, int flak)
{
	if (flak == 1)
	{
		pMove->x = 5;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 2)
	{
		pMove->x = 4;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 3)
	{
		pMove->x = 6;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 4)
	{
		pMove->x = 3;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 5)
	{
		pMove->x = 7;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 6)
	{
		pMove->x = 7;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 7)
	{
		pMove->x = 3;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 8)
	{
		pMove->x = 2;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 9)
	{
		pMove->x = 8;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 10)
	{
		pMove->x = 5;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
}
bool dingshi2(SMove* pMove, int flak)
{
	if (flak == 1)
	{
		pMove->x = 5;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 2)
	{
		pMove->x = 6;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 3)
	{
		pMove->x = 4;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 4)
	{
		pMove->x = 7;
		pMove->y = 4;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 5)
	{
		pMove->x = 7;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 6)
	{
		pMove->x = 3;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 7)
	{
		pMove->x = 2;
		pMove->y = 4;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 8)
	{
		pMove->x = 2;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 9)
	{
		pMove->x = 5;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 10)
	{
		pMove->x = 4;
		pMove->y = 4;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
}
bool dingshi3(SMove* pMove, int flak)
{
	if (flak == 1)
	{
		pMove->x = 5;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 2)
	{
		pMove->x = 4;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 3)
	{
		pMove->x = 6;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 4)
	{
		pMove->x = 6;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 5)
	{
		pMove->x = 3;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 6)
	{
		pMove->x = 3;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 7)
	{
		pMove->x = 6;
		pMove->y = 8;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 8)
	{
		pMove->x = 2;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 9)
	{
		pMove->x = 6;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 10)
	{
		pMove->x = 4;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
}
bool dingshi4(SMove* pMove, int flak)
{
	if (flak == 1)
	{
		pMove->x = 6;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 2)
	{
		pMove->x = 6;
		pMove->y = 4;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 3)
	{
		pMove->x = 6;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 4)
	{
		pMove->x = 6;
		pMove->y = 3;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 5)
	{
		pMove->x = 7;
		pMove->y = 3;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 6)
	{
		pMove->x = 5;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 7)
	{
		pMove->x = 5;
		pMove->y = 2;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 8)
	{
		pMove->x = 6;
		pMove->y = 8;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 9)
	{
		pMove->x = 6;
		pMove->y = 1;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 10)
	{
		pMove->x = 5;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
}
bool dingshi5(SMove* pMove, int flak)
{
	if (flak == 1)
	{
		pMove->x = 5;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 2)
	{
		pMove->x = 5;
		pMove->y = 4;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 3)
	{
		pMove->x = 4;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 4)
	{
		pMove->x = 5;
		pMove->y = 3;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 5)
	{
		pMove->x = 6;
		pMove->y = 5;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 6)
	{
		pMove->x = 5;
		pMove->y = 7;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 7)
	{
		pMove->x = 6;
		pMove->y = 6;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 8)
	{
		pMove->x = 6;
		pMove->y = 3;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 9)
	{
		pMove->x = 6;
		pMove->y = 8;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
	if (flak == 10)
	{
		pMove->x = 5;
		pMove->y = 2;
		if (board[pMove->x][pMove->y] == NOSTONE)
			return true;
		else
			return false;
	}
}

#endif