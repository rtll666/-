#pragma once
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define ASSERT 1	
#define BIGU 10000	
#define RESIGN (-2)	
#define PASS (-1)	
#define BOTHPASS (-3)	
#define EDGE 23		
int edge = 9;
#define NPLAYERS 2	
#define abs(i) ((i)>=0?(i):-(i))
#define on1board(x) (0<=(x)&&(x)<edge)
#define onboard(x,y) (on1board(x)&&on1board(y))
#define onedge1(x) (0==(x)||edge-1==(x))
#define onedge(x,y) (onedge1(x)||onedge1(y))
#define WBLACK 0
#define WWHITE 1
#define EMPTY 2
#define F_WBLACK 1	
#define F_WWHITE 2
#define F_EMPTY 4	
#define F_OFF   8	
int flookup[] = { F_WBLACK, F_WWHITE, F_EMPTY };
int evenmode = 0;
int    flag = 0;
#define ko(x,y) (thegame.kox==(x)&&thegame.koy==(y))
#define nextp(p) (WBLACK==(p)?WWHITE:WWHITE==(p)?WBLACK:\
	panic("illegal input to nextp()"))
#define lettercol(x) (							\
	  (0<=(x)&&(x)<=7) ? 'a'+(x) : (7<(x)&&(x)<edge) ? 'a'+(x)+1 :	\
	  panic("illegal lettercol()") )
#define lowercase(c) ('A'<=(c)&&(c)<='Z'?(c)-'A'+'a':(c))
char WWHITEname[] = "WWHITE", WBLACKname[] = "WBLACK";
#define pname(c) (WBLACK==(c)?WBLACKname:WWHITE==(c)?WWHITEname:\
	(panic("illegal input to pname()"),""))
#define intoatari(x,y) (subj_lib(x,y)<=1)
#define assert(q) ((q)?1:(1))
#define TAB 8
char* ofname;
FILE* ofile = 0;
char version[] = "2.1";
typedef int wboard[EDGE][EDGE];
wboard theboard;
struct thegame
{
	int kox, koy;
	int pla;
	int tur;
	int qpa;
} thegame;
typedef struct wgroup
{
	int	color,
		nliberties,
		nstones,
		x, y;
} wgroup;
wgroup wgroups[EDGE * EDGE];
int nwgroups;
int handi9[] = { 2, 2,	6, 2,	2, 6,	6, 6 };
int handi13[] = { 2, 2,	2, 6,	2, 10,
		 6, 2,	6, 6,	6, 10,
		10, 2,	10, 6, 	10, 10 };
int handi19[] = { 15, 3, 	15, 9,		15, 15,
		 9,  3,		9, 9,		9, 15,
		 3, 3,		3, 9,		3, 15 };
int nhandicap[] = { 0, 0, 0, 0, 0,
				  0, 0, 0, 0, sizeof(handi9) / (2 * sizeof(int)),
				  0, 0, 0, sizeof(handi13) / (2 * sizeof(int)), 0,
				  0, 0, 0, 0, sizeof(handi19) / (2 * sizeof(int))
};
int* handicap[] = { 0, 0, 0, 0, 0,
				  0, 0, 0, 0, handi9,
				  0, 0, 0, handi13, 0,
				  0, 0, 0, 0, handi19
};
#define PATTERN 12345	
#define PATTEND 7171	
int patterns[] =
{
	PATTERN,
   4, 24,
  -1, 0, F_WBLACK | F_OFF,
   1, 0, F_WBLACK,
   0, -1, F_WWHITE,
   0, 1, F_EMPTY | F_WWHITE,

  PATTERN, 3, 22,
  -1, 0, F_WBLACK,
   1, -1, F_WBLACK,
   0, -1, F_WWHITE,

  PATTERN, 5, 26,
  -1, 1, F_WBLACK | F_OFF,
   1, 1, F_WBLACK,
   0, 1, F_WWHITE,
   1, 0, F_EMPTY,
   0, -3, F_EMPTY | F_WWHITE,

  PATTERN, 4, 26,
  -1, 1, F_WBLACK | F_OFF,
  1, 1, F_WBLACK,
  1, 0, F_WBLACK,
  0, 1, F_WWHITE,

  PATTERN, 6, 24,
  -1, 0, F_WBLACK,
  0, -1, F_WWHITE,
  1, 0,  F_EMPTY,
  1, -1, F_EMPTY,
  2, 0,  F_WBLACK,
  0, 1, F_EMPTY | F_WWHITE,

  PATTERN, 5, 27,
  -1, 0, F_WBLACK,
  0, -1, F_WWHITE,
  1, 0,  F_EMPTY,
  2, 0,  F_OFF,
  0, 1, F_EMPTY | F_WWHITE,

  PATTERN, 5, 24,
  -2, 0, F_WBLACK,
  -1, 0, F_EMPTY,
  0, -1, F_WWHITE,
  1,  0, F_EMPTY,
  2,  0, F_WBLACK,

  PATTERN, 5, 30,
  -2, 0, F_WBLACK,
  -1, 0, F_EMPTY,
  0, -1, F_WWHITE,
  1,  0, F_EMPTY,
  2,  0, F_OFF,

  PATTERN, 7, 26,
   -1, 0, F_WBLACK,
   1, -1, F_WWHITE,
   1, 0, F_WBLACK,
   2, 0, F_WWHITE,
   1, 1, F_EMPTY,
   0, 1, F_EMPTY | F_WWHITE,
   0, -1, F_EMPTY | F_WWHITE,

  PATTERN, 8, 26,
  -1, -1, F_WBLACK | F_EMPTY,
  -2, 0, F_WBLACK,
  -1, 0, F_EMPTY,
  -1, 1, F_WBLACK,
   0, 1, F_WWHITE,
   0, -1, F_WBLACK | F_EMPTY,
  -2, -1, F_WBLACK | F_EMPTY,
  -2, 1, F_WBLACK | F_EMPTY,

  PATTERN, 4, 26,
  0, 2,  F_EMPTY,
  -1, 1, F_WBLACK,
  1, 1,  F_WBLACK,
  1, 0,  F_WWHITE,

  PATTERN, 4, 24,
  0, 1, F_EMPTY,
  -1, -1, F_WWHITE,
  0, -1, F_WBLACK,
  1, -1, F_WWHITE,

  PATTERN, 4, 24,
  0, 1, F_EMPTY,
  -1, -1, F_WWHITE,
  0, -1, F_WBLACK,
  1, 0, F_WWHITE,

  PATTERN, 4, 26,
  0, 1, F_EMPTY,
  -1, 1, F_WWHITE,
  1, 1, F_WWHITE,
  0, 2, F_WWHITE,

  PATTERN, 8, 24,
  -2, 0, F_EMPTY | F_WBLACK,
  0, -1, F_EMPTY,
  1, -2, F_OFF,
  1, -1, F_EMPTY,
  1, 0, F_WBLACK,
  1, 1, F_WWHITE,
  2, -1, F_EMPTY,
  1, 0, F_WWHITE,

  PATTERN, 8, 28,
  -1, 0, F_EMPTY,
  0, -1, F_EMPTY,
  0, 1, F_WBLACK,
  1, 0, F_WBLACK,
  1, 1, F_WWHITE,
  2, 0, F_WWHITE,
  -1, 1, F_EMPTY,
  1, -1, F_EMPTY,

  PATTERN, 8, 23,
  0, 2, F_WBLACK,
  1, 2, F_WBLACK,
  2, 0, F_WBLACK,
  2, 1, F_WBLACK,
  1, 0, F_EMPTY,
  0, 1, F_EMPTY,
  -1, 0, F_EMPTY | F_WBLACK | F_WWHITE,
  0, -1, F_EMPTY | F_WWHITE,

  PATTERN, 8, 24,
  0, 2, F_WWHITE,
  1, 2, F_WWHITE,
  2, 0, F_WWHITE,
  2, 1, F_WWHITE,
  1, 0, F_EMPTY,
  0, 1, F_EMPTY,
  -1, 0, F_EMPTY | F_WWHITE | F_WBLACK,
  0, -1, F_EMPTY | F_WBLACK,

  PATTERN, 8, 34,
  -1, 1, F_WBLACK,
  -1, 0, F_WBLACK,
  0, 2, F_WBLACK,
  0, 1, F_EMPTY,
  1, 1, F_WBLACK,
  1, 2, F_WBLACK,
  -1, 2, F_WBLACK | F_EMPTY,
  0, -1, F_WWHITE | F_EMPTY,

  PATTERN, 7, 34,
  -1, 1, F_WBLACK,
  -1, 0, F_WBLACK | F_EMPTY,
  -1, 2, F_WBLACK | F_EMPTY,
  0, 2, F_WBLACK,
  0, 1, F_EMPTY,
  1, 1, F_WBLACK,
  1, 2, F_WBLACK | F_EMPTY,

  PATTERN, 10, 27,
  -2, 0, F_WBLACK,
  2, 0, F_WBLACK,
  -1, 0, F_EMPTY,
  1, 0, F_EMPTY,
  -1, 1, F_EMPTY,
  0, 1, F_EMPTY,
  1, 1, F_EMPTY,
  -1, -1, F_EMPTY,
  0, -1, F_EMPTY,
  1, -1, F_EMPTY,

  PATTERN, 6, 25,
  -1, 1, F_WBLACK,
  -1, -1, F_WBLACK,
  1, 1, F_WBLACK,
  0, 1, F_EMPTY,
  -1, 0, F_EMPTY,
  -2, 0, F_EMPTY | F_WBLACK | F_OFF,

  PATTERN, 5, 35,
  -1, 0, F_EMPTY,
  0, 1, F_WWHITE,
  1, 1, F_WBLACK,
  0, -1, F_OFF,
  0, 1, F_WBLACK | F_EMPTY,

  PATTERN,  5, 40,
  -1, 0, F_EMPTY,
  -1, 1, F_WWHITE,
  0, 1, F_WBLACK,
  0, -1, F_OFF,
  1, 0, F_WWHITE | F_EMPTY,

  PATTERN, 6, 38,
  -1, 1, F_WWHITE,
  1, 1, F_WBLACK,
  0, 1, F_EMPTY,
  1, 0, F_EMPTY,
  0, -1, F_EMPTY,
  0, -2, F_OFF | F_WBLACK,

  PATTERN, 6, 38,
  -1, 0, F_WWHITE,
  1, 1, F_WBLACK,
  0, 1, F_EMPTY,
  1, 0, F_EMPTY,
  0, -1, F_EMPTY,
  0, -2, F_OFF | F_WBLACK,

  PATTERN, 11, 29,
  -2, 0, F_EMPTY | F_WBLACK,
  0, -1, F_EMPTY,
  1, -2, F_OFF,
  1, -1, F_EMPTY,
  1, 0, F_WBLACK,
  1, 1, F_WWHITE,
  2, -1, F_EMPTY,
  -1, -2, F_EMPTY | F_OFF,
  0, -2, F_EMPTY | F_OFF,
  1, -2, F_EMPTY | F_OFF,
  1, 0, F_WWHITE,

  PATTERN, 12, 38,
  -1, 0, F_WWHITE,
  1, 1, F_WBLACK,
  0, 1, F_EMPTY | F_WBLACK,
  1, 0, F_EMPTY | F_WWHITE,
  0, -3, F_OFF,
  0, -1, F_EMPTY | F_WBLACK,
  0, 2,  F_EMPTY | F_WBLACK | F_OFF,
  1, -1, F_EMPTY | F_WBLACK | F_OFF,
  2, -1, F_EMPTY | F_WBLACK | F_OFF,
  0, -2, F_EMPTY | F_WBLACK | F_OFF,
  1, -2, F_EMPTY | F_WBLACK | F_OFF,
  2, -2, F_EMPTY | F_WBLACK | F_OFF,

  PATTERN, 12, 38,
  -1, 0, F_WWHITE,
  0, 1, F_WBLACK,
  1, 1, F_EMPTY | F_WBLACK,
  1, 0, F_EMPTY | F_WWHITE,
  0, -3, F_OFF,
  0, -1, F_EMPTY | F_WBLACK,
  0, 2,  F_EMPTY | F_WBLACK | F_OFF,
  1, -1, F_EMPTY | F_WBLACK | F_OFF,
  2, -1, F_EMPTY | F_WBLACK | F_OFF,
  0, -2, F_EMPTY | F_WBLACK | F_OFF,
  1, -2, F_EMPTY | F_WBLACK | F_OFF,
  2, -2, F_EMPTY | F_WBLACK | F_OFF,

  PATTERN, 15, 25,
  0, 1, F_EMPTY,
  0, 2, F_EMPTY,
  1, 0, F_EMPTY,
  1, 1, F_EMPTY,
  1, 2, F_EMPTY,
  2, 0, F_EMPTY,
  2, 1, F_EMPTY,
  2, 2, F_EMPTY,
  4, 3, F_OFF,
  3, 4, F_OFF,
  -1, 0, F_EMPTY,
  -1, 1, F_EMPTY,
  0, -1, F_EMPTY,
  1, -1, F_EMPTY,
  3, 3, F_EMPTY | F_WWHITE | F_WBLACK,

  PATTERN, 10, 29,
  -1, 0, F_EMPTY,
  -1, 1, F_EMPTY,
  0, -1, F_EMPTY,
  1, -1, F_EMPTY,
  0, 1, F_EMPTY,
  1, 0, F_EMPTY,
  1, 1, F_EMPTY,
  2, 2, F_EMPTY | F_WWHITE | F_WBLACK,
  3, 2, F_OFF,
  2, 3, F_OFF,

  PATTERN, 17, 29,
  0, 1, F_EMPTY,
  0, -1, F_EMPTY,
  1, 0, F_EMPTY,
  -1, 0, F_EMPTY,
  1, 1, F_EMPTY,
  1, -1, F_EMPTY,
  -1, 1, F_EMPTY,
  -1, -1, F_EMPTY,
  -1, 2, F_EMPTY,
  0, 2, F_EMPTY,
  1, 2, F_EMPTY,
  -1, -2, F_EMPTY,
  0, -2, F_EMPTY,
  1, -2, F_EMPTY,
  3, 0, F_WWHITE | F_WBLACK | F_EMPTY,
  4, 0, F_OFF | F_WBLACK,
  -2, 0, F_WWHITE | F_EMPTY,


  PATTERN, 12, 31,
  0, 1, F_EMPTY,
  0, -1, F_EMPTY,
  1, 0, F_EMPTY,
  -1, 0, F_EMPTY,
  1, 1, F_EMPTY,
  1, -1, F_EMPTY,
  -1, 1, F_EMPTY,
  -1, -1, F_EMPTY,
  -2, -1, F_EMPTY | F_WBLACK,
  2, -1, F_EMPTY | F_WBLACK,
  0, -2, F_EMPTY | F_WBLACK | F_WWHITE,
  0, -3, F_OFF,

  PATTERN, 22, 33,
  0, 1, F_EMPTY,
  0, -1, F_EMPTY,
  1, 0, F_EMPTY,
  -1, 0, F_EMPTY,
  1, 1, F_EMPTY,
  1, -1, F_EMPTY,
  -1, 1, F_EMPTY,
  -1, -1, F_EMPTY,
  2, -2, F_EMPTY,
  -2, -2, F_EMPTY,
  0, 2, F_WBLACK,
  0, -2, F_EMPTY,
  2, 0, F_EMPTY,
  -2, 0, F_EMPTY,
  2, 1, F_EMPTY,
  2, -1, F_EMPTY,
  -2, 1, F_EMPTY,
  -2, -1, F_EMPTY,
  1, -2, F_EMPTY,
  -1, -2, F_EMPTY,
  -1, 2, F_EMPTY | F_WWHITE,
  -2, 2, F_EMPTY | F_WWHITE,
  PATTEND
};
int patnum;
int lex, ley;
int goodmoves[2 * EDGE * EDGE];
int* pgoodmoves;
int wx = 0;
int wy = 0;
int fatal(char* message);
int panic(char* message);
int rng(int n);
int initgame();
int remove(register int x, register int y);
int capture(int p, int* capx, int* capy);
int movedone();
int count(register int x, register int y, register wgroup* thiswgroup, wboard scratch, int mark);
int makewgroups();
int placestone(int x, int y, int p);
int sortv(wgroup** p, int n);
int subj_lib(int x, int y);
int pattern1(int* u, wboard masks, wboard movehere);
int pattern(int* chosenx, int* choseny, int* urgency, wboard movehere);
int attack(wgroup* g, int* rx, int* ry, int ml);
int escape(wgroup* g, int* rx, int* ry);
int mymove();
int enemymove();
int refresh();
int wally(void);