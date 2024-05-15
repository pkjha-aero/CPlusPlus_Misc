// PANKAJ KUMAR JHA
// 01 MA 2011
// SECD PROG

#include<iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* TYPE DECLARATIONS */ 
//#undef true;
//#undef false;
//typedef enum {false,true} boolean;

typedef enum {alphanumeric, numeric, delimiter, endfile} type_of_token;
typedef enum {is_symbol, is_number, is_cons} celltype;
typedef enum {left, right} backtype;
typedef enum {parsing, execing} gc_flag;

/* CONSTANT DECLARATIONS */

#define MAX_LINE_LENGTH 	90		/* Linelength for reading */
#define MAX_OUT_LINE_LENGTH 80		/* smaller lines to put out */
#define MAX_STORE 			400		/* Proto Hash Table for Identifiers */
#define MAX_CONS 			1000000	/* Cons Cells Available */
#define MAX_TOKEN_LENGTH	20 		/* maximum identifier length */
#define NIL					0L
#define BLANK 				' '
#define END_OF_INPUT 		'&'

/* The opcodes for the SECD machine */
#define 	LD		1		
#define		LDC 	2
#define		LDF		3
#define		AP		4
#define		RTN		5
#define		DUM		6
#define		RAP		7
#define		SEL		8
#define		JOIN	9
#define		CAR		10
#define		CDR		11
#define		ATOM	12	
#define		CONS	13
#define		EQ		14
#define		ADD		15		/* Arithmetic ops */
#define		SUB		16
#define		MUL		17
#define		DIV		18
#define		REM		19
#define		LEQ		20
#define		STOP	21		/* End of computation */
#define		SOR		31		/* Non-deterministic OR */
#define 	NON		32		/* branch termination no good */
#define		LDE		33		/* Lazy evaluation ops */
#define		UPD		34
#define		AP0		35
#define 	RPLA	41
#define		RPLD	42
#define     PRNT    51

/* ===================== GLOBAL VARIABLE DECLARATIONS ====================== */
		
long	index = 0;		/* used as an index whenever needed */

int		out_buffer = 0,
		in_buffer = 0,
		in_buff_pointer = 0,
		linelength = 0,
		storefree = 0;  
		
type_of_token	tokentype;

FILE	*outfile,
		*infile;
		
bool    in_disk 		= false,
		out_disk 		= false,
		in_echo 		= false,		
		out_echo		= true,
		fun_echo 		= false,
		arg_echo 		= false,
		save_function 	= false,
		go_on 			= false,
		keep_going		= true,
		dumpsomething 	= false,
		dumpstack		= false,
		dumpenvironment = false,
		dumpcontrol 	= false,
		dumpdump 		= false,
		trace_ops 		= false,
		put_back_char 	= false,
		debug_mode 		= false;

/* Trace Information */		
bool    	TraceLD 	= false,		
		 	TraceLDC 	= false,
		 	TraceLDF 	= false,
			TraceAP		= false,
 			TraceRTN 	= false,
 			TraceDUM 	= false,
 			TraceRAP 	= false,
 			TraceSEL 	= false,
 			TraceJOIN	= false,
 			TraceCAR	= false,
			TraceCDR	= false,
			TraceATOM	= false,	
			TraceCONS	= false,
			TraceEQ		= false,
			TraceADD	= false,
			TraceSUB	= false,
			TraceMUL	= false,
			TraceDIV	= false,
			TraceREM	= false,
			TraceLEQ	= false,
			TraceSTOP	= false,
			TraceSOR	= false,
			TraceNON	= false,
			TraceLDE	= false,
			TraceUPD	= false,
			TraceAP0	= false,
			TraceRPLA	= false,
			TraceRPLD	= false,
			TracePRNT	= false;
			
			
/* memory stuff */
bool 		*marked; 	/* has cons cell been marked?? */
celltype 	*is;     	/* what type is this cell?? */
backtype	*back;   	/* for bounded space garbage collection */
long		*car,		/* CAR & CDR, boys and girls... */
			*cdr;

/* pointers into CONS space */			
long 		consfree 	= MAX_CONS - 1,
			s 			= NIL, 	/* STACK */
			e 			= NIL, 	/* ENVIRONMENT */
			c 			= NIL, 	/* CONTROL */
			d 			= NIL,	/* DUMP */
			r 			= NIL, 	/* RESUMPTION */
			t 			= NIL, 	/* TRUE */
			f			= NIL, 	/* FALSE */
			omega		= NIL,	/* UNDEFINED */
			w 			= NIL,  /* WORKING */
			fn 			= NIL,	/* Pointer to the initial code */
			args 		= NIL,	/* Pointer to the initial data */
			result 		= NIL,	/* hopefully, anyway.. */
			tempnum 	= NIL,	/* global temps - for speed */
			temp1 		= NIL,
			temp2		= NIL;	
			
char		stringstore[MAX_STORE][MAX_TOKEN_LENGTH], /* HASH TABLE ?? */
			token[MAX_TOKEN_LENGTH],
			in_line[MAX_LINE_LENGTH];
			
gc_flag		which_mode = execing;	/* are we parsing or executing? */

/* =================== END GLOBAL VARIABLE DECLARATIONS ==================== */				

/* ========================= FUNCTION PROTOTYPES =========================== */
void allocate_arrays(void);
void cleanup(int ercode);
void initialize(void);
bool yes_no(void);
void rotate(long *p1, long *p2, long *p3);
void markit(long p);
void collect(void);
void collect_garbage(void);
long newnode(celltype kind);
long cons (long e1, long e2);
long copy_list(long exp);
void install(long cp, char *word);
void dumpregisters(void);
void header_dump_and_opcode(int opcode);
void check_for_register_dumps(void);
void collect_opcodes_to_trace(void);
void kill_opcode_trace(void);

/* The SECD Machine Instructions */
void m_ld(void);
void m_ldc(void);
void m_ldf(void);
void m_ap(void);
void m_rtn(void);
void m_dum(void);
void m_rap(void);
void m_sel(void);
void m_join(void);
void m_car(void);
void m_cdr(void);
void m_atom(void);
void m_cons(void);
void m_eq(void);
void m_add(void);
void m_sub(void);
void m_mul(void);
void m_div(void);
void m_rem(void);
void m_leq(void);
void m_stop(void);
void m_sor(void);
void m_non(void);
void m_lde(void);
void m_upd(void);
void m_ap0(void);
void m_rpla(void);
void m_rpld(void);
void m_prnt(void);
/* -- */
long debug_exec(long fn, long args);
long exec(long fn, long args);
void puttoken(char token[MAX_TOKEN_LENGTH]);
void putexp(long exp);
void putoutput(long result);
void put_final_exp(long exp);
void put_final_output(long result);
static int stc_ld(register char *out, register unsigned long in, 
                  register int outlen, int signflag);
int  stci_ld(char *out, unsigned long in, int outlen);
char get_char_from_inbuffer(void);
void gettoken(void);
long getexplist(void);
long getexp(void);
long getinput(bool compin);
void getprogfile(void);
void setoutfile(void);
void getargfile(void);

/* =================  INITIALIZATION AND EXIT MODULE  ====================== */		

/* ALLOCATE_ARRAYS : large structures allocation and program exit */		
void allocate_arrays(void)
{	marked 	= (bool *)calloc(MAX_CONS + 1, sizeof(bool));
	is 		= (celltype *)calloc(MAX_CONS + 1, sizeof(celltype));
	back 	= (backtype *)calloc(MAX_CONS + 1, sizeof(long));
	car		= (long *)calloc(MAX_CONS + 1, sizeof(long));
	cdr		= (long *)calloc(MAX_CONS + 1, sizeof(long));
}

/* CLEANUP : this sends an error message and exits as neatly as possible */	
void cleanup(int ercode)
{	printf("Error %d\n", ercode);
	exit(1); 		/* this closes all open files--- */
}

/* INITIALIZE : this function does all up-front initializations of globals 
	and SECD machine registers and reserved symbols. */
void initialize(void)
{	int 	ch = BLANK;
	int		i, j;
	srand(37);
	in_line[0] = '\0';
	printf("Initializing the stringstore \n");
	for (j = 0; j < MAX_STORE; j++)
		for (i = 0; i < MAX_TOKEN_LENGTH; i++)
			stringstore[j][i] = '\0'; 
		/*initialize the "hash table" */
	consfree = MAX_CONS - 1;
	printf("Initializing cons space: %ld\n", consfree);
	for (index = consfree; index > 0; index--)
		car[index] = index - 1;	
	printf("Installing NIL, T, F & OMEGA\n");	
	cdr[NIL] = NIL;
	is[NIL] = is_symbol;
	install(NIL, "NIL");		/* so we can print it out */	
	t = newnode(is_symbol);
	install(t, "T");
	f = newnode(is_symbol);
	install(f, "F");
	omega = newnode(is_symbol);
	install(omega,"OMEGA");
	fn = NIL;
	args = NIL;
	check_for_register_dumps();
}
/* ======================  USER INTERFACE GENERICS  ======================== */
bool yes_no(void)
{	int 	ch;
	do {ch = getchar();}
		while (ch != 'Y' && ch != 'y' && ch != 'N' &&  ch != 'n');
	putchar('\n');
	if (ch == 'Y' || ch == 'y') return(true);
	else return(false);
}
/* ======================  GARBAGE COLLECTION MODULE  ====================== */

/* ROTATE : this function rotates the pointers - see A. H. U. for algorithm */
void rotate(long *p1, long *p2, long *p3)
{	temp1 = *p1;
	*p1 = *p2;
	*p2 = *p3;
	*p3 = temp1;
}
/* MARKIT : this is the marking routine. It works in bounded space, since
	one usually garbage collects when one is out of space and using a lot
	of stack for recursion is not a swift idea  */
void markit(long p)	
{	long	current,
			previous;
	int 	label;
	current = p;
	previous = NIL;
	back[NIL] = right;
	cdr[NIL] = NIL;
	marked[NIL] = true;
	label = 10;	
	/* the marking algorithm proper (Deutsch - Schorr - Waite) */
	while (label != 30)
	{	if (label == 10)
		{	if (marked[current] == true || 
				is[current] != is_cons ||
				(car[current] == NIL && cdr[current] == NIL))
			{	marked[current] = true;
				label = 20;
			}
			else
			{	marked[current] = true;
				if (car[current] == NIL)
				{	back[current] = right;
					rotate(&previous, &current, &cdr[current]);
				}
				else
				{	back[current] = left;
					rotate(&previous, &current, &car[current]);
				}
				label = 10;
			}
		}
		else if (label == 20)
		{	if (previous == current)
				label = 30;
			else if (back[previous] == left && cdr[previous] != NIL)
			{	back[previous] = right;
				rotate(&car[previous], &current, &cdr[previous]);
				label = 10;
			}
			else if (back[previous] == right)
				rotate(&previous, &cdr[previous], &current);
			else rotate(&previous, &car[previous], &current);
		}
	}
}				       
/* COLLECT : this function collects	the garbage and puts it back on the free
	list */
void collect(void)
{	long 	nodesfree;
	nodesfree = 0;
	for (index = NIL; index < MAX_CONS; index++)
		if (marked[index] != true)
		{	car[index] = consfree;
			consfree = index;
			++nodesfree;
		}
	printf("Collected: %ld\n", nodesfree);
}

/* COLLECT_GARBAGE : This function starts the GC process. It first 
   initializes the MARKED array to FALSE, and then starts marking from the
   four available entry points into memory. 
   These are the four registers: T, F, FN and ARGS */
void collect_garbage(void)	
{ 	long savecar;
	/*	putoutput(s);
	putoutput(e);
	putoutput(c);
	putoutput(d);	*/
	savecar = car[NIL];
	car[NIL] = NIL;
	printf("GC: ");
	for ( index = NIL; index < MAX_CONS; index++)
		marked[index] = false;
	marked[NIL] = true;
	markit(t);
	markit(f);
	markit(omega);
	if (which_mode == parsing)
	{	markit(fn);			/* the other stacks are not being used */
		markit(args);
	}
	else 
	{	if (save_function == true)	
			markit(fn); 	/* we intend to run it again */
		markit(w);			/* the execution time registers */
		markit(s);
		markit(e);
		markit(c);
		markit(d);
		markit(r);
	}
	collect();
	if ( consfree == NIL)	/* no space to be found */
		cleanup(4);
	car[NIL] = savecar;
	cdr[NIL] = NIL;
	/*	putoutput(s);
	putoutput(e);
	putoutput(c);
	putoutput(d);	*/
}
/* =========================== MEMORY ALLOCATION =========================== */

long 	newnode(celltype kind)
{	/* if (which_mode == execing) 	printf("In newnode\n"); */
	if (consfree == NIL)
		collect_garbage();
	temp1 = consfree;
	consfree = car[consfree];
	car[temp1] = NIL;
	cdr[temp1] = NIL;
	is[temp1] = kind;
	return(temp1);
}		
/* CONS : this makes a CONS cell with given CAR and CDR */
long 	cons (long e1, long e2)
{	temp2 = newnode(is_cons);
	car[temp2] = e1;
	cdr[temp2] = e2;
	return(temp2);
}
/*COPY_LIST : recall that NIL is a symbol in this system */
long copy_list(long exp)
{	if (is[exp] == is_symbol || is[exp] == is_number)
		return(exp);
	else
		return(cons(copy_list(car[exp]),copy_list(cdr[exp])));
}
/* INSTALL :  this function installs an alphanumeric atom into the STRINGSTORE.
	This will probably have to be augmented to a hash table later. */
void install(long cp, char *word)
{	int wordindex = 0;
	while (strcmp(stringstore[wordindex],word) != 0 && wordindex < storefree)
		wordindex++;
	if (wordindex < storefree)
		car[cp] = wordindex;
	else if (storefree < MAX_STORE)
	{	car[cp] = storefree;
		strcpy(stringstore[storefree], word);
		storefree++;
	}
	else cleanup(3);
}
/* ===========================  DEBUGGING AIDS  ============================ */
/* DUMPREGISTERS - This is a debugging procedure - it allows the printing out
	of selected registers as execution progresses */
void dumpregisters(void)
{	int	ch;
	if (dumpstack == true)  		putoutput(s);
	if (dumpenvironment == true)	putoutput(e);
	if (dumpcontrol == true)		putoutput(c);
	if (dumpdump == true)			putoutput(d);
	if (out_disk == true) 			putc('\n', outfile);
	if (out_echo == true)
	{	while ((ch = getchar()) != '\n')
		{	if (ch == '$') cleanup(6);
		}
	}
}
/* END DUMPREGISTERS */

/* HEADER_DUMP_AND_OPCODE */
void header_dump_and_opcode(int opcode)
{	printf("===================\n");
	dumpregisters();
	printf("Opcode: %d\n", opcode);
}
/* END HEADRE_DUMP_AND_OPCODE */

/* CHECK_FOR_REGISTER_DUMPS */
void check_for_register_dumps()
{	dumpsomething = false;
	fputs("Debugging Environment: ", stdout);
	if (yes_no() == true)
	{	puts("REGISTERS to be displayed:");
		fputs("STACK      : ", stdout);
		dumpstack = yes_no();
		fputs("ENVIRONMENT: ", stdout);
		dumpenvironment = yes_no();
		fputs("CONTROL    : ", stdout);
		dumpcontrol = yes_no();
		fputs("DUMP       : ", stdout);
		dumpdump = yes_no();
		if (dumpstack == true || dumpenvironment == true || 
	   		dumpcontrol == true || dumpdump == true)
		{	dumpsomething = true;
			debug_mode = true;
		}
	}
	else
	{	dumpstack = false;
		dumpenvironment = false;
		dumpcontrol = false;
		dumpdump = false;
		dumpsomething = false;
		debug_mode = false;
	}
}
/* END CHECK_FOR_REGISTER_DUMPS */

/* COLLECT_OPCODES_TO_TRACE */
void collect_opcodes_to_trace(void)
{	trace_ops = false; /* not all of them */
	printf("Trace LD  : (y/n) - ");
	TraceLD = yes_no();
	printf("Trace LDC : (y/n) - ");		
	TraceLDC 	= yes_no();
	printf("Trace LDF : (y/n) - ");
	TraceLDF 	= yes_no();
	printf("Trace AP  : (y/n) - ");
	TraceAP		= yes_no();
	printf("Trace RTN : (y/n) - ");
 	TraceRTN 	= yes_no();
 	printf("Trace DUM : (y/n) - ");
 	TraceDUM 	= yes_no();
 	printf("Trace RAP : (y/n) - ");
 	TraceRAP 	= yes_no();
 	printf("Trace SEL : (y/n) - ");
 	TraceSEL 	= yes_no();
 	printf("Trace JOIN: (y/n) - ");
 	TraceJOIN	= yes_no();
 	printf("Trace CAR : (y/n) - ");
 	TraceCAR	= yes_no();
 	printf("Trace CDR : (y/n) - ");
	TraceCDR	= yes_no();
	printf("Trace ATOM: (y/n) - ");
	TraceATOM	= yes_no();
	printf("Trace CONS: (y/n) - ");	
	TraceCONS	= yes_no();
	printf("Trace EQ  : (y/n) - ");
	TraceEQ		= yes_no();
	printf("Trace ADD : (y/n) - ");
	TraceADD	= yes_no();
	printf("Trace SUB : (y/n) - ");
	TraceSUB	= yes_no();
	printf("Trace MUL : (y/n) - ");
	TraceMUL	= yes_no();
	printf("Trace DIV : (y/n) - ");
	TraceDIV	= yes_no();
	printf("Trace REM : (y/n) - ");
	TraceREM	= yes_no();
	printf("Trace LEQ : (y/n) - ");
	TraceLEQ	= yes_no();
	printf("Trace STOP: (y/n) - ");
	TraceSTOP	= yes_no();
	printf("Trace SOR : (y/n) - ");
	TraceSOR	= yes_no();
	printf("Trace NON : (y/n) - ");
	TraceNON	= yes_no();
	printf("Trace LDE : (y/n) - ");
	TraceLDE	= yes_no();
	printf("Trace UPD : (y/n) - ");
	TraceUPD	= yes_no();
	printf("Trace AP0 : (y/n) - ");
	TraceAP0	= yes_no();
	printf("Trace RPLA: (y/n) - ");
	TraceRPLA	= yes_no();
	printf("Trace RPLD: (y/n) - ");
	TraceRPLD	= yes_no();
	printf("Trace PRNT: (y/n) - ");
	TracePRNT	= yes_no();
	debug_mode 	= true;
}
/* END COLLECT_OPCODES_TO_TRACE */

/* KILL_OPCODE_TRACE : sets all opcode trace flags to false */
void kill_opcode_trace(void)
{	TraceLD 	= false;		
	TraceLDC 	= false;
	TraceLDF 	= false;
	TraceAP		= false;
 	TraceRTN 	= false;
 	TraceDUM 	= false;
 	TraceRAP 	= false;
 	TraceSEL 	= false;
 	TraceJOIN	= false;
 	TraceCAR	= false;
	TraceCDR	= false;
	TraceATOM	= false;	
	TraceCONS	= false;
	TraceEQ		= false;
	TraceADD	= false;
	TraceSUB	= false;
	TraceMUL	= false;
	TraceDIV	= false;
	TraceREM	= false;
	TraceLEQ	= false;
	TraceSTOP	= false;
	TraceSOR	= false;
	TraceNON	= false;
	TraceLDE	= false;
	TraceUPD	= false;
	TraceAP0	= false,
	TraceRPLA 	= false,
	TraceRPLD	= false;
	TracePRNT	= false;
	debug_mode  = false;
}
/* END KILL_OPCODE_TRACE */

/* =========================  END DEBUGGING AIDS  ========================== */

/* ======================= SECD MACHINE INTERPRETER ======================== */

/* ==> THE OPCODES : we give the stack operations for each opcode - this 
	is what defines the SECD machine */

/* M_LD - OPCODE : LD = 1 
 	S			E	(LD (i.j) . C)		D	
-->	(w . S)	 	E	C					D  
 	where w has been extracted from the ENVIRONMENT stack 	*/
void m_ld(void)
{	w = e;
	for (index = 1; index <= car[car[car[cdr[c]]]]; index++) 
		w = cdr[w];
	w = car[w];
	for (index = 1; index <= car[cdr[car[cdr[c]]]]; index++)
		w = cdr[w];
	w = car[w];
	s = cons(w,s);
	c = cdr[cdr[c]];	/* skip operator and operand */
}
/* END M_LD */

/* M_LDC - OPCODE : LDC = 2 
	S 			E 	(LDC x . C)		D	
-->	(x . S)		E	C				D 	
	this implementation copies constant lists .. */
void m_ldc(void)
{	/* if (is[car[cdr[c]]] == is_cons)	
		s = cons(copy_list(car[cdr[c]]),s); 
	else */
		s = cons(car[cdr[c]], s);
	c = cdr[cdr[c]];
}
/* END M_LDC */

/* M_LDF - OPCODE : LDF = 3 
	This loads a closure - code + environment - on the stack, and continues.
	The next opcode, AP, sets things up for function execution.
	S				E	(LDF C' . C)	D	
-->	((C' . E) . S)	E	C				D	*/
void m_ldf(void)
{	s = cons(cons(car[cdr[c]],e),s);
	c = cdr[cdr[c]];
}
/* END M_LDF */

/* M_AP - OPCODE : AP = 4
	This is the FUNCTION APPLICATION opcode. Notice how the system already
	expects that the function CODE and LOCAL ENVIRONMENT be already at the top
	of the stack. It moves the function code to the CONTROL register, ZEROS 
	the STACK REGISTER, sets up the ENVIRONMENT REGISTER, and saves all further
	computation instructions on the DUMP REGISTER. 
	((C' . E') v . S)	E			(AP . C)	D	
-->	NIL					(v . E')	C'			(S E C . D)		*/
void m_ap(void)
{	d = cons(cdr[cdr[s]],cons(e,cons(cdr[c],d)));
	e = cons(car[cdr[s]],cdr[car[s]]);
	c = car[car[s]];
	s = NIL;
}
/* END M_AP */

/* M_RTN - OPCODE : RTN = 5
	This function assumes the top of the STACK contains the result of some
	computation - a function call -, and that we are now returning from it.
	Notice the restoration of all the saved registers.
	(x)			E'	(RTN)	(S E C . D)		
-->	(x . S)		E	C		D	*/
void m_rtn(void)
{	s = cons(car[s],car[d]);
	e = car[cdr[d]];
	c = car[cdr[cdr[d]]];
	d = cdr[cdr[cdr[d]]];
}
/* END M_RTN */

/* M_DUM - OPCODE : DUM = 6	
	This instruction creates a dummy environment with OMEGA as its first sublist.
	Any attempts to access values in this sublists will be undefined, until 
	OMEGA has been replaced.
	S	E				(DUM . C)	D	
-->	S	(omega . E)		C			D	*/
void m_dum(void)
{	e = cons(omega, e);
	c = cdr[c];
}
/* END M_DUM */

/* M_RAP - OPCODE : RAP = 7
	This insruction is similar to AP, using RPLACA on a DUMMY environment
	rather than consing.
	((C'. E') v . S) 	(omega . E) 	(RAP . C)	D	
-->	NIL					rplaca(E', v)	C'			(S E C . D) */
void m_rap(void)
{	d = cons(cdr[cdr[s]],cons(cdr[e],cons(cdr[c],d)));
	e = cdr[car[s]];
	car[e] = car[cdr[s]]; 	/* here is RPLACA */
	c = car[car[s]];
	s = NIL;
}
/* END M_RAP */

/* M_SEL - OPCODE : SEL = 8
	This is the branch instruction - it depends on the truth status of the
	top of the stack.
	(x . S)		E	(SEL Ctrue Cfalse . C) 	D
-->	S 			E 	Cx 						(C . D)		
	where x is either true or false	*/ 
void m_sel(void)
{	d = cons(cdr[cdr[cdr[c]]], d);
	if (car[car[s]] == car[t])
		c = car[cdr[c]];
	else
		c = car[cdr[cdr[c]]];
	s = cdr[s];
}
/* END M_SEL */

/* M_JOIN - OPCODE : JOIN = 9
	This is the RETURN FROM BRANCH instruction.
	S	E	(JOIN)	(C . D)
-->	S	E	C		D	*/
void m_join(void)
{	c = car[d];
	d = cdr[d];
}
/* END M_JOIN */

/* M_CAR - OPCODE : CAR = 10
	This is the usual CAR instruction : takes the first element of the top
	list of the stack and puts it back on top of the stack.
	((a . b) . S)	E	(CAR . C)	D
-->	(a . S) 		E 	C			D	*/
void m_car(void)
{	s = cons (car[car[s]], cdr[s]);
	c = cdr[c];
}	
/* END M_CAR */

/* M_CDR - OPCODE : CDR = 11
	This is the usual CDR instruction : takes all but the first element of 
	the top list of the stack and puts it back on top of the stack.
	((a . b) . S)	E	(CDR . C)	D
-->	(b . S) 		E 	C			D	*/
void m_cdr(void)
{	s = cons(cdr[car[s]], cdr[s]);
	c = cdr[c];
}
/* END M_CDR */

/* M_ATOM - OPCODE : ATOM = 12
	Checks is the top of the stack is an atom - leaves t or f on top of stack.
	(a . S) 	E 	(ATOM . C) 	D
-->	(ax . S)	E	C			D	*/
void m_atom(void)
{	if (is[car[s]] == is_number || is[car[s]] == is_symbol)
		s = cons(t, cdr[s]);
	else
		s = cons(f, cdr[s]);
	c = cdr[c];
}

/* M_CONS - OPCODE : CONS = 13
	Creates a cons cell of the two topmost elements of the stack and puts it
	on the stack.
	(a b . S)		E	(CONS . C) 		D
-->	((a . b) .S) 	E	C				D	*/
void m_cons(void)
{	if (TraceCONS == true)
	{	printf("Print CAR & CADR?");
		if (yes_no() == true)
		{	printf("CAR: ");
			putoutput(car[s]);
			printf("CADR: ");
			putoutput(car[cdr[s]]);
		}
	}
	s = cons(cons(car[s], car[cdr[s]]), cdr[cdr[s]]);
	c = cdr[c];
}	
/* END M_CONS */

/* M_EQ - OPCODE : EQ = 14
	a and b could be symbols, numbers or conses - two pointers to the same 
	list will return T.
	(a b . S) 	E	(EQ . C)	D
-->	(? . S)		E	C			D		where ? is T or F	*/
void m_eq(void)
{	if ((is[car[s]] == is_symbol &&
		 is[car[cdr[s]]] == is_symbol &&
		 car[car[s]] == car[car[cdr[s]]]) || 	/* pointing to same string? */
		(is[car[s]] == is_number &&
		 is[car[cdr[s]]] == is_number &&
		 car[car[s]] == car[car[cdr[s]]]))		/* same number? */
		s = cons(t, cdr[cdr[s]]);
	else
		s = cons(f, cdr[cdr[s]]);
	c = cdr[c];
}
/* END M_EQ */ 

/* M_ADD - OPCODE : ADD = 15
	(a b . S) 		E	(ADD . C) 	D
-->	((b+a) . S)		E	C			D	*/
void m_add(void)
{	tempnum = newnode(is_number);
	car[tempnum] = car[car[cdr[s]]] + car[car[s]];
	s = cons(tempnum, cdr[cdr[s]]);
	c = cdr[c];
}
/* END M_ADD */

/* M_SUB - OPCODE : SUB = 16
	(a b . S) 		E	(SUB . C) 	D
-->	((b-a) . S)		E	C			D	*/
void m_sub(void)
{	tempnum = newnode(is_number);
	car[tempnum] = car[car[cdr[s]]] - car[car[s]];
	s = cons(tempnum, cdr[cdr[s]]);
	c = cdr[c];
}
/* END M_SUB */

/* M_MUL - OPCODE : MUL = 17
	(a b . S) 		E	(MUL . C) 	D
-->	((b*a) . S)		E	C			D	*/
void m_mul(void)
{	tempnum = newnode(is_number);
	car[tempnum] = car[car[cdr[s]]] * car[car[s]];
	s = cons(tempnum, cdr[cdr[s]]);
	c = cdr[c];
}
/* END M_MUL */

/* M_DIV - OPCODE : DIV = 18
	(a b . S) 		E	(DIV . C) 	D
-->	((b/a) . S)		E	C			D	*/
void m_div(void)
{	tempnum = newnode(is_number);
	car[tempnum] = car[car[cdr[s]]] / car[car[s]];
	s = cons(tempnum, cdr[cdr[s]]);
	c = cdr[c];
}
/* END M_DIV */

/* M_REM - OPCODE : REM = 19
	(a b . S) 		E	(REM . C) 	D
-->	((bMODa) . S)	E	C			D	*/
void m_rem(void)
{	long 	num1, 
			num2;
	tempnum = newnode(is_number);
	num1 = car[car[cdr[s]]];
	num2 = car[car[s]];
	car[tempnum] = num1 - num2 * (num1 / num2);
	s = cons(tempnum, cdr[cdr[s]]);
	c = cdr[c];
}
/* END M_REM */	

/* M_LEQ - OPCODE : LEQ = 20
	(a b . S)	E	(LEQ . C)	D
-->	(x . S) 	E	C			D	
	where x = t if b <= a and f otherwise */
void m_leq(void)
{	if (car[car[cdr[s]]] <= car[car[s]])
		s = cons(t, cdr[cdr[s]]);
	else
		s = cons(f, cdr[cdr[s]]);
	c = cdr[c];
}
/* END M_LEQ */

/* M_STOP - OPCODE : STOP = 21
	This has as side-effect the stopping of execution. It leaves the SECD
	machine intact.
	S 	E 	(STOP) 	D
--> S	E	(STOP)	D	*/
void m_stop(void)
{	go_on = false;
}
/* END M_STOP */

/* Extended stuff -  OR plus FORCE and DELAY */	

/* M_SOR - OPCODE : SOR = 31
	S 	E	(SOR c1 c2 . C)		D			R
-->	S	E	c1					(C . D)		(S E c2 (C . D) . R) 
			OR
	S 	E	(SOR c1 c2 . C)		D			R
-->	S	E	c2					(C . D)		(S E c1 (C . D) . R) 
			*/
void m_sor(void)
{	d = cons(cdr[cdr[cdr[c]]],d);
	if (rand() < 16250) /* about half way - 16 bit integers... */
	{	r = cons(s,cons(e,cons(cons(car[cdr[cdr[c]]],d),r)));
		c = car[cdr[c]];
		}
	else
	{	r = cons(s,cons(e,cons(cons(car[cdr[c]],d),r)));
		c = car[cdr[cdr[c]]];
	}
}
/* END M_SOR */

/* M_NON - OPCODE : NON = 32
	This opcode checks that the RESUMPTION register holds something - if it 
	does, the computation backtracks to the saved state, otherwise it stops.
	S	E	(NON)	D	(S' E' C' D' . R)
--> S'	E'	C'		D'	R
	--- OR ---
	S 	E 	(NON)	D	NIL
-->	NIL	E	(NON)	D	NIL 	with go_on = false. */
void m_non(void)
{	if (r == NIL)
	{	s = NIL;
		go_on = false;
	}
	else
	{	s = car[r];
		e = car[cdr[r]];
		c = car[cdr[cdr[r]]];
		d = car[cdr[cdr[cdr[r]]]];
		r = cdr[cdr[cdr[cdr[r]]]];
	}
}
/* END M_NON */

/* M_LDE - OPCODE : LDE = 33 
	S					E	(LDE C . C')		D
-->	([F(C . E)] . S)	E	C'					D	
	where [F(C . E)] is a "recipe" for computation 	*/
void m_lde(void)
{	s = cons(cons(f, cons(car[cdr[c]], e)), s);
	c = cdr[cdr[c]];
}
/* END M_LDE */

/* M_UPD - OPCODE : UPD = 34 
	(x)			E	(UPD)	(([F(C . E)] . S) E' C' . D)
-->	(x . S)		E'	C'		D	
	A better implementation will also have [F(C . E)] --> [T x]. We accept
	the inefficiency. */
void m_upd(void)
{	car[car[d]] = cons(t, car[s]);  /* new code saving value */
	s = cons(car[s], cdr[car[d]]);
	e = car[cdr[d]];
	c = car[cdr[cdr[d]]];
	d = cdr[cdr[cdr[d]]];
}
/* END M_UPD */		

/* M_AP0 - OPCODE : AP0 = 35 
	([F(C . E)] . S)	E'	(AP0 . C')	D
-->	NIL					E	C			(([F(C . E)] . S) E' C' . D) 
	A different transition would be used for an EVALUATED recipe - [T x]  */
void m_ap0(void)
{	if (car[car[s]] == t)		/* found an evaluated recipe */
	{	s = cons(cdr[car[s]], cdr[s]);
		c = cdr[c];
	}
	else
	{	d = cons(s, cons(e, cons(cdr[c],d)));
		e = cdr[cdr[car[s]]];
		c = car[cdr[car[s]]];
		s = NIL;
	}
}
/* END M_AP0 */

/* M_RPLA - OPCODE : RPLA = 41
   	(x (y . z) . S) 	E		(RPLA . C)		D
-->	((x . z) . S		E		C				D
	This is the RPLACA command - it is NOT purely functional, but appears
	necessary to be able to implement an interpreter in LISPKIT itself */
void m_rpla(void)
{	car[car[cdr[s]]] = car[s];
	s = cdr[s];
	c = cdr[c];
}
/* END M_RPLA */

/* M_RPLD - OPCODE : RPLD = 42
	(x (y . z) . S)		E		(RPLD . C) 		D
-->	((y . x) . S) 		E		C				D
	This is the RPLACD commmand - added for symmetry  */
void m_rpld(void)
{	cdr[car[cdr[s]]] = car[s];
	s = cdr[s];
	c = cdr[c];
}
/* END M_RPLD */

/* M_PRNT - OPCODE : PRNT = 51
   	(x . S)		E		(PRNT . C)		D
-->	S			E		C				D
    with the side-effect of sending x to the console */
void m_prnt(void)
{	fputs("PRINT INST  : ", stdout);
	put_final_output(car[s]);
	/* s = cdr[s]; no effect on the stack or anything else */
	c = cdr[c];
}
/* END M_PRNT */

/* ==> THE MACHINE INTREPRETER */
/* DEBUG_EXEC : this function takes an expression, FN, and an expression list, ARGS,
	and sets up and runs the SECD machine until termination. The result of
	the computation is left at the top of the stack - This is used when 
	debugging output is expected */
long 	debug_exec(long fn, long args)
{	int		opcode;
	/* SECD initialization section */
	go_on = true;
	which_mode = execing;
	s = newnode(is_cons);
	car[s] = args;
	e = NIL;
	c = fn;
	d = NIL;
	/* end of SECD initialization section */
	if (trace_ops == true && dumpsomething == true) dumpregisters();
	while (go_on == true)
	{	/* if (kbhit() == 1)	-- panic exit from infinite loop --
			if (getchar() == '&') cleanup(6); */
		opcode = car[car[c]]; 	/* we MUST first coerce to INTEGER */
		if (trace_ops == true) 	/* Tracing ALL opcodes */
		{	printf("opcode: %d \n", opcode);
			if (out_disk == true) 
				fprintf(outfile,"Opcode: %d\n", opcode);
		}
		switch	(opcode)
		{	case	LD  :	if (TraceLD == true)
							{	header_dump_and_opcode(LD);
								m_ld();
								dumpregisters();
							}
							else m_ld(); 	break;
			case	LDC :	if (TraceLDC == true)
							{	header_dump_and_opcode(LDC);
								m_ldc();
								dumpregisters();
							}
							else m_ldc(); 	break;
			case	LDF :	if (TraceLDF == true)
							{	header_dump_and_opcode(LDF);
								m_ldf();
								dumpregisters();
							}
							else m_ldf();	break;
			case	AP  :	if (TraceAP == true)
							{	header_dump_and_opcode(AP);
								m_ap();
								dumpregisters();
							}
							else m_ap();		break;
			case	RTN :	if (TraceRTN == true)
							{	header_dump_and_opcode(RTN);
								m_rtn();
								dumpregisters();
							}
							else m_rtn();	break;
			case	DUM :	if (TraceDUM == true)
							{	header_dump_and_opcode(DUM);
								m_dum();
								dumpregisters();
							}
							else m_dum();	break;
			case	RAP :	if (TraceRAP == true)
							{	header_dump_and_opcode(RAP);
								m_rap();
								dumpregisters();
							}
							else m_rap();	break;
			case 	SEL :	if (TraceSEL == true)
							{	header_dump_and_opcode(SEL);
								m_sel();
								dumpregisters();
							}
							else m_sel();	break;
			case	JOIN:	if (TraceJOIN == true)
							{	header_dump_and_opcode(JOIN);
								m_join();
								dumpregisters();
							}
							else m_join();	break;
			case	CAR :	if (TraceCAR == true)
							{	header_dump_and_opcode(CAR);
								m_car();
								dumpregisters();
							}
							else m_car();	break;
			case	CDR :	if (TraceCDR == true)
							{	header_dump_and_opcode(CDR);
								m_cdr();
								dumpregisters();
							}
							else m_cdr();	break;
			case 	ATOM:	if (TraceATOM == true)
							{	header_dump_and_opcode(ATOM);
								m_atom();
								dumpregisters();
							}
							else m_atom();	break;
			case	CONS:	if (TraceCONS == true)
							{	header_dump_and_opcode(CONS);
								m_cons();
								dumpregisters();
							}
							else m_cons();	break;
			case	EQ  :	if (TraceEQ == true)
							{	header_dump_and_opcode(EQ);
								m_eq();
								dumpregisters();
							}
							else m_eq();		break;
			case	ADD :	if (TraceADD == true)
							{	header_dump_and_opcode(ADD);
								m_add();
								dumpregisters();
							}
							else m_add();	break;
			case	SUB :	if (TraceSUB == true)
							{	header_dump_and_opcode(SUB);
								m_sub();
								dumpregisters();
							}
							else m_sub();	break;
			case	MUL :	if (TraceMUL == true)
							{	header_dump_and_opcode(MUL);
								m_mul();
								dumpregisters();
							}
							else m_mul();	break;
			case	DIV :	if (TraceDIV == true)
							{	header_dump_and_opcode(DIV);
								m_div();
								dumpregisters();
							}
							else m_div();	break;
			case	REM :	if (TraceREM == true)
							{	header_dump_and_opcode(REM);
								m_rem();
								dumpregisters();
							}
							else m_rem();	break;
			case	LEQ :	if (TraceLEQ == true)
							{	header_dump_and_opcode(LEQ);
								m_leq();
								dumpregisters();
							}
							else m_leq();	break;
			case	STOP:	if (TraceSTOP == true)
							{	header_dump_and_opcode(STOP);
								m_stop();
								dumpregisters();
							}
							else m_stop();	break;
			case	SOR	:	if (TraceSOR == true)
							{	header_dump_and_opcode(SOR);
								m_sor();
								dumpregisters();
							}
							else m_sor();	break;
			case	NON	:	if (TraceNON == true)
							{	header_dump_and_opcode(NON);
								m_non();
								dumpregisters();
							}
							else m_non();	break;
			case	LDE :	if (TraceLDE == true)
							{	header_dump_and_opcode(LDE);
								m_lde();
								dumpregisters();
							}
							else m_lde();	break;
			case	UPD :	if (TraceUPD == true)
							{	header_dump_and_opcode(UPD);
								m_upd();
								dumpregisters();
							}
							else m_upd();	break;
			case	AP0 :	if (TraceAP0 == true)
							{	header_dump_and_opcode(AP0);
								m_ap0();
								dumpregisters();
							}
							else m_ap0();	break;
			case	RPLA:	if (TraceRPLA == true)
							{	header_dump_and_opcode(RPLA);
								m_rpla();
								dumpregisters();
							}
							else m_rpla();	break;
			case	RPLD:	if (TraceRPLD == true)
							{	header_dump_and_opcode(RPLD);
								m_rpld();
								dumpregisters();
							}
							else m_rpld();	break;
			case	PRNT:	if (TracePRNT == true)
							{	header_dump_and_opcode(PRNT);
								m_prnt();
								dumpregisters();
							}
							else m_prnt();	break;
			default		:	printf("opcode: %d \n", opcode);
							if (out_disk == true) 
								fprintf(outfile,"Opcode: %d\n", opcode);
							cleanup(10);break;
		}
		if (trace_ops == true && dumpsomething == true) dumpregisters();
		/* Info for debugging? */
	}
	if (s == NIL) return(omega);		/* return undefined */
	else return(car[s]);				/* return top of stack */
}
/* EXEC : this function takes an expression, FN, and an expression list, ARGS,
	and sets up and runs the SECD machine until termination. The result of
	the computation is left at the top of the stack. Only debugging output
	provided is a bad opcode error */
long 	exec(long fn, long args)
{	int		opcode;
	/* SECD initialization section */
	go_on = true;
	which_mode = execing;
	s = newnode(is_cons);
	car[s] = args;
	e = NIL;
	c = fn;
	d = NIL;
	/* end of SECD initialization section */
	while (go_on == true)
	{	opcode = car[car[c]]; 	/* we MUST first coerce to INTEGER */
		switch	(opcode)
		{	case	LD  :	m_ld(); 	break;
			case	LDC :	m_ldc(); 	break;
			case	LDF :	m_ldf();	break;
			case	AP  :	m_ap();		break;
			case	RTN :	m_rtn();	break;
			case	DUM :	m_dum();	break;
			case	RAP :	m_rap();	break;
			case 	SEL :	m_sel();	break;
			case	JOIN:	m_join();	break;
			case	CAR :	m_car();	break;
			case	CDR :	m_cdr();	break;
			case 	ATOM:	m_atom();	break;
			case	CONS:	m_cons();	break;
			case	EQ  :	m_eq();		break;
			case	ADD :	m_add();	break;
			case	SUB :	m_sub();	break;
			case	MUL :	m_mul();	break;
			case	DIV :	m_div();	break;
			case	REM :	m_rem();	break;
			case	LEQ :	m_leq();	break;
			case	STOP:	m_stop();	break;
			case	SOR	:	m_sor();	break;
			case	NON	:	m_non();	break;
			case	LDE :	m_lde();	break;
			case	UPD :	m_upd();	break;
			case	AP0 :	m_ap0();	break;
			case	RPLA:	m_rpla();	break;
			case	RPLD:	m_rpld();	break;
			case	PRNT:	m_prnt();	break;
			default		:	printf("ERROR: opcode = %d \n", opcode);
							if (out_disk == true) 
								fprintf(outfile,"ERROR: opcode = %d\n", opcode);
							cleanup(10);break;
		}
	}
	if (s == NIL) return(omega);		/* return undefined */
	else return(car[s]);				/* return top of stack */
}
/* ======================  END SECD MACHINE INTERPRETER  =================== */

/* ==========================  OUTPUT ROUTINES  ============================ */
/* This section is in two parts: one for the debugging time output, since the
internal computation can generate circular structures, and one for the final 
output, when no circular structures exist any longer. In one case we need to
mark and to avoid expressios that have already been visited - this cause some
difficulty in the output of shared non-circular structures. A possible solution
involves copying all lists before loading them in a register. This is both
inefficient and would vitiate the FORCE induced computation, when fully
implemented, and any RPLACA - RPLACD primitives, which would be useful for 
the implementation of an interpreter */

/* PUTTOKEN : this function prints a string either to a file or to the
	console or both. It does not break identifiers at line boundaries: they are
	put on the next line. This function is common to both output routines */
void puttoken(char token[MAX_TOKEN_LENGTH])
// char token[MAX_TOKEN_LENGTH];
{	int	toklen;
	toklen = (int)strlen(token);
	if ((out_buffer + toklen) > (MAX_OUT_LINE_LENGTH))
	{	if (out_disk == true) 	fputc('\n', outfile);
		if (out_echo == true) 	putchar('\n');	
		out_buffer = 0;
	}
	if (out_disk == true) 
		fprintf(outfile, "%s ", token);
	if (out_echo == true)
		printf("%s ",token);
	out_buffer = out_buffer + toklen + 1;
}
/* END PUTTOKEN */
	
/* PUTEXP : this function outputs a whole lisp expression */
void putexp(long exp)
{	long	p;
	char	temp[MAX_TOKEN_LENGTH];
	if (marked[exp] == false)  	/* this avoids circularities */
	{	if (is[exp] == is_symbol)
			puttoken(stringstore[car[exp]]);
		else if (is[exp] == is_number)
		{	stci_ld(temp, car[exp], 10);	/*convert to string for output */
			puttoken(temp);
		}
		else
		{	puttoken("(");
			p = exp;
			while (is[p] == is_cons && marked[p] == false)
			{	putexp(car[p]);
				marked[p] = true;
				p = cdr[p];
			}
			if (is[p] == is_symbol)
			{	if (strcmp(stringstore[car[p]], "NIL") != 0)
				{ 	puttoken(".");
					putexp(p);
				}
			}
			else
			{	puttoken(".");
				putexp(p);
			}
			puttoken(")");
		}
	}
}
/* END PUTEXP */

/* PUTOUTPUT : This function sends output to the screen, to a file or both 
	index is a global index... We need */
void putoutput(long result)
{	out_buffer = 0;
	for ( index = NIL; index < MAX_CONS; index++)
		marked[index] = false;
	putexp(result);
	if (out_disk == true) 	
	{	fputc('&',outfile);	/* end_of_input character */
		fputc('\n', outfile);
		fflush(outfile);
	}
	if (out_echo == true) 	printf("\n");
}			
/* END PUTOUTPUT */	

/* PUT_FINAL_EXP : this function outputs a whole lisp expression - no marking*/
void put_final_exp(long exp)
{	long	p;
	char	temp[MAX_TOKEN_LENGTH];
	if (is[exp] == is_symbol) puttoken(stringstore[car[exp]]);
	else if (is[exp] == is_number)
	{	stci_ld(temp, car[exp], 10);	/*convert to string for output */
		puttoken(temp);
	}
	else
	{	puttoken("(");
		p = exp;
		while (is[p] == is_cons)
		{	put_final_exp(car[p]);
			p = cdr[p];
		}
		if (is[p] == is_symbol)
		{	if (strcmp(stringstore[car[p]], "NIL") != 0)
			{ 	puttoken(".");
				put_final_exp(p);
			}
		}
		else
		{	puttoken(".");
			put_final_exp(p);
		}
		puttoken(")");
	}
}
/* END PUT_FINAL_EXP */

/* PUT_FINAL_OUTPUT : This function sends output to the screen, to a file or 
both : no marking, since the output is assumed a tree -
	index is a global index... We need */
void put_final_output(long result)
{	out_buffer = 0;
	put_final_exp(result);
	if (out_disk == true) 	
	{	fputc('&',outfile);	/* end_of_input character */
		fputc('\n', outfile);
		fflush(outfile);
	}
	if (out_echo == true) 	printf("\n");
}			
/* END PUTOUTPUT */	
/* ========================  END OUTPUT ROUTINES  ========================== */

/* ========================  CONVERSION ROUTINES  ========================== */
/* These routines exist to support a conversion from a LONG to an ASCII string.
A program that uses only INT rather than LONG will use a call to stci_d, rather
than a call to stci_ld, and these routines can be dropped */

static int stc_ld(register char *out, register unsigned long in, 
                  register int outlen, int signflag)
// register char *out;
// register unsigned long in;
// register int outlen;
// int signflag;
{
char revnum [8];
register int i=0;
register char *out0 = out;

	if (outlen<=0) return (0);
	
	if (in == 0) revnum[i++]=0;
	else
		while (in)
		{
			revnum[i++] = (char)(in - (in/10)*10);
			in /= 10;
		}
	
	if (signflag)
	{
		*out++ = '-';
		outlen--;
	}
	
	for (; i && outlen; i--, outlen--)
		*out++ = revnum[i-1] + '0';
	
	*out = '\0';
	
	return (out-out0);
	
}

/* THIS WOULD BE REPLACED BY stci_d in a version with no LONGs */
int stci_ld(char *out, unsigned long in, int outlen)
{
	return (stc_ld(out, (in>=0?in:-in), outlen, in<0));
}
/* =======================  END CONVERSION ROUTINES  ======================= */

/* ============================  INPUT ROUTINES  =========================== */
/* GET_CHAR_FROM_INBUFFER : this gets a character from the input buffer and
	does appropriate input buffer housecleaning. We allow comments in text
	files, although comments are not accepted from the console */
char	get_char_from_inbuffer(void)
{	char 	ch;
	if (in_disk == true)	/* you are reading this from disk */
	{	ch = fgetc(infile);
		if ((ch != EOF) && (in_echo == true))
		{ 	if (put_back_char == false) 
				putchar(ch); /* you do not want chars appearing twice */
			else put_back_char = false;
		}
		if (ch == EOF) cleanup(2);
		else if (ch == '\n' || ch == '\t' || ch == '\r') return(BLANK);
		else if (ch == '\;')   /* comment delimiter */
		{	do 	{	ch = fgetc(infile);
					if (ch == EOF) cleanup(2); /* panic exit... */
					if (in_echo == true) putchar(ch);
				}
			while (ch != '\n');
			return(BLANK);	
		}
		else return(ch);
	}
	else if (in_buff_pointer >= linelength)
	{	in_buff_pointer = 0;
		putchar('>');
		while ((linelength = strlen(gets(in_line))) < 1)
			 putchar('>');
		if (in_line[0] == '$') cleanup(2);
		return(BLANK);
	}
	else	
	{	ch = in_line[in_buff_pointer];
		in_buff_pointer++;
		if (ch == '\t')
			return(BLANK);
		else	return(ch);
	}	 
}
/* END GET_CHAR_FROM_INBUFFER */

/* GETTOKEN : this function gets the next token from the input buffer and
	returns the type of the token */
void gettoken(void)
{	char ch;
	char short_string[2]; 
	short_string[0] = '\0';
	short_string[1] = '\0';
	token[0] = '\0';
	do { ch = get_char_from_inbuffer();} while (isspace(ch));	
	if (ch == END_OF_INPUT) 
	{	tokentype = endfile;
		token[0] = ')';
		token[1] = '\0';
		if (in_echo == true) putchar('\n');
	}
	else if (isdigit(ch) || ch == '-') 	/* a number !! */
	{	tokentype = numeric;
		do 
		{	short_string[0] = ch;
			if (strlen(token) < MAX_TOKEN_LENGTH)
				strcat(token, short_string);
			ch = get_char_from_inbuffer();
		}	while (isdigit(ch));
		if (ch != BLANK) 
		{	if (in_disk == true) 
			{	ungetc(ch,infile); /* put last char back */
				put_back_char = true;
			}
			else in_buff_pointer--;
		}
	}
	else if (isalpha(ch))
	{	tokentype = alphanumeric;
	 	do
		{	short_string[0] = ch;
			if (strlen(token) < MAX_TOKEN_LENGTH)
				strcat(token, short_string);
			ch = get_char_from_inbuffer();
		}	while (isalnum(ch));
		if (isspace(ch) == 0)	/*a potentially significant character */
		{	if (in_disk == true) 
			{	ungetc(ch,infile); /* put last char back */
				put_back_char = true;
			}
			else in_buff_pointer--;
		}
	}
	else
	{	tokentype = delimiter;
		short_string[0] = ch;
		strcat(token, short_string);
	}
}
/* END GETTOKEN */	
	 
/* GETEXP : this function returns an expression */
long 	getexp(void)
{	long 	exp;
	if (token[0] == '(')
	{	gettoken();
		exp = getexplist();
		gettoken();
	}
	else if (tokentype == numeric)
	{	exp = newnode(is_number);
		car[exp] = atol(token);
		gettoken();
	}
	else if (tokentype == alphanumeric)
	{	exp = newnode(is_symbol);
		install(exp, token);
		gettoken();
	}
	return(exp);
}
/* END GETEXP */

/* GETEXPLIST : this function returns (a pointer to) an expression list */
long 	getexplist(void)
{	long 	exp;
	exp = newnode(is_cons);			/* this is a list, so make a cons cell */
	car[exp] = getexp();		 	/* get the head of the list */
	if (token[0] == '.')
	{	gettoken();
		cdr[exp] = getexp();       	/* get the tail - dotted pair */
	}
	else if (token[0] != ')' && token[0] != END_OF_INPUT)
		cdr[exp] = getexplist();	/* get the tail - NOT dotted pair */
	return(exp);					/* return pointer to tree or list */
}
	
/* GETINPUT : This function reads input from some file. When COMPIN is TRUE
	it reads an expression - i.e. a function - when FALSE it reads an 
	expression list - i.e. an argument list for a function. Acts both as a
	parser and a lexical scanner. */
long 	getinput(bool compin)
{	which_mode = parsing;
	put_back_char = false;
	gettoken(); 	/* get the first token */
	if (compin == true)  	
		return(getexp());
	else					
		return(getexplist());
}		
/* END GETINPUT */
/* =========================  END INPUT ROUTINES  ========================== */

/* ======================  USER INTERFACE ROUTINES  ======================== */

/* GETPROGFILE : this function opens the file that contains the program to be 
	executed. If another file is open, it will close it first. Only one 
	file can be open for reading and one for writing at the same time. */
void getprogfile(void)
{	char	filename[MAX_LINE_LENGTH]; /* why not? */
	filename[0] = '\0';
	save_function = false; 
	keep_going = true;
	in_disk = true;
	fputs("Execute: ",stdout);
	do gets(filename); while (strlen(filename) == 0);
	if (strcmp(filename, "quit") == 0 || strcmp(filename, "QUIT") == 0 )
		keep_going = false;
	else if ((strcmp(filename, "console") == 0) ||
			 (strcmp(filename, "CONSOLE") == 0)) 
		in_disk = false;
	else if (strcmp(filename, "") > 0)
	{	fclose(infile);	/* try to close possibly open file */
		in_disk = true;
		fputs("Echo to console: ", stdout);
		fun_echo = yes_no();
		while ((infile = fopen(filename, "r")) == NULL) 
		{	fputs("File not found. Try again? ", stdout);
			if (yes_no() == true)
			{	fputs("Argument File: ", stdout);
				do gets(filename); while (strlen(filename) == 0);
			}
			else	cleanup(5);
		}
	}
	if (keep_going == true)
	{	fputs("Multiple Execution: ", stdout);
		save_function = yes_no();
	}
	in_echo = fun_echo;
}
/* END GETPROGFILE */

/* SETOUTFILE : this function sets up the disk file, if any, to which the 
result of the computation will be written. */
void setoutfile(void)
{	char	filename[MAX_LINE_LENGTH];
	filename[0] = '\0';
	fputs("Output File: ", stdout);
	do gets(filename); while (strlen(filename) == 0);
	if ((strcmp(filename, "console") == 0) ||
	    (strcmp(filename, "CONSOLE") == 0))
	{	out_disk = false;
		out_echo = true;
	}
	else if (strcmp(filename, "") > 0)
	{	out_disk = true;
		outfile = fopen(filename, "w");
		fputs("Echo to console: ", stdout);
		out_echo = yes_no();
	}
}
/* END SETOUTFILE */

/* GETARGFILE: get the parameters of the function */
void getargfile(void)
{	char	filename[MAX_LINE_LENGTH];
	filename[0] = '\0';
	fputs("Argument File: ", stdout);
	do gets(filename); while (strlen(filename) == 0);
	if ((strcmp(filename, "quit") == 0) ||
		(strcmp(filename, "QUIT") == 0))
		keep_going = false;
	if ((strcmp(filename, "console") == 0) ||
	    (strcmp(filename, "CONSOLE") == 0))
	{	in_disk = false;
		arg_echo = false;
	}
	else if (strcmp(filename, "") > 0) 	
	{	fclose(infile);
		in_disk = true;
		arg_echo = true;
		while ((infile = fopen(filename, "r")) == NULL) 
		{	fputs("File not found. Try again? ", stdout);
			if (yes_no() == true)
			{	fputs("Argument File: ", stdout);
				do gets(filename); while (strlen(filename) == 0);
			}
			else	cleanup(5);
		}
		fputs("Echo to console: ", stdout);
		if ((in_echo = yes_no()) == false)
			arg_echo = false;
	}
	in_echo = arg_echo;
}
/* END GETARGFILE */
/* ====================  END USER INTERFACE ROUTINES  ====================== */	

/* =============================   MAIN   ================================== */
/* MAIN : this is the main loop. It must first allocate all the large arrays,
	which cannot be allocated at compile time */
int main(void)
{ 	start_arrays();
	start();
	while (flag == true)
	{	getprogfile();
		if (flag == true)
		{	fn = getinput(true);
			while (flag == true)
			{	getargfile();
				if (flag == true)
				{	args = getinput(false);
					setoutfile(); 
				 	fputs("\nTrace opcodes?   ", stdout);
					trace_ops = yes_no();
					if (trace_ops == true)
					{	fputs("Trace ALL opcodes? ", stdout);
						if (yes_no() == false)
							collect_opcodes_to_trace();
						debug_mode = true;
					}
					else
					{	kill_opcode_trace();
						if (dumpsomething == true) debug_mode = true;
						else debug_mode = false;
					}
					if (debug_mode == true) 
						result = debug_exec(fn,args);
					else
						result = exec(fn,args);
					printf("Exited computation\n"); 
					args = NIL;
					put_final_output(result);
					fputs("\nDo you want to change register dumps? ", stdout);
					if (yes_no() == true)
					{	debug_mode = false;
						check_for_register_dumps();
					}
					fputs("New Function? ", stdout);
					if (yes_no() == true)
					{	getprogfile();		
				 		fn = getinput(true);
				 	} 
				}
			}
			keep_going = true; 
		}
	}
	cleanup(1);
}
