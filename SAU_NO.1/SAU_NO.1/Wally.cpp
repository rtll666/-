#ifndef	_WALLY_CPP_
#define	_WALLY_CPP_
#include "wally.h"
#include "Define.h"


int sfdy = 1;
int fatal(char* message)
{
	fprintf(stderr, "\n?!fatal error--%s\n", message);
	return 0;

}
int panic(const char* message)
{
	fprintf(stderr, "\n?!panic--%s\n", message); return 0;
}
int rng(int n)
{
	static int seed = 0x1231;
	int r;
	seed = (seed * 11 + 15) & 0x7FFF;
	r = (((long)seed) * n) / (0x7FFF + 1);
	return r;
}
int initgame()
{
	register int x, y, j, * h;
	for (x = 0; x < edge; ++x)
		for (y = 0; y < edge; ++y)
			theboard[x][y] = EMPTY;
	thegame.kox = thegame.koy = (-1);
	thegame.tur = 1;
	if (edge < sizeof(nhandicap) / sizeof(int) && nhandicap[edge])
		thegame.pla = WWHITE;
	else
		thegame.pla = WBLACK;
	thegame.qpa = 0;
	lex = ley = (-1000);
	if (edge <= sizeof(nhandicap) / sizeof(int))
	{
		for (h = handicap[edge], j = nhandicap[edge]; j; --j)
		{
			x = *h++;
			y = *h++;
			assert(onboard(x, y));
			assert(EMPTY == theboard[x][y]);
			theboard[x][y] = EMPTY;

		}
	}
	return 0;
}
int remove(register int x, register int y)
{
	register int color;
	assert(onboard(x, y));
	color = theboard[x][y];
	assert(WBLACK == color || WWHITE == color);
	theboard[x][y] = EMPTY;

	if (onboard(x, y + 1) && color == theboard[x][y + 1])
		remove(x, y + 1);
	if (onboard(x, y - 1) && color == theboard[x][y - 1])
		remove(x, y - 1);
	if (onboard(x + 1, y) && color == theboard[x + 1][y])
		remove(x + 1, y);
	if (onboard(x - 1, y) && color == theboard[x - 1][y])
		remove(x - 1, y);
	return 0;
}
int capture(int p, int* capx, int* capy)
{
	register int j, rv = 0;
	register wgroup* g;
	for (g = wgroups, j = 0; j < nwgroups; ++g, ++j)
		if (p == g->color && 0 == g->nliberties)
		{
			rv += g->nstones;
			*capx = g->x;
			*capy = g->y;
			remove(g->x, g->y);
		}
	return rv;
}
int movedone()
{
	thegame.pla = nextp(thegame.pla);  ++thegame.tur; return 0;
}
int count(register int x, register int y, register wgroup* thiswgroup, wboard scratch, int mark)
{
	register int* bxy, * sxy;

endrecurse:
	assert(onboard(x, y));
	assert(thiswgroup->color == theboard[x][y]);
	assert(thiswgroup->nstones >= 0);
	assert(thiswgroup->nliberties >= 0);
	assert(mark != scratch[x][y]);
	bxy = &(theboard[x][y]);
	sxy = &(scratch[x][y]);
	++(thiswgroup->nstones);
	*sxy = mark;
	y = y - 1;
	bxy -= 1;
	sxy -= 1;
	assert(&theboard[x][y] == bxy);
	assert(&scratch[x][y] == sxy);
	if (y >= 0)
		if (thiswgroup->color == *bxy)
		{
			if (*sxy != mark)
				count(x, y, thiswgroup, scratch, mark);
		}
		else if (EMPTY == *bxy)
		{
			if (*sxy != mark)
			{
				*sxy = mark;
				++(thiswgroup->nliberties);
			}
		}
	y = y + 2;
	bxy += 2;
	sxy += 2;
	assert(&theboard[x][y] == bxy);
	assert(&scratch[x][y] == sxy);
	if (y < edge)
		if (thiswgroup->color == *bxy)
		{
			if (*sxy != mark)
				count(x, y, thiswgroup, scratch, mark);
		}
		else if (EMPTY == *bxy)
		{
			if (*sxy != mark)
			{
				*sxy = mark;
				++(thiswgroup->nliberties);
			}
		}
	y = y - 1;
	x = x - 1;
	bxy -= EDGE + 1;
	sxy -= EDGE + 1;
	assert(&theboard[x][y] == bxy);
	assert(&scratch[x][y] == sxy);
	if (x >= 0)
		if (thiswgroup->color == *bxy)
		{
			if (*sxy != mark)
				count(x, y, thiswgroup, scratch, mark);
		}
		else if (EMPTY == *bxy)
		{
			if (*sxy != mark)
			{
				*sxy = mark;
				++(thiswgroup->nliberties);
			}
		}
	x = x + 2;
	bxy += 2 * EDGE;
	sxy += 2 * EDGE;
	assert(&theboard[x][y] == bxy);
	assert(&scratch[x][y] == sxy);
	if (x < edge)
		if (thiswgroup->color == *bxy)
		{
			if (*sxy != mark)
				goto endrecurse;
		}
		else if (EMPTY == *bxy)
		{
			if (*sxy != mark)
			{
				*sxy = mark;
				++(thiswgroup->nliberties);
			}
		}
	return 0;
}
int makewgroups()
{
	register int x, y;
	wboard scratch;
	nwgroups = 0;
	{
		register int* s;
		for (s = scratch[0], x = 0; x < EDGE * EDGE; ++x)
			*s++ = 0;
	}
	{
		register int* bxy = (int*)theboard, * sxy = (int*)scratch;
		register wgroup* thiswgroup = wgroups;
		for (x = 0; x < edge; ++x, bxy += EDGE - edge, sxy += EDGE - edge)
			for (y = 0; y < edge; ++y, ++bxy, ++sxy)
			{
				assert(&(theboard[x][y]) == bxy);
				assert(&(scratch[x][y]) == sxy);
				assert(&(wgroups[nwgroups]) == thiswgroup);
				if ((WBLACK == *bxy || WWHITE == *bxy) && 0 == *sxy)
				{
					thiswgroup->color = *bxy;
					thiswgroup->x = x;
					thiswgroup->y = y;
					thiswgroup->nliberties = 0;
					thiswgroup->nstones = 0;
					count(x, y, thiswgroup, scratch, 1 + thiswgroup - wgroups);
					++thiswgroup;
					++nwgroups;
				}
			}
	}
	return 0;
}
int placestone(int x, int y, int p)
{
	int ncap, capx, capy;
	assert(onboard(x, y));
	assert(WBLACK == p || WWHITE == p);
	assert(EMPTY == theboard[x][y]);

	theboard[x][y] = p;
	makewgroups();
	ncap = capture(nextp(p), &capx, &capy);
	thegame.kox = thegame.koy = (-1);
	if (1 == ncap)
	{
		register int j, * ip;  wgroup g;
		wboard scratch;
		for (ip = (int*)scratch, j = EDGE * EDGE; j--; ) *ip++ = 0;
		g.color = theboard[x][y];
		g.nstones = 0;
		g.nliberties = 0;
		g.x = x;
		g.y = y;
		count(x, y, &g, scratch, 1);
		if (1 == g.nstones && 1 == g.nliberties)
		{
			thegame.kox = capx; thegame.koy = capy;
		}
	}
	if (ncap)
		makewgroups();
	ncap = capture(p, &capx, &capy);
	assert(WWHITE == p || 0 == ncap);
	return 0;
}
int sortv(wgroup** p, int n)
{
	register int uns;
	register wgroup* t,
		** ip;
	register int j;
	do
	{
		uns = 0;
		for (j = 0, ip = p; j < n - 1; ++j, ++ip)
		{
			t = ip[1];
			if (t->nliberties < (*ip)->nliberties ||
				(t->nliberties == (*ip)->nliberties && t->nstones > (*ip)->nstones))
			{
				uns = 1;
				ip[1] = *ip;
				*ip = t;
			}
		}
	} while (uns);
	return 0;
}
int subj_lib(int x, int y)
{
	wboard scratch;
	wgroup t;
	assert(onboard(x, y));
	assert(EMPTY == theboard[x][y]);
	theboard[x][y] = WBLACK;
	{ register int* s, j;
	for (j = EDGE * EDGE, s = (int*)scratch; j--; )
		*s++ = 0;
	}
	t.color = WBLACK;
	t.x = x;
	t.y = y;
	t.nliberties = 0;
	t.nstones = 0;
	count(x, y, &t, scratch, 1);
	theboard[x][y] = EMPTY;
	return t.nliberties;
}
int pattern1(int* u, wboard masks, wboard movehere)
{
	register int* is, * iis;/*pointers into patterns[]; or scratch*/
	register int j;	/*& into a particular pattern, # points remaining*/
	register int x, y;	/*current position we're trying to match pattern to*/
	register int xs, ys;	/*position of a point from a pattern*/
	int ua;		/*urgency and adjustment for this move*/
	int thispat;		/*which pattern in the table are we currently */
			  /* trying to match?*/


	for (is = patterns, thispat = 0; PATTERN == *is; is += 3 + 3 * (is[1]), ++thispat)
	{
		for (x = 0; x < edge; ++x)
			for (y = 0; y < edge; ++y)
			{
				if (F_EMPTY == masks[x][y] && 0 == ko(x, y)
					&& (thegame.kox != x || thegame.koy != y))
				{
					for (iis = is + 1, j = *iis++, ua = *iis++; j; --j)
					{
						xs = *iis++;
						ys = *iis++;
						if (onboard(x + xs, y + ys))
						{
							if (0 == (masks[x + xs][y + ys] & *iis++)) goto mismatch;
						}
						else
						{
							if (0 == (F_OFF & *iis++)) goto mismatch;
						}
					}
					/*If we fall through here, then we matched a pattern.*/
					/*Compute adjusted urgency.*/
					if (abs(x - lex) <= 1 && abs(y - ley) <= 1)
						ua -= 4;	            /*Important to oppose enemy's last move.*/
					for (xs = (-2); xs <= 2; ++xs)
						for (ys = (-2); ys <= 2; ++ys)
							if (onboard(x + xs, y + ys))/*Important to move to */
								++ua;		    /* uncrowded parts of the board.*/
					if (ua < *u &&		    /*If this pattern is most urgent so far */
						0 == intoatari(x, y))  /* and the move is not futile */
					{
						*u = ua;	 	    /*Replace old */
						movehere[x][y] = ua;     /* urgency values.*/
						patnum = thispat;	    /*Record pattern # for debugging.*/
						pgoodmoves = goodmoves;  /*Reinit goodmoves[].*/
						goto intogoodmoves;
					}
					else if (ua == *u &&	    /*If there's no better pattern */
						ua < movehere[x][y] /* and it's the best move here */
						&& !intoatari(x, y)) /*and not futile*/
					{
						movehere[x][y] = ua;	/*Mark as best move here.*/
					intogoodmoves:;	/*Put it into goodmoves[].*/
						*pgoodmoves++ = x;  *pgoodmoves++ = y;
					}
				}
			mismatch:;
			}
	}
	if (PATTEND != *is)
	{
		fprintf(stderr, "?error in pattern table, pattern # %d\n", thispat);
		panic("programmer error in pattern table");
	}return 0;
}
int pattern(int* chosenx, int* choseny, int* urgency, wboard movehere)
{
	register int x, y, t, j, * is;
	wboard scratch;


	/*Translate the board to flags for easy comparison with pattern table.*/
	for (x = 0; x < edge; ++x)
		for (y = 0; y < edge; ++y)
			scratch[x][y] = flookup[theboard[x][y]];

	*urgency = BIGU;		/*No big move so far.*/
	pgoodmoves = goodmoves;	/*No moves so far.*/
	patnum = (-1);			/*For debugging: no pattern # so far.*/

	pattern1(urgency, scratch, movehere);
	/*Find matches to untransformed table.*/

/*Invert y coordinates in pattern table.*/
	for (is = patterns; PATTERN == *is; )
	{
		for (j = *++is, is += 2; j--; )
		{
			is += 1;
			*is = (-*is);
			is += 2;
		}
	}
	assert(PATTEND == *is);


	pattern1(urgency, scratch, movehere);
	/*Find matches to transformed table.*/

/*Invert x coordinates in pattern table.*/
	for (is = patterns; PATTERN == *is; )
	{
		for (j = *++is, is += 2; j--; )
		{
			;
			*is = (-*is);
			is += 3;
		}
	}
	assert(PATTEND == *is);

	pattern1(urgency, scratch, movehere);
	/*Find matches to transformed table.*/

/*Invert y coordinates in pattern table.*/
	for (is = patterns; PATTERN == *is; )
	{
		for (j = *++is, is += 2; j--; )
		{
			is += 1;
			*is = (-*is);
			is += 2;
		}
	}
	assert(PATTEND == *is);

	pattern1(urgency, scratch, movehere);
	/*Find matches to transformed table.*/

/*Exchange x and y coordinates in pattern table.*/
	for (is = patterns; PATTERN == *is; )
	{
		for (j = *++is, is += 2; j--; )
		{
			t = *is;
			*is = is[1];
			is[1] = t;
			is += 3;
		}
	}
	assert(PATTEND == *is);

	pattern1(urgency, scratch, movehere);
	/*Find matches to transformed table.*/

/*Invert y coordinates in pattern table.*/
	for (is = patterns; PATTERN == *is; )
	{
		for (j = *++is, is += 2; j--; )
		{
			is += 1;
			*is = (-*is);
			is += 2;
		}
	}
	assert(PATTEND == *is);

	pattern1(urgency, scratch, movehere);
	/*Find matches to transformed table.*/

/*Invert x coordinates in pattern table.*/
	for (is = patterns; PATTERN == *is; )
	{
		for (j = *++is, is += 2; j--; )
		{
			;
			*is = (-*is);
			is += 3;
		}
	}
	assert(PATTEND == *is);

	pattern1(urgency, scratch, movehere);
	/*Find matches to transformed table.*/

/*Invert y coordinates in pattern table.*/
	for (is = patterns; PATTERN == *is; )
	{
		for (j = *++is, is += 2; j--; )
		{
			is += 1;
			*is = (-*is);
			is += 2;
		}
	}
	assert(PATTEND == *is);

	pattern1(urgency, scratch, movehere);
	/*Find matches to transformed table.*/

/*Exchange x and -y coordinates in pattern table.*/
	for (is = patterns; PATTERN == *is; )
	{
		for (j = *++is, is += 2; j--; )
		{
			t = (-*is);
			*is = (-is[1]);
			is[1] = t;
			is += 3;
		}
	}
	assert(PATTEND == *is);

	/*Try to pick a move from the table of equally good ones.*/
	{ int nmoves = (pgoodmoves - goodmoves) / 2;
	if (0 == nmoves) return 0;
	else
	{
		int whichmove = rng(nmoves);
		*chosenx = goodmoves[2 * whichmove];
		*choseny = goodmoves[2 * whichmove + 1];
	}
	}

	/*We'd better not have decided on an illegal move.*/
	if (*urgency < BIGU)
		if (EMPTY != theboard[*chosenx][*choseny] || ko(*chosenx, *choseny))
			panic("illegal move selected in pattern()");

}
int attack(wgroup* g, int* rx, int* ry, int ml)
{
	int bestx, besty;
	int edist;
	register int x, y;
	wboard scratch;
	{ register int j, * is;
	for (j = EDGE * EDGE, is = (int*)scratch; j--; )
		*is++ = 0;
	}
	g->nstones = 0;
	g->nliberties = 0;
	count(g->x, g->y, g, scratch, 1);
	assert(g->nliberties >= 0);
	edist = edge * 10;
	for (x = 0; x < edge; ++x)
		for (y = 0; y < edge; ++y)
			if (EMPTY == theboard[x][y] && scratch[x][y]
				&& (thegame.kox != x || thegame.koy != y))
				if (subj_lib(x, y) >= ml)
				{
					register int toedge = x;
					if (toedge > edge - 1 - x) toedge = edge - 1 - x;
					if (toedge > y) toedge = y;
					if (toedge > edge - 1 - y) toedge = edge - 1 - y;
					if (abs(10 * toedge - 19) < edist)
					{
						edist = abs(10 * toedge - 21);
						bestx = x;  besty = y;
					}
				}
	if (edist < edge * 10)
	{
		*rx = bestx;  *ry = besty;
		return 0;
	}
	else
	{
		return 1;
	}
}
int escape(wgroup* g, int* rx, int* ry)
{
	register int x, y;
	wboard scratch;
	{ register int j, * is;
	for (j = EDGE * EDGE, is = (int*)scratch; j--; )
		*is++ = 0;
	}
	g->nstones = 0;
	g->nliberties = 0;
	count(g->x, g->y, g, scratch, 1);
	assert(g->nliberties >= 0);
	for (x = 0; x < edge; ++x)
		for (y = 0; y < edge; ++y)
			if (EMPTY == theboard[x][y] && scratch[x][y]
				&& (thegame.kox != x && thegame.koy != y))
				if (0 == intoatari(x, y))
				{
					*rx = x;  *ry = y;  return 0;
				}
	return 1;
}
int mymove()
{
	register int j;
	register wgroup* g;
	int x, y;
	wgroup* gt[EDGE * EDGE];
	wgroup** fs, ** es;
	register wgroup** igt;
	int nf, ne;
	int upattern, patternx, patterny;
	wboard scratch;
	{ register int* ip;
	for (ip = (int*)scratch, j = EDGE * EDGE; j--; )
		*ip++ = BIGU;
	}
	pattern(&patternx, &patterny, &upattern, scratch);
	for (j = 0, g = wgroups, nf = 0, fs = igt = gt; j < nwgroups; ++j, ++g)
		if (WBLACK == g->color)
		{
			++nf;
			*igt++ = g;
		}
	for (j = 0, g = wgroups, ne = 0, es = igt; j < nwgroups; ++j, ++g)
		if (WWHITE == g->color)
		{
			++ne;
			*igt++ = g;
		}
	sortv(fs, nf);
	sortv(es, ne);
	if (upattern < 16)
	{
	movepattern:
		x = patternx;
		y = patterny;
		goto movexy;
	}
	while (ne && 1 == (*es)->nliberties)
	{
		if (0 == attack(*es, &x, &y, 0))
		{
			goto movexy;
		}
		else
		{
			++es; --ne;
		}
		if (upattern < 24) goto movepattern;
		while (nf && 1 == (*fs)->nliberties)
		{
			if (escape(*fs, &x, &y))
			{
				++fs; --nf;
			}
			else
			{
				if ((0 == x || edge - 1 == x || 0 == y || edge - 1 == y) && (2 >= subj_lib(x, y)))
				{
					++fs; --nf;  continue;
				}
				goto movexy;
			}
		}
		if (upattern < 34) goto movepattern;
		while (ne && 2 == (*es)->nliberties)
		{
			if (attack(*es, &x, &y, 2))
			{
				ne--; ++es;
			}
			else
			{
				goto movexy;
			}
		}
		if (upattern < BIGU) goto movepattern;
		while (ne)
		{
			if (attack(*es, &x, &y, 3))
			{
				--ne; ++es;
			}
			else
			{
				goto movexy;
			}
		}
		sfdy = 0;
		thegame.kox = thegame.koy = (-1);
		movedone();
		if (thegame.qpa) return BOTHPASS;
		else
		{
			thegame.qpa = 1;
			return PASS;
		}
	movexy:
		placestone(x, y, WBLACK);
		wx = x; wy = y;
		thegame.qpa = 0;
		movedone();
		return 0;
	}
}
int enemymove()
{
	int s = 1;
	movedone();
	return 0;
}
int refresh()
{
	int x, y;
	for (x = 0; x < edge; ++x)
	{
		for (y = 0; y < edge; ++y)
		{
			if (board[x + 1][y + 1] == WHITE)
				theboard[y][x] = WWHITE;
			else if (board[x + 1][y + 1] == BLACK)
				theboard[y][x] = WBLACK;
			else if (board[x + 1][y + 1] == NOSTONE)
				theboard[y][x] = EMPTY;
		}
	}return 0;
}
int wally(void)
{
	int maybe = 0;
	int rvalue;
	int start = 2;
	initgame();
	if (flag == 2)
		thegame.pla = WBLACK;
	while (start)
	{

		if (WBLACK == thegame.pla)
		{
			refresh();
			rvalue = mymove();
		}
		else if (WWHITE == thegame.pla)
		{
			rvalue = enemymove();
			refresh();
		}
		start--;
	}
	return 0;
}

#endif
