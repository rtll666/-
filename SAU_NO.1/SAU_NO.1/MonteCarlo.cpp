#ifndef	_MONTECARLO_CPP_
#define	_MONTECARLO_CPP_

#include "Define.h"


extern int wally(void);
extern int wx;
extern int wy;
extern int sfdy;
extern int enginenum;


char temp_board[GRID_NUM][GRID_NUM];
char visited[GRID_NUM][GRID_NUM];
int  stone_num[4], eye[4];
#pragma omp threadprivate(temp_board,visited,stone_num,eye)

void boardCopy()
{
	int i, j;
	for (i = 0; i <= 10; i++) {
		for (j = 0; j <= 10; j++) {
			temp_board[i][j] = board[i][j];
		}
	}
}

bool isEye(SMove pMove, char temp_board[][GRID_NUM])
{
	//	int i;
	SMove temp = pMove;
	if (temp_board[temp.x][temp.y] != 0)
		return false;
	if (temp_board[temp.x - 1][temp.y] != temp_board[temp.x + 1][temp.y] &&
		temp_board[temp.x - 1][temp.y] != BORDER &&
		temp_board[temp.x + 1][temp.y] != BORDER)
		return false;
	if (temp_board[temp.x - 1][temp.y] != temp_board[temp.x][temp.y - 1] &&
		temp_board[temp.x - 1][temp.y] != BORDER &&
		temp_board[temp.x][temp.y - 1] != BORDER)
		return false;
	if (temp_board[temp.x + 1][temp.y] != temp_board[temp.x][temp.y + 1] &&
		temp_board[temp.x + 1][temp.y] != BORDER &&
		temp_board[temp.x][temp.y + 1] != BORDER)
		return false;
	if (temp_board[temp.x][temp.y + 1] != temp_board[temp.x][temp.y - 1] &&
		temp_board[temp.x][temp.y + 1] != BORDER &&
		temp_board[temp.x][temp.y - 1] != BORDER)
		return false;
	return true;
}

void createEye(SMove pMove, char color, char temp_board[][GRID_NUM]) {
	int i;
	SMove temp = pMove;
	for (i = -1; i <= 1; i += 2) {
		temp.x = pMove.x + i;
		if (isEye(temp, temp_board)) {
			eye[color]++;
		}
		temp.x = pMove.x;
		temp.y = pMove.y + i;
		if (isEye(temp, temp_board)) {
			eye[color]++;
		}
		temp.y = pMove.y;
	}
}

void haveEye()
{
	SMove temp;
	for (temp.x = 1; temp.x <= 9; temp.x++)
	{
		for (temp.y = 1; temp.y <= 9; temp.y++)
		{
			if (isEye(temp, board))
			{
				if (temp_board[temp.x + 1][temp.y] != BORDER)
					eye[temp_board[temp.x + 1][temp.y]]++;
				else
					eye[temp_board[temp.x - 1][temp.y]]++;

			}
		}
	}
}

bool live(SMove pMove, char color, char temp_board[][GRID_NUM])
{
	int i;
	SMove temp = pMove;

	if (temp_board[pMove.x][pMove.y] == 0)
		return true;

	if (temp_board[temp.x][temp.y] != color)
		return false;

	visited[pMove.x][pMove.y] = 1;

	for (i = -1; i <= 1; i += 2)
	{
		temp.x = pMove.x + i;
		if (visited[temp.x][temp.y] == 0 && live(temp, color, temp_board))
		{
			visited[temp.x][temp.y] = 0;
			visited[pMove.x][pMove.y] = 0;
			return true;
		}
		temp.x = pMove.x;
		temp.y = pMove.y + i;
		if (visited[temp.x][temp.y] == 0 && live(temp, color, temp_board))
		{
			visited[temp.x][temp.y] = 0;
			visited[pMove.x][pMove.y] = 0;
			return true;
		}
		temp.y = pMove.y;
	}
	return false;
}

bool check(SMove pMove, char color)
{
	char temp_color;
	SMove temp = pMove;
	int i;
	if (temp_board[pMove.x][pMove.y] == color)
		return false;
	if (temp_board[pMove.x][pMove.y] == 0)
	{
		temp_board[pMove.x][pMove.y] = color;
		if (live(pMove, color, temp_board))
			return true;
		temp_board[pMove.x][pMove.y] = 0;
	}
	if (board_know[pMove.x][pMove.y] < 2)
	{
		temp_color = temp_board[pMove.x][pMove.y];
		temp_board[pMove.x][pMove.y] = color;
		for (i = -1; i <= 1; i += 2) {
			temp.x = pMove.x + i;
			if (temp_board[temp.x][temp.y] != color && !live(temp, color % 2 + 1, temp_board) && temp_board[temp.x][temp.y] != BORDER)
			{
				temp_board[pMove.x][pMove.y] = color % 2 + 1;
				return true;
			}
			temp.x = pMove.x;
			temp.y = pMove.y + i;
			if (temp_board[temp.x][temp.y] != color && !live(temp, color % 2 + 1, temp_board) && temp_board[temp.x][temp.y] != BORDER) {
				temp_board[pMove.x][pMove.y] = color % 2 + 1;
				return true;
			}
			temp.y = pMove.y;
		}
		temp_board[pMove.x][pMove.y] = temp_color;
	}
	return false;
}

int removed(SMove pMove, char color, char temp_board[][GRID_NUM])
{
	int i, num = 0;
	SMove temp = pMove;
	temp_board[temp.x][temp.y] = 0;

	for (i = -1; i <= 1; i += 2)
	{
		temp.x = pMove.x + i;
		if (temp_board[temp.x][temp.y] == color)
		{
			num += removed(temp, color, temp_board) + 1;
		}
		temp.x = pMove.x;
		temp.y = pMove.y + i;
		if (temp_board[temp.x][temp.y] == color)
		{
			num += removed(temp, color, temp_board) + 1;
		}
		temp.y = pMove.y;
	}
	return num;
}

int clean(SMove pMove, char color, char temp_board[][GRID_NUM])
{
	int i, num = 0;
	SMove temp = pMove;
	memset(visited, 0, sizeof(visited));

	for (i = -1; i <= 1; i += 2)
	{
		temp.x = pMove.x + i;
		if (temp_board[temp.x][temp.y] == color && !live(temp, color, temp_board))
		{
			num += removed(temp, color, temp_board) + 1;
		}
		temp.x = pMove.x;
		temp.y = pMove.y + i;
		if (temp_board[temp.x][temp.y] == color && !live(temp, color, temp_board))
		{
			num += removed(temp, color, temp_board) + 1;
		}
		temp.y = pMove.y;

	}
	return num;
}

int MonteCarloMove(char color)
{
	int num, flag, take_num, out = 0;
	SMove temp;
	memset(eye, 0, sizeof(eye));
	haveEye();
	while (1)
	{
		if (stone_num[1] + stone_num[2] + eye[1] + eye[2] >= 81)
			break;

		srand(rand() * (int)time(0));
		num = 1 + (int)((81.0 - stone_num[1] - stone_num[2] - eye[1] - eye[2]) * rand() / (RAND_MAX + 1.0));
		flag = 0;
		for (temp.x = 1; temp.x <= 9; temp.x++)
		{
			for (temp.y = 1; temp.y <= 9; temp.y++)
			{
				if (temp_board[temp.x][temp.y] == 0)
				{
					num--;
					if (num <= 1)
					{
						if (check(temp, color))
						{
							flag = 1;
							temp_board[temp.x][temp.y] = color;
							stone_num[color] ++;
							take_num = clean(temp, color % 2 + 1, temp_board);
							stone_num[color % 2 + 1] = stone_num[color % 2 + 1] - take_num;
							createEye(temp, color, temp_board);
							color = color % 2 + 1;
							take_num = 0;
							temp.x = 11;
							break;
						}
						else
						{
							temp_board[temp.x][temp.y] = 0;
						}
					}
				}
			}
		}
		if (flag == 0)
		{
			color = color % 2 + 1;
		}
	}
	if (stone_num[chessColor] + eye[chessColor] > stone_num[chessColor % 2 + 1] + eye[chessColor % 2 + 1])
		return 1;
	if (stone_num[chessColor] + eye[chessColor] < stone_num[chessColor % 2 + 1] + eye[chessColor % 2 + 1])
		return -1;
	return 0;
}

bool MonteCarlo(SMove* pMove)
{
	int i, num, point, max_point = 0;
	SMove temp, begin_stone, best;
	int start = clock();
	int end;
	omp_set_num_threads(4);
#pragma omp parallel private(begin_stone,point,i,num,temp)
	{
#pragma omp for
		for (begin_stone.x = 3; begin_stone.x <= 7; begin_stone.x++)
		{
			for (begin_stone.y = 3; begin_stone.y <= 7; begin_stone.y++)
			{
#pragma omp critical(board)	
				boardCopy();
				if (!check(begin_stone, chessColor))
				{
					continue;
				}
				point = 0;
				for (i = 0; i < MCMAX; i++)     //MCMAX为蒙特卡洛次数 为10000
				{
					srand(rand() * (int)time(0));
					boardCopy();
					temp_board[begin_stone.x][begin_stone.y] = chessColor;
					stone_num[chessColor] = player[chessColor].total + 1;
					stone_num[chessColor % 2 + 1] = player[chessColor % 2 + 1].know;          // 已知的对方子个数

					while (player[chessColor % 2 + 1].total > stone_num[chessColor % 2 + 1])
					{
						num = 1 + (int)((81.0 - stone_num[1] - stone_num[2]) * rand() / (RAND_MAX + 1.0));//产生随机数
						for (temp.x = 1; temp.x <= 9; temp.x++) //在棋盘空点随机落子
						{
							for (temp.y = 1; temp.y <= 9; temp.y++)
							{
								if (temp_board[temp.x][temp.y] == 0)
								{
									num--;
									if (num == 1 && check(temp, chessColor % 2 + 1))
									{
										temp_board[temp.x][temp.y] = chessColor % 2 + 1;
										stone_num[chessColor % 2 + 1] ++;
										temp.x = 10;
										break;
									}
								}
							}
						}
						end = clock();
						if (end - start >= 6000)
						{
							i = MCMAX;
							break;
						}
						point += MonteCarloMove(chessColor % 2 + 1);
					}
				}
#pragma omp critical(max_point_best)
				if (point > max_point && begin_stone.x != (*pMove).x && begin_stone.y != (*pMove).y)
				{
					max_point = point;
					best.x = begin_stone.x;
					best.y = begin_stone.y;
				}
			}
		}
	}
	if (max_point > believePoint)//胜率最大的点胜率是否大于置信值
	{
		*pMove = best;
		return true;
	}
	else
	{
		return GetGoMove(pMove);
	}
}
#endif