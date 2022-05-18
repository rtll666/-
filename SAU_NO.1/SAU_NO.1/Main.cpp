#define _CRT_SECURE_NO_WARNINGS 1
#ifndef	_MAIN_CPP_
#define	_MAIN_CPP_

#include "Define.h"
#include <stdarg.h>
#include<iostream>
char undo_board[GRID_NUM][GRID_NUM];
char undo_board_know[GRID_NUM][GRID_NUM];
SPlayer undo_player[3];
int dsxz = 2;

int main()
{
	char msg[100] = { 0 };
	int	numTi = 0;//������Ŀ
	int	x, y;
	int sfxz = 0;//�㷨ѡ��0Ϊ��ʽ������ģʽ����1Ϊwally����·Χ���㷨��,2Ϊ���ؿ��壬3Ϊ�Ʒ��㷨GetGoMove

	InitGame();//��ʼ����Ϸ
	system("color 70");//�ı����̨��ǰ��ɫ�ͱ���
	while (1)
	{
		Sleep(50);//��������0.05��
		fflush(stdin);//ˢ�±�׼���뻺����
		Sleep(50);
		fflush(stdout);//ˢ�±�׼���������
		printf("���֣�'new' or 'quit'\n");
		scanf("%s", msg);
		if (strcmp(msg, "quit") == 0)                                 //������Ϸ
		{
			break;
		}
		else if (strcmp(msg, "new") == 0)                	         //��ʼ�����
		{
			InitGame();
			PrintBoard();
			printf("���ӣ�'black' or other\n");
			scanf("%s", msg);
			if (strcmp(msg, "black") == 0)                            //���msg��black���Լ��Ǻ���
			{
				chessColor = BLACK;
				//
				SearchMove(&bestMove, 4);

				//SearchMove(&bestMove, sfxz);
				printf("%d%d", bestMove.x, bestMove.y);
				printf("-->%d %c", bestMove.x, bestMove.y + '@');        //���һ������з�
				printf("   ���ߣ�'m' or 'i'\n");//m��ʾ�Ϸ���i��ʾ���Ϸ�
				while (1)
				{
					scanf("%s", msg);                              //��ȡ������Ϣ
					if (strcmp(msg, "m") == 0)                     //�Լ��ϴ��ߵ�Ϊ�Ϸ��з�
					{
						board[bestMove.x][bestMove.y] = BLACK;//�Ϸ��Ļ��ϴ��ߵ���λ�ú����ʾ
						PrintBoard();
						record();
						player[BLACK].total++;//��¼�������ӵ�����
						clean(bestMove, WHITE, board);
						player[WHITE].total++;//��¼�������ӵ�����
						printf("������'go' / 'take' / 'taked' / 'undo' / 'passed'\n");
					}
					else if (strcmp(msg, "go") == 0)
					{
						if (SearchMove(&bestMove, 4))
						{
							printf("-->%d %c", bestMove.x, bestMove.y + '@');     //�����з��ɹ�������ƽ̨ 
							printf("   ���ߣ�'m' or 'i'\n");
						}
						else
						{
							printf("passed\n");                   //���ɹ����Լ�pass
						}
					}
					else if (strcmp(msg, "i") == 0)                //�Լ��ϴ��ߵ�Ϊ�Ƿ��з�
					{
						board[bestMove.x][bestMove.y] = WHITE;//�Ƿ��Ļ��ϴ��ߵ���λ�ð����ʾ
						PrintBoard();
						player[WHITE].know++; //��¼֪�����������
						board_know[bestMove.x][bestMove.y] ++;     //
						if (SearchMove(&bestMove, 2))
						{
							printf("-->%d %c", bestMove.x, bestMove.y + '@');      //�����з��ɹ�������ƽ̨
							printf("   ���ߣ�'m' or 'i'\n");
						}
						else
						{
							printf("passed\n");			         //���ɹ����Լ�pass
						}
					}
					else if (strcmp(msg, "take") == 0)            //�Լ�����,��ȡ������Ŀ
					{
						SMove moveList[81];
						printf("������Ŀ��");
						scanf("%d", &numTi);
						player[WHITE].total -= numTi;
						for (int k = 0; k < numTi; k++)
						{
							printf("�������꣺");
							Sleep(50);
							fflush(stdin);
							scanf("%d%d", &x, &y);
							moveList[k].x = x;
							moveList[k].y = y;
						}
						for (int i = 0; i < numTi; i++)
						{
							board[moveList[i].x][moveList[i].y] = NOSTONE;
						}
						PrintBoard();
						printf("������'go' / 'passed' / 'taked'\n");
					}
					else if (strcmp(msg, "taked") == 0)            //�Է�����,��ȡ������Ŀ
					{
						SMove moveList[81];
						printf("��������Ŀ��");
						scanf("%d", &numTi);
						player[BLACK].total -= numTi;
						for (int k = 0; k < numTi; k++)
						{
							printf("���������꣺");
							Sleep(50);
							fflush(stdin);
							scanf("%d %d", &x, &y);
							moveList[k].x = x;
							moveList[k].y = y;
							if (board[x - 1][y] == NOSTONE)           //��������ӵı߽����̽�⣬����ǿգ��϶��ǶԷ�����
							{
								board[x - 1][y] = WHITE;
								player[WHITE].know++;
							}
							if (board[x + 1][y] == NOSTONE)
							{
								board[x + 1][y] = WHITE;
								player[WHITE].know++;
							}
							if (board[x][y - 1] == NOSTONE)
							{
								board[x][y - 1] = WHITE;
								player[WHITE].know++;
							}
							if (board[x][y + 1] == NOSTONE)
							{
								board[x][y + 1] = WHITE;
								player[WHITE].know++;
							}
						}
						for (int i = 0; i < numTi; i++)
						{
							board[moveList[i].x][moveList[i].y] = NOSTONE;
						}
						PrintBoard();
						printf("������'go' / 'passed'\n");
					}
					else if (strcmp(msg, "passed") == 0)           //�Է�pass
					{
						player[WHITE].know = player[WHITE].total;  // ///// MonteCarlo �� stone_num[chessColor%2+1] = player[chessColor].know; �ж���
					}
					else if (strcmp(msg, "undo") == 0)
					{
						Undo();
						printf("������'i' or 'm'\n");
					}
					else
					{
						printf("Error Input!!!\n");
						PrintBoard();
					}
				}
			}
			else
			{
				chessColor = WHITE;
				// SearchMove(&bestMove,0);

				SearchMove(&bestMove, sfxz);

				printf("-->%d %c", bestMove.x, bestMove.y + '@');        //���һ������з�
				printf("   ���ߣ�'m' or 'i'\n");
				while (1)
				{
					scanf("%s", msg);
					chessColor = WHITE;			                     //�Լ��ǰ���		    
					if (strcmp(msg, "m") == 0)					     //�Լ��ϴ��ߵ�Ϊ�Ϸ��з�
					{
						board[bestMove.x][bestMove.y] = WHITE;
						PrintBoard();
						record();
						player[WHITE].total++;
						clean(bestMove, BLACK, board);
						player[BLACK].total++;
						printf("������'go' / 'take' / 'taked' / 'undo' / 'passed'\n");
					}
					else if (strcmp(msg, "go") == 0)
					{
						if (SearchMove(&bestMove, 1))
						{
							printf("%d %c", bestMove.x, bestMove.y + '@');          //�����з��ɹ�������ƽ̨
							printf("   ���ߣ�'m' or 'i'\n");
						}
						else                                          //���ɹ����Լ�pass
						{
							printf("passed\n");
						}
					}
					else if (strcmp(msg, "i") == 0)                   //�Լ��ϴ��ߵ�Ϊ�Ƿ��з�
					{
						board[bestMove.x][bestMove.y] = BLACK;
						PrintBoard();
						player[BLACK].know++;
						board_know[bestMove.x][bestMove.y] ++;
						if (SearchMove(&bestMove, 2))
						{
							printf("%d %c", bestMove.x, bestMove.y + '@');          //�����з��ɹ�������ƽ̨
							printf("   ���ߣ�'m' or 'i'\n");
						}
						else                                         //���ɹ����Լ�pass
						{
							printf("passed\n");
						}
					}
					else if (strcmp(msg, "take") == 0)
					{
						SMove moveList[81];                         //�Լ�����,��ȡ������Ŀ
						printf("������Ŀ��");
						scanf("%d", &numTi);
						player[BLACK].total -= numTi;
						for (int k = 0; k < numTi; k++)
						{
							printf("�������꣺");
							Sleep(50);
							fflush(stdin);
							scanf("%d%d", &x, &y);
							moveList[k].x = x;
							moveList[k].y = y;
						}
						for (int i = 0; i < numTi; i++)
						{
							board[moveList[i].x][moveList[i].y] = NOSTONE;
						}
						//�Լ�֪������ҲӦ������
						PrintBoard();
						printf("������'go' or 'passed' or 'taked'\n");
					}
					else if (strcmp(msg, "taked") == 0)               //�Է�����,��ȡ������Ŀ
					{
						SMove moveList[81];
						printf("��������Ŀ��");
						scanf("%d", &numTi);
						player[WHITE].total -= numTi;                //��ȡ�Լ����б������	    
						for (int k = 0; k < numTi; k++)
						{
							printf("���������꣺");
							Sleep(50);
							fflush(stdin);
							scanf("%d%d", &x, &y);
							moveList[k].x = x;
							moveList[k].y = y;
							if (board[x - 1][y] == NOSTONE)            //��������ӵı߽����̽�⣬����ǿգ��϶��ǶԷ�����
							{
								board[x - 1][y] = BLACK;
								player[BLACK].know++;
							}
							if (board[x + 1][y] == NOSTONE)
							{
								board[x + 1][y] = BLACK;
								player[BLACK].know++;
							}
							if (board[x][y - 1] == NOSTONE)
							{
								board[x][y - 1] = BLACK;
								player[BLACK].know++;
							}
							if (board[x][y + 1] == NOSTONE)
							{
								board[x][y + 1] = BLACK;
								player[BLACK].know++;
							}
						}
						for (int i = 0; i < numTi; i++)
						{
							board[moveList[i].x][moveList[i].y] = NOSTONE;
						}
						PrintBoard();
						printf("������'go' or 'passed'\n");
					}
					else if (strcmp(msg, "passed") == 0)              //�Է�pass
					{
						player[WHITE].know = player[BLACK].total;
					}
					else if (strcmp(msg, "undo") == 0)
					{
						Undo();
						printf("������'i' or 'm'\n");
					}
					else
					{
						printf("Error Input!!!\n");
						PrintBoard();
					}

				}
			}
		}
	}
	return 0;
}

void record()//��¼�ϴε�����λ����Ϣ
{
	long i, j;
	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			undo_board[i][j] = board[i][j];
			undo_board_know[i][j] = board_know[i][j];
		}
	}
	for (i = 0; i < 3; i++) {
		undo_player[i] = player[i];
	}
}

void Undo()//�������ص��ϴ�����λ��(�����ʱ����)
{
	long i, j;
	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			board[i][j] = undo_board[i][j];
			board_know[i][j] = undo_board_know[i][j];
		}
	}
	for (i = 0; i < 3; i++)
		player[i] = undo_player[i];
}


void InitGame()//��ʼ����Ϸ
{
	memset(player, 0, sizeof(player));//��ʼ�����
	memset(board, 0, sizeof(board));//��ʼ������
	memset(board_know, 0, sizeof(board_know));//��ʼ����̽����
	memset(&bestMove, 0, sizeof(bestMove));//��ʼ�����Ž�
	for (long i = 0; i < 11; i++)
	{
		board[i][0] = BORDER;
		board[0][i] = BORDER;
		board[i][10] = BORDER;
		board[10][i] = BORDER;
	}
}

void PrintBoard()//��������
{
	printf("  ");
	char ch = 'A';
	for (long j = 1; j < 10; j++)
	{
		printf("   %c", ch);
		ch++;
	}
	printf("%s", "\n  ���������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ�������\n");
	for (long i = 0; i < 9; i++)
	{
		printf("%d %s", i + 1, "��");
		for (long j = 0; j < 9; j++)
		{
			if (board[i + 1][j + 1] == 1)
				printf("%s", " ��");
			else if (board[i + 1][j + 1] == 2)
				printf("%s", " ��");
			else
				printf("%s", "   ��");
		}
		printf("%s", "\n");
		if (i == 8)
			printf("%s", "  ���������ة������ة������ة������ة������ة������ة������ة������ة�������\n");
		else
			printf("%s", "  ���������੤�����੤�����੤�����੤�����੤�����੤�����੤�����੤������\n");
	}
}


#endif