/************************************************************************************
                                 PANKAJ KUMAR JHA
       				    01 MA 2011
				   SECD PROGRAM
*************************************************************************************/

/******************************SOME FUNCTIONS AND THEIR USES*************************/

/* pickup(): this function collects the garbage and puts it back on the free list */

/* ragpick(): It first initializes the MARKED array to FALSE, and then starts marking from the four available entry points into memory.  */

/* make(): this makes a CONS cell with given CAR and CDR */

/* INSTALL :  this function installs an alphanumeric atom into the STORE.*/


/**********************SECD MACHINE INTERPRETER-----HOW IT WORKS???******************/


/*THE OPCODES : stack operations for each opcode - this defines the SECD machine  */


/* M_LD : LD = 1 
 	S		E	(LD (i.j) . C)		D	
-->	(w . S)	 	E	C		       	D  
 	where w has been extracted from the ENVIRONMENT stack 	*/


/* M_LDC : LDC = 2 
	S 			E 	(LDC x . C)		D	
-->	(x . S)		E	C				D 	
	this implementation copies constant lists .. */


/* M_LDF : LDF = 3 
	This loads a closure - code + environment - on the stack, and continues.
	The next opcode, AP, sets things for function execution.
	S				E	(LDF C' . C)	D	
	-->	((C' . E) . S)	E	C				D	*/


/* M_AP : AP = 4
	This is the FUNCTION APPLICATION opcode.IT moves the function code to the CONTROL, ZEROS 
	the STACK, sets up the ENVIRONMENT, and saves all further
	computation instructions on the DUMP REGISTER. 
	((C' . E') v . S)	E			(AP . C)	D	
-->	NIL					(v . E')	C'			(S E C . D)		*/


/* M_RTN : RTN = 5
	This function assumes the top of the STACK contains the result of some
	computation - a function call -, and  we are now returning from it.
	(x)			E'	(RTN)	(S E C . D)		
-->	(x . S)		E	C		D	*/


/* M_CDR : CDR = 11
	This is the usual CDR instruction : takes all but the first element of 
	the top list of the stack and puts it back on top of the stack.
	((a . b) . S)	E	(CDR . C)	D
-->	(b . S) 		E 	C			D	*/



#include<iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "secd.h"

//SOME GLOBAL VARIABLES

unsigned long *atm= NULL,*num= NULL,*cell= NULL;
static pointer ff = 0, s, e, c, d, w, t, f, nil;
static int top=0;
static char *store = NULL;

typedef enum
{
	LD = 1, LDC, LDF, AP, RTN,DUM, RAP, SEL, JOIN, CAR,CDR, ATOM, CONS, EQ, ADD,
	SUB, MUL, DIV, REM, LEQ,STOP,QUOTE, IF, LAMBDA, LET, LETREC, APPLY
}interpreter;

//USING CONCEPT OF STORAGE
static pointer symbol(char *s);
static void init_storage(void)
{
	pointer i;
	sayyes(num== NULL && atm == NULL && cell == NULL);
	num= (unsigned long *)calloc((CELLS+31)/32, sizeof(long));
	sayyes(num);
	atm=(unsigned long *)calloc((CELLS+31)/32, sizeof(long));
	sayyes(atm);
	cell=(unsigned long *)calloc(CELLS, sizeof(long));
	sayyes(cell);
	ff = 0;
	for (i=1;i<CELLS;i++)
	{
		cdr_func(i,ff);
		ff = i;
	}
	top=0;
	sayyes(store == NULL);
	store = calloc(space,sizeof(char));
	sayyes(store);
	nil = symbol("\nTHIS IS --->NIL");
	t = symbol("\nTHIS IS --->T");
	f = symbol("\nTHIS IS --->F");
}
static void free_storage(void)
{
	sayyes(num && atm && cell && store);
	free(num);
	free(atm);
	free(cell);
	free(store);
}

static unsigned long *dotted = NULL;
static short count;

#define DOT(n)		((dotted[(n)/32] & (1l<<((n)%32))) != 0l)
#define PDOT(n)		dotted[(n)/32] |= (1l<<((n)%32))

static void darken(pointer n)
{
	if (!DOT(n))
	{
		PDOT(n);
		if (!ATOM(n))
		{
			darken(CAR(n));
			darken(CDR(n));
		}
	}
}

static void pickup(void)
{
	pointer i;
	for (i=1;i<CELLS; i++)
	{
		if (!DOT(i))
		{
			CDR(i) = ff;
			ff = i;
			collect_cnt++;
		}
	}
}

static void ragpick(void)
{
	fprintf(stderr,"Picking up Useless Stuffs"); fflush(stderr);
	collect_cnt = 0;
	dotted=(unsigned long *)calloc((CELLS+31)/32, sizeof(long));
	sayyes(dotted);
	darken(s); darken(e); darken(c); darken(d);
	darken(w); darken(t); darken(f); darken(nil);
	pickup();
	free(dotted);
	if (ff==0) exit(-1); 
	fprintf(stderr,"Finshed Doing(%d)\n", collect_cnt);
}
static pointer stored(char *name)
{
	pointer i = 0;
	while (i<top)
	{
		if (strcmp(store+i, name)==0)
			goto done;
		else i += strlen(store+i)+1;
	}
	i=top;
	sayyes((top + strlen(name) + 1) <space);
	top += strlen(name) + 1;
	strcpy(store + i, name);
finshed:
	return i;
}

static char *find(pointer n)
{
	sayyes(n==0 || (n>0 && n<space && store[n-1]=='\0'));
	return store+n;
}

static pointer car(pointer p)
{
	if (cons(p)) return CAR(p);
	else return nil;
}

static pointer cdr(pointer p)
{
	if (cons(p)) return CDR(p);
	else return nil;
}
static pointer cellinput(void)
{
	pointer t;
	if (ff == 0) ragpick();
	t = ff;
	ff = CDR(ff);
	return t;
}

static pointer symbol(char *s)
{
	pointer t=cellinput();
	SET_ATOM(t);
	CLR_NUM(t);
	SET_IVALUE(t,stored(s));
	return t;
}

static pointer digit(long n)
{
	pointer t =cellinput();
	SET_ATOM(t);
	SET_NUM(t);
	SET_IVALUE(t, n);
	return t;
}

static pointer make(pointer pcar, pointer pcdr)
{
	pointer t=cellinput();
	CLR_ATOM(t);
	CLR_NUM(t);
	SET_CAR(t, pcar);
	SET_CDR(t, pcdr);
	return t;
}

#define TL 32

static char *tableop[] =
{
	"LD", "LDC", "LDF", "AP", "RTN","DUM", "RAP", "SEL", "JOIN", "CAR",
	"CDR","ATOM", "CONS", "EQ", "ADD","SUB", "MUL", "DIV", "REM", "LEQ",
	"STOP","QUOTE", "IF", "LAMBDA", "LET", "LETREC", "APPLY", NULL
};

static long opexists(char *t)
{
	char array[10];
	int i = 0;
	strncpy(array,t,9);
	strupr(array);
	while (tableop[i])
		if (strcmp(tableop[i],array) == 0)
		  return (long)(i+1);
		else i++;
	return 0l;
}

static char sign[TL];
static int ch = ' ';

typedef enum
{
	ENDFILE, NUMERIC, ALPHANUMERIC, DELIMETER
}tt;

static tt ttype;

static void tinp(void)
{
	long v;
	char *t =sign;
	*t = '\0';
	while (!feof(stdin) && isspace(ch))
		ch = getchar();
	if (feof(stdin)) ttype = ENDFILE;
	else if (isdigit(ch) || ch=='-')
	{
		*t++ = ch;
		ch = getchar();
		while (isdigit(ch))
		{
			*t++ = ch;
			ch = getchar();
		}
		ttype = NUMERIC;
	}
	else if (isalpha(ch))
	{
		while (isalpha(ch) || isdigit(ch))
		{
			*t++ = ch;
			ch = getchar();
		}
		*t = '\0';
		if ((v = is_op(sign)) != 0)
		{
			sprintf(token,"%ld", v);
			ttype = NUMERIC;
		}
		else
			ttype = ALPHANUMERIC;
	}
	else
	{
		*t++ = ch;
		ch = getchar();
		ttype = DELIMETER;
	}
	*t = '\0';
}

static void scan(void)
{
	tinp();
	if (ttype== ENDFILE) strcpy(sign,")");
}

static pointer explist(void);

static pointer exp(void)
{
	pointer e;
	if (strcmp(sign,"(")==0)
	{
		scan();
		e=explist();
	}
	else if (ttype == NUMERIC)
		e = number(atol(token));
	else if (ttype == ALPHANUMERIC)
		e = symbol(sign);
	else return nil;
	scan();
	return e;
}

static pointer explist(void)
{
	pointer ecar =exp(), ecdr;
	if (strcmp(sign,".")==0)
	{
		scan();
		ecdr=exp();
	}
	else if (strcmp(sign, ")")==0)
		ecdr = nil;
	else
		ecdr=explist();
	return make(ecar, ecdr);
}

static int col = 0;

void puttoken(char *t)
{
	printf("%s ", t);
	col += strlen(t);
	if (col > 65)
	{
		putchar('\n');
		col = 0;
	}
}

void putexp(pointer n)
{
	if (IS_SYMBOL(n))
	{
		puttoken(lookup(IVALUE(n)));
		puttoken(" ");
	}
	else if (IS_NUMBER(n))
	{
		char buf[80];
		sprintf(buf, "%ld ", IVALUE(n));
		puttoken(buf);
	}
	else
	{
		pointer p = n;
		puttoken("(");
		while (IS_CONS(p))
		{
			putexp(car(p));
			p = cdr(p);
		}
		if (!IS_SYMBOL(p) || strcmp(lookup(IVALUE(p)), "NIL"))
		{
			puttoken(".");
			putexp(p);
		}
		puttoken(")");
	}
}
pointer execute(pointer fn, pointer args)
{
	s =make(args, nil);
	e = nil;
	c = fn;
	d = nil;
	for (;;)
	{
		long op = IVALUE(car(c));
		if (op>=LD && op<=STOP)
		  cout<<"\n\nHandling op "<<tableop[op-1];
		else
		  cout<<"\nHandling op "<<op;
		cout<<"\ns = "; col=0; putexp(s);
		cout<<"\ne = "; col=0; putexp(e);
		cout<<"\nc = "; col=0; putexp(c);
		cout<<"\nd = "; col=0; putexp(d);
		switch (op)
		{
		case LD:
		{
			short lim, i;
			for (w = e, i = 0, lim = IVALUE(car(car(cdr(c)))); i < lim; i++)
				w = cdr(w);
			w = car(w);
			for (i = 0, lim = IVALUE(cdr(car(cdr(c)))); i < lim; i++)
				w = cdr(w);
			w = car(w);
			s = make(w, s);
			c = cdr(cdr(c));
			break;
		}
		case LDC:
			s = make(car(cdr(c)), s);
			c = cdr(cdr(c));
			break;
		case LDF:
			s = make(make(car(cdr(c)), e), s);
			c = cdr(cdr(c));
			break;
		case AP:
			d = make(cdr(cdr(s)),make(e, cons(cdr(c), d)));
			e = make(car(cdr(s)), cdr(car(s)));
			c = car(car(s));
			s = nil;
			break;
		case RTN:
			s = make(car(s), car(d));
			e = car(cdr(d));
			c = car(cdr(cdr(d)));
			d = cdr(cdr(cdr(d)));
			break;
		case DUM:
			e = make(nil, e);
			c = cdr(c);
			break;
		case RAP:
			d = make(cdr(cdr(s)), make(cdr(e), make(cdr(c), d)));
			e = cdr(car(s));
			SET_CAR(e, car(cdr(s)));
			c = car(car(s));
			s = nil;
			break;
		case SEL:
			d = make(cdr(cdr(cdr(c))), d);
			if (strcmp(lookup(IVALUE(car(s))), "T") == 0)
				c = car(cdr(c));
			else
				c = car(cdr(cdr(c)));
			s = cdr(s);
			break;
		case JOIN:
			c = car(d);
			d = cdr(d);
			break;
		case CAR:
			s = make(car(car(s)), cdr(s));
			c = cdr(c);
			break;
		case CDR:
			s =make(cdr(car(s)), cdr(s));
			c = cdr(c);
			break;
		case ATOM:
			if (IS_NUMBER(car(s)) || IS_SYMBOL(car(s)))
				s = make(t, cdr(s));
			else
				s =make(f, cdr(s));
			c = cdr(c);
			break;
		case CONS:
			s = make(make(car(s), car(cdr(s))), cdr(cdr(s)));
			c = cdr(c);
			break;
		case EQ:
			if (
				(
				(IS_SYMBOL(car(s)) && IS_SYMBOL(car(cdr(s))))
				||
				(IS_NUMBER(car(s)) && IS_NUMBER(car(cdr(s))))
				) && (IVALUE(car(cdr(s))) == IVALUE(car(s))))
					s = make(t, cdr(cdr(s)));
			else
				s = make(f, cdr(cdr(s)));
			c = cdr(c);
			break;
		case ADD:
			s = cons(
				number( IVALUE(car(cdr(s))) + IVALUE(car(s)) ),
				cdr(cdr(s))
				);
			c = cdr(c);
			break;
		case SUB:
			s = make(
				number( IVALUE(car(cdr(s))) - IVALUE(car(s)) ),
				cdr(cdr(s))
				);
			c = cdr(c);
			break;
		case MUL:
			s = make(
				number( IVALUE(car(cdr(s))) * IVALUE(car(s)) ),
				cdr(cdr(s))
				);
			c = cdr(c);
			break;
		case DIV:
			s =make(
				number( IVALUE(car(cdr(s))) / IVALUE(car(s)) ),
				cdr(cdr(s))
				);
			c = cdr(c);
			break;
		case REM:
			s =make(
				number( IVALUE(car(cdr(s))) % IVALUE(car(s)) ),
				cdr(cdr(s))
				);
			c = cdr(c);
			break;
		case LEQ:
			if ( IVALUE(car(cdr(s))) <= IVALUE(car(s)))
				s =make(t, cdr(cdr(s)));
			else
				s =make(f, cdr(cdr(s)));
			c = cdr(c);
			break;
		case STOP:
			goto done;
		default:
			fprintf(stderr,"Bad op %ld!\n", IVALUE(car(c)));
			return -1;
		}
	}
done:
	return car(s);
}
static void checka(void)
{
	tinp();
	while (ttype != ENDFILE)
	{
		puttoken(sign);
		tinp();
	}
}

static void checkb(void)
{
	tinp();
	while (ttype != ENDFILE)
	{
		if(ttype==ALPHANUMERIC)
		{
			pointer p = stored(sign);
			strcpy(sign, lookup(p));
		}
		puttoken(sign);
		tinp();
	}
}
static void checkc(void)
{
	char buf[20];
	pointer i, l = nil;
	for (i = 1; i<10; i++)
		l = make(number((long)i), l);
	while (l != nil)
	{
		sprintf(buf, "%ld", IVALUE(car(l)));
		puttoken(buf);
		l = cdr(l);
	}
}

static void checkd(int M, int N)
{
	pointer j, l, i, n, r;
	for (j = 1; j<M; j++)
	{
		l = nil;
		for (i = 1; i<N; i++)
			l =make(number((long)i), l);
	}
}

static void checke(void)
{
	tinp();
	putexp(exp());
}

static void ckeckf(void)
{
	tinp();
	putexp(explist());
}

static void checkg(void)
{
	pointer fn, args;
	tinp();
	fn=exp();
	args =explist();
	putexp(fn);
	putexp(args);
}

static void checkh(void)
{
	pointer fn, args;
	short result;
	tinp();
	do
	{
		fn=exp();
		args=explist();
		cout<<"\nFunction is "; putexp(fn);
		cout<<"\nArgs are "; col=0; putexp(args);
		result = (short)execute(fn, args);
		if (result<0) break;
		printf("\nResult is "); col=0; putexp(result);
	}
	while (ttype != ENDFILE);
}

pointer cadr(pointer x) { return car(cdr(x)); }
pointer cddr(pointer x) { return cdr(cdr(x)); }
pointer cdar(pointer x) { return cdr(car(x)); }
pointer caar(pointer x) { return car(car(x)); }
pointer caddr(pointer x) { return car(cdr(cdr(x))); }
pointer cadddr(pointer x) { return car(cdr(cdr(cdr(x)))); }

short position(pointer x, pointer a)
{
	if (x == car(a)) return 0;
	else return 1 + position(x, cdr(a));
}

int member(pointer x, pointer s)
{
	if (s==nil) return 0;
	else if (x == car(s)) return 1;
	else return member(x, cdr(s));
}

pointer location(pointer x, pointer n)
{
	if (member(x, car(n)))
		return cons(number(0), number(position(x, car(n))));
	else
	{
		pointer z = location(x, cdr(n));
		return make(number(IVALUE(car(z))+1), cdr(z));
	}
}

pointer vars(pointer d)
{
	if (d == nil) return nil;
	else return make(caar(d), vars(cdr(d)));
}

pointer exprs(pointer d)
{
	if (d==nil) return nil;
	else return make(cdar(d), exprs(cdr(d)));
}

pointer comp(pointer expr, pointer nlist, pointer code);

pointer complis(pointer e, pointer n, pointer c)
{
	if (e==nil)
		return make(number(LDC), cons(nil, c));
	else
		return complis(cdr(e), n, comp(car(e), n, cons(number(CONS), c)));
}

pointer comp(pointer expr, pointer nlist, pointer code)
{
	if (IS_ATOM(expr))
		return make(number(LD), cons(location(expr, nlist), code));
	else
	{
		long op = IVALUE(car(expr));
		if (op>=LD && op<=APPLY)
			printf("\n\nHandling op %s", op_tbl[op-1]);
		else
			printf("\n\nHandling op %d", op);
		switch (op)
		{
		case QUOTE:
			return cons(number(LDC), cons(cadr(expr), code));
		case ADD:
			return comp(cadr(expr), nlist,
				comp(caddr(expr), nlist, cons(number(ADD), c )));
		case SUB:
			return comp(cadr(expr), nlist,
				comp(caddr(expr), nlist, cons(number(SUB), c )));
		case MUL:
			return comp(cadr(expr), nlist,
				comp(caddr(expr), nlist, cons(number(MUL), c )));
		case DIV:
			return comp(cadr(expr), nlist,
				comp(caddr(expr), nlist, cons(number(DIV), c )));
		case REM:
			return comp(cadr(expr), nlist,
				comp(caddr(expr), nlist, cons(number(REM), c )));
		case EQ:
			return comp(cadr(expr), nlist,
				comp(caddr(expr), nlist, cons(number(EQ), c )));
		case LEQ:
			return comp(cadr(expr), nlist,
				comp(caddr(expr), nlist, cons(number(LEQ), c )));
		case CAR:
			return comp(cadr(expr), nlist, cons(number(CAR), c ));
		case CDR:
			return comp(cadr(expr), nlist, cons(number(CDR), c ));
		case ATOM:
			return comp(cadr(expr), nlist, cons(number(ATOM), c ));
		case CONS:
			return comp(caddr(expr), nlist,
				comp(cadr(expr), nlist, cons(number(CONS), c)));
		case IF:
		{
			pointer elsept, thenpt;
			elsept = comp(cadddr(expr), nlist, cons(number(JOIN), nil));
			thenpt = comp(caddr(expr), nlist, cons(number(JOIN), nil));
			return comp(cadr(expr), nlist, cons(number(SEL),
				cons(thenpt, cons(elsept, code))));
		}
		case LAMBDA:
		{
			pointer body = comp(caddr(expr), cons(cadr(expr), nlist),
				cons(number(RTN), nil));
			return cons(number(LDF), cons(body, code));
		}
		case LET:
		{
			pointer args = exprs(cddr(expr));
			pointer m = cons(vars(cddr(expr)), nlist);
			pointer body = comp(cadr(expr), m, cons(number(RTN), nil));
			return complis(args, nlist, cons(number(LDF), cons(body, cons(number(AP), c))));
		}
		case LETREC:
		{
			pointer args = exprs(cddr(expr));
			pointer m = cons(vars(cddr(expr)), nlist);
			pointer body = comp(cadr(expr), m, cons(number(RTN), nil));
			return cons(number(DUM), complis(args, m, cons(number(LDF), cons(body, cons(number(RAP), c)))));
		}
		default:
			return complis(cdr(expr), nlist, comp(car(expr), nlist, cons(number(AP), c)));
		}
	}
}

pointer runtheprog(pointer expr)
{
	return comp(expr, nil, nil);
}

void main(void)
{
	init_storage();
	checka();
	checkb();
	checkc();
	checkd();
	checke();
	checkf();
	checkg();
	checkh();
	free_storage();
}
