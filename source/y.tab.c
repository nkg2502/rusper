#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "rusper.y"
/*
 * Kookmin University
 * 컴퓨터공학부
 * 3학년
 * 정태성
 *
 * rusper.y
 * 
 */

#include <stdio.h>
#include <string.h>

enum node_number {
	STATEMENT_LIST,
	COMPOUND_STATEMENT,
	DECLARATION_STATEMENT,
	SELECTION_STATEMENT,
	BREAK_STATEMENT,
	FOR_STATEMENT,
	DO_STATEMENT,
	PRINT_STATEMENT,
	PRINT_EXPR_LIST,
	OUTPUT_STATEMENT,
	EXPRESSION
};

enum {
	TERMINAL = 0,
	NON_TERMINAL,
	STACK_MAX = 1024,
};

typedef struct _AST_node {
	int token_number;
	char *token_value;
	int node_type;
	struct _AST_node *child;
	struct _AST_node *sibling;
} AST_node;

int cmp_stmt_cnt_stack[STACK_MAX];
int cmp_stmt_cnt_sp;
int cmp_stmt_cnt;
int print_stmt_cnt;

AST_node *AST_stack[STACK_MAX];
int sp;

AST_node *AST_root;

AST_node *build_node(int t_num, char *t_val);
AST_node *build_tree(int n_num);

int loop_label_count;
int cmp_label_count;
void generate_lmc_asm_code(FILE *fp, AST_node *root);
void generate_lmc_asm_code_stmt_expr(FILE *fp, AST_node *node);

void treverse(AST_node *node, int tab);
void print_stack(char *s);


#line 67 "rusper.y"
typedef union {
	int integer;
	char *str;
} YYSTYPE;
#line 92 "y.tab.c"
#define T_EOF 257
#define T_ERROR 258
#define T_VAR 259
#define T_IF 260
#define T_LPAREN 261
#define T_RPAREN 262
#define T_COLON 263
#define T_DCOLON 264
#define T_BREAK 265
#define T_FOR 266
#define T_SEPARATOR 267
#define T_DO 268
#define T_LBRACKET 269
#define T_RBRACKET 270
#define T_LCURLYBRACE 271
#define T_RCURLYBRACE 272
#define T_ASSIGNMENT 273
#define T_PLUS 274
#define T_MINUS 275
#define T_MUL 276
#define T_DIV 277
#define T_REMAINDER 278
#define T_EQUAL 279
#define T_NOT_EQUAL 280
#define T_NOT 281
#define T_AND 282
#define T_OR 283
#define T_LT 284
#define T_GT 285
#define T_LT_EQUAL 286
#define T_GT_EQUAL 287
#define T_RANDOM 288
#define T_ITERATOR 289
#define T_OUTPUT 290
#define T_IDENTIFIER 291
#define T_INTEGER 292
#define T_COMMENT 293
#define T_STRING_LITERAL 294
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    2,    2,    4,    4,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    5,    6,    7,    8,    9,
   10,   11,   17,   17,   18,   18,   12,   13,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   20,   21,   21,
   21,   21,   21,   22,   22,   23,   23,   23,   24,   24,
   24,   24,   25,   26,   27,   19,   16,   14,
};
short yylen[] = {                                         2,
    1,    1,    1,    2,    1,    2,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    2,    1,    7,    1,    9,
    7,    3,    1,    2,    1,    3,    4,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    6,    6,    6,
    6,    6,    6,    6,    6,    4,    6,    6,    6,    6,
    6,    6,    6,    1,    1,    1,    1,    1,
};
short yydefred[] = {                                      0,
    0,    0,   19,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   54,    0,   58,   57,   28,    0,    1,    2,
    0,    7,    8,    9,   10,   11,   12,   13,   14,   15,
   37,   17,   36,   29,   30,   31,   32,   33,   34,   35,
   16,    0,    0,    0,    0,   56,    0,    0,   25,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    4,    0,    0,    0,
    0,   22,   24,   55,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   26,    0,    0,    0,    0,    0,
    0,    0,    0,   46,    0,    0,    0,    0,    0,    0,
    0,   27,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   38,   39,   40,   41,   42,   43,
   44,   45,   47,   48,   49,   50,   51,   52,   53,    6,
   18,    0,   21,    0,   20,
};
short yydgoto[] = {                                      28,
   29,   30,  141,  142,   32,   33,   34,   35,   36,   37,
   38,   39,   40,   41,   42,   43,   57,   58,   59,   44,
   45,   46,   47,   48,   49,   50,   85,
};
short yysindex[] = {                                   -180,
 -290, -256,    0, -255, -254, -267, -253, -235, -233, -232,
 -231, -230, -227, -226, -225, -224, -223, -222, -221, -220,
 -219, -218,    0, -217,    0,    0,    0,    0,    0,    0,
 -180,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -159, -246, -246, -159,    0, -208, -267,    0, -290,
 -159, -159, -159, -159, -159, -159, -159, -159, -159, -159,
 -159, -159, -159, -159, -246, -247,    0, -213, -216, -212,
 -202,    0,    0,    0, -215, -214, -196, -195, -193, -192,
 -191, -190, -184, -186, -185, -177, -175, -136, -133, -132,
 -179, -128, -246, -127,    0, -159, -159, -159, -159, -159,
 -159, -159, -159,    0, -159, -159, -159, -159, -159, -159,
 -246,    0, -180, -124, -180, -123, -122, -121, -120, -119,
 -118, -117, -116, -115, -114, -113, -112, -111, -110, -109,
 -180, -176, -108, -106,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -180,    0, -105,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  154,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -107,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -104,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  124,    2,  -93,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   24,  -52,  -30,  102,    0,   85,    0,
    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 163
short yytable[] = {                                      78,
   25,   31,   81,   55,   52,   53,   54,   60,   86,   87,
   88,   89,   90,   91,   92,   93,   94,   95,   96,   97,
   98,   99,   79,   80,   51,   61,   56,   62,   63,   64,
   65,  144,   31,   66,   67,   68,   69,   70,   71,   72,
   73,   74,   75,   76,  100,   26,   56,  160,  102,  104,
  103,  106,  107,  126,  127,  128,  129,  130,  131,  132,
  133,   82,  134,  135,  136,  137,  138,  139,  164,  105,
  108,  109,  124,  110,  111,  112,  113,  114,    1,    2,
  115,  116,  122,   84,    3,    4,  161,    5,    6,  117,
  140,  118,    7,    8,    9,   10,   11,   12,   13,   14,
   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
   25,   26,   27,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
  119,   25,   26,  120,  121,  123,  125,  143,  145,  146,
  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,
  157,  158,  159,    3,   77,  162,  163,  165,    5,   83,
  101,    0,   23,
};
short yycheck[] = {                                      52,
  291,    0,   55,  271,  261,  261,  261,  261,   61,   62,
   63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
   73,   74,   53,   54,    1,  261,  294,  261,  261,  261,
  261,  125,   31,  261,  261,  261,  261,  261,  261,  261,
  261,  261,  261,  261,   75,  292,  294,  141,  262,  262,
  267,  267,  267,  106,  107,  108,  109,  110,  111,  112,
  113,  270,  115,  116,  117,  118,  119,  120,  162,  272,
  267,  267,  103,  267,  267,  267,  267,  262,  259,  260,
  267,  267,  262,   60,  265,  266,  263,  268,  269,  267,
  121,  267,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,  286,  287,  288,  289,  290,
  291,  292,  293,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  284,  285,  286,  287,  288,  289,
  267,  291,  292,  267,  267,  264,  264,  262,  262,  262,
  262,  262,  262,  262,  262,  262,  262,  262,  262,  262,
  262,  262,  262,    0,   31,  264,  263,  263,  263,   58,
   76,   -1,  270,
};
#define YYFINAL 28
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 294
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"T_EOF","T_ERROR","T_VAR","T_IF",
"T_LPAREN","T_RPAREN","T_COLON","T_DCOLON","T_BREAK","T_FOR","T_SEPARATOR",
"T_DO","T_LBRACKET","T_RBRACKET","T_LCURLYBRACE","T_RCURLYBRACE","T_ASSIGNMENT",
"T_PLUS","T_MINUS","T_MUL","T_DIV","T_REMAINDER","T_EQUAL","T_NOT_EQUAL",
"T_NOT","T_AND","T_OR","T_LT","T_GT","T_LT_EQUAL","T_GT_EQUAL","T_RANDOM",
"T_ITERATOR","T_OUTPUT","T_IDENTIFIER","T_INTEGER","T_COMMENT",
"T_STRING_LITERAL",
};
char *yyrule[] = {
"$accept : program",
"program : file",
"file : statement_list",
"statement_list : statement",
"statement_list : statement statement_list",
"compound_statement : statement",
"compound_statement : statement compound_statement",
"statement : declaration_statement",
"statement : expression_statement",
"statement : selection_statement",
"statement : break_statement",
"statement : for_statement",
"statement : do_statement",
"statement : print_statement",
"statement : output_statement",
"statement : comment_statement",
"declaration_statement : T_VAR identifier",
"expression_statement : expression",
"selection_statement : T_IF T_LPAREN expression T_RPAREN T_DCOLON compound_statement T_COLON",
"break_statement : T_BREAK",
"for_statement : T_FOR T_LPAREN integer T_SEPARATOR integer T_RPAREN T_DCOLON compound_statement T_COLON",
"do_statement : T_DO T_LPAREN integer T_RPAREN T_DCOLON compound_statement T_COLON",
"print_statement : T_LBRACKET print_expression_list T_RBRACKET",
"print_expression_list : print_expression",
"print_expression_list : print_expression print_expression_list",
"print_expression : string_literal",
"print_expression : T_LCURLYBRACE expression T_RCURLYBRACE",
"output_statement : T_OUTPUT T_LPAREN string_literal T_RPAREN",
"comment_statement : T_COMMENT",
"expression : assignment_expression",
"expression : arithmetic_expression",
"expression : equality_expression",
"expression : relational_expression",
"expression : logical_expression",
"expression : random_expression",
"expression : iterator_expression",
"expression : integer",
"expression : identifier",
"assignment_expression : T_ASSIGNMENT T_LPAREN lvalue T_SEPARATOR expression T_RPAREN",
"arithmetic_expression : T_PLUS T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"arithmetic_expression : T_MINUS T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"arithmetic_expression : T_MUL T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"arithmetic_expression : T_DIV T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"arithmetic_expression : T_REMAINDER T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"equality_expression : T_EQUAL T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"equality_expression : T_NOT_EQUAL T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"relational_expression : T_NOT T_LPAREN expression T_RPAREN",
"relational_expression : T_AND T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"relational_expression : T_OR T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"logical_expression : T_LT T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"logical_expression : T_GT T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"logical_expression : T_LT_EQUAL T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"logical_expression : T_GT_EQUAL T_LPAREN expression T_SEPARATOR expression T_RPAREN",
"random_expression : T_RANDOM T_LPAREN integer T_SEPARATOR integer T_RPAREN",
"iterator_expression : T_ITERATOR",
"lvalue : identifier",
"string_literal : T_STRING_LITERAL",
"integer : T_INTEGER",
"identifier : T_IDENTIFIER",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 707 "rusper.y"

AST_node *build_node(int t_num, char *t_val)
{
	AST_node *ptr;
	int val_len;

	ptr = (AST_node *) malloc(sizeof(AST_node));
	if(NULL == ptr) {
		fprintf(stderr, "Error : %s : malloc\n", __func__);
		exit(255);
	}

	ptr->token_number = t_num;

	val_len = strlen(t_val) + 1;
	ptr->token_value = (char *) malloc(sizeof(char) * val_len);
	strncpy(ptr->token_value, t_val, val_len);

	ptr->node_type = TERMINAL;
	ptr->child = ptr->sibling = NULL;

	return ptr;
}

AST_node *build_tree(int n_num)
{
	AST_node *ptr;
	
	ptr = (AST_node *) malloc(sizeof(AST_node));
	if(NULL == ptr) {
		fprintf(stderr, "Error : %s : malloc\n", __func__);
		exit(255);
	}

	ptr->token_number = n_num;
	ptr->token_value = NULL;
	ptr->node_type = NON_TERMINAL;
	ptr->child = ptr->sibling = NULL;

	return ptr;
}

void generate_lmc_asm_code(FILE *fp, AST_node *root)
{
	AST_node *iter = root;

	fprintf(fp, "BOX\t_LOOP_TEMP\n");
	fprintf(fp, "BOX\t_NUM_TEMP\n");
	fprintf(fp, "BOX\t_LOGC_TEMP\n");
	fprintf(fp, "BOX\t_CNT_TEMP\n");
	fprintf(fp, "BOX\t_ITER_TEMP\n");
	fprintf(fp, "BOX\t_REDIRECTION_FILE\n");

	while(NULL != iter) {

		switch(iter->token_number) {
			case DECLARATION_STATEMENT:
				fprintf(fp, "BOX\t%s\n", iter->child->sibling->token_value);
				break;
			case SELECTION_STATEMENT:
				generate_lmc_asm_code_stmt_expr(fp, iter->child);
				break;
			case BREAK_STATEMENT:
				fprintf(fp, "JMP LOOP_LABEL_%d\n", loop_label_count);
				break;
			case FOR_STATEMENT:
				break;
			case DO_STATEMENT:
				generate_lmc_asm_code_stmt_expr(fp, iter->child);
				break;
			case PRINT_STATEMENT:
				break;
			case OUTPUT_STATEMENT:
				break;
			case EXPRESSION:
				generate_lmc_asm_code_stmt_expr(fp, iter->child);
				break;
			default:
				fprintf(stderr, "ERROR\n");
				exit(255);
				break;
		}

		iter = iter->sibling;
	}
}

void generate_lmc_asm_code_stmt_expr(FILE *fp, AST_node *node)
{
	AST_node *lhs;
	AST_node *rhs;

	if(NULL == node)
		return;
	if(NULL == node->sibling)
		return;

	lhs = node->sibling;
	rhs = node->sibling->sibling;

	switch(node->token_number) {
		case T_DO:
			fprintf(fp, "LDA\t%s%s\n", T_INTEGER == lhs->token_number ? "#" : "", lhs->token_value);
			fprintf(fp, "STA\t_LOOP_TEMP\n");
			fprintf(fp, "LDA\t#0\n");
			fprintf(fp, "STA\t_CNT_TEMP\n");
			fprintf(fp, "LOOP_LABEL_%d:\n", loop_label_count);
			fprintf(fp, "LDA\t_CNT_TEMP\n");
			fprintf(fp, "CMPA\t_LOOP_TEMP\n");
			fprintf(fp, "JCOND BREAK_LABEL_%d:\n", loop_label_count);

			// loop for compound statement
			if(NON_TERMINAL == rhs->node_type) {
				if(NON_TERMINAL == rhs->child->node_type)
					generate_lmc_asm_code_stmt_expr(fp, rhs->child->child);
				else
					generate_lmc_asm_code_stmt_expr(fp, rhs->child);
			}

			fprintf(fp, "LDA\t_CNT_TEMP\n");
			fprintf(fp, "ADDA\t#1\n");
			fprintf(fp, "JMP LOOP_LABEL_%d\n", loop_label_count);
			fprintf(fp, "BREAK_LABEL_%d:\n", loop_label_count);
			++loop_label_count;
			break;
		case T_ASSIGNMENT:

			if(NON_TERMINAL == rhs->node_type) {
				generate_lmc_asm_code_stmt_expr(fp, rhs->child);
			} else {
				fprintf(fp, "LDA\t%s%s\n", T_INTEGER == rhs->token_number ? "#" : "", rhs->token_value);
			}

			fprintf(fp, "STA\t%s\n", lhs->token_value);

			break;
		case T_PLUS:

			if(NON_TERMINAL == lhs->node_type) {
				generate_lmc_asm_code_stmt_expr(fp, lhs->child);
				fprintf(fp, "STA\t_NUM_TEMP\n");
			} else
				fprintf(fp, "LDA\t%s%s\n", T_INTEGER == lhs->token_number ? "#" : "", lhs->token_value);

			if(NON_TERMINAL == rhs->node_type) {
				generate_lmc_asm_code_stmt_expr(fp, rhs->child);
				fprintf(fp, "ADDA\t_NUM_TEMP\n");
			} else
				fprintf(fp, "ADDA\t%s%s\n", T_INTEGER == rhs->token_number ? "#" : "", rhs->token_value);
			break;
		case T_MINUS:
			break;
		case T_MUL:
			break;
		case T_DIV:
			break;
		case T_REMAINDER:
			break;
		case T_IF:

			if(NON_TERMINAL == lhs->node_type) {
				generate_lmc_asm_code_stmt_expr(fp, lhs->child);
			} else {
				fprintf(fp, "LDA\t%s%s\n", T_INTEGER == lhs->token_number ? "#" : "", lhs->token_value);
			}
			fprintf(fp, "STA\t_LOGC_TMP\n");
			fprintf(fp, "LDA\t_LOGC_TMP\n");
			fprintf(fp, "CMPA\t#0\n");
			fprintf(fp, "JCOND IF_LABEL_%d\n", cmp_label_count);

			if(NON_TERMINAL == rhs->node_type) {
				if(NON_TERMINAL == rhs->child->node_type)
					generate_lmc_asm_code_stmt_expr(fp, rhs->child->child);
				else
					generate_lmc_asm_code_stmt_expr(fp, rhs->child);
			}

			fprintf(fp, "IF_LABEL_%d:\n", cmp_label_count);
			++cmp_label_count;
			break;
		case T_AND:
			break;
		case T_OR:
			break;
		case T_LT:
			break;
		case T_GT:
			break;
		case T_LT_EQUAL:
			break;
		case T_GT_EQUAL:
			break;
		case T_NOT_EQUAL:
			break;
		case T_EQUAL:
			break;
		case T_LBRACKET:
			break;
		default:
			fprintf(stderr, "ERROR expr : %d\n", node->token_number);
			exit(255);
			break;
	}


}

void treverse(AST_node *node, int tab)
{
	int i;

	if(NULL == node)
		return;
	
	for(i = 0; i < tab; ++i)
		printf("\t");	

	printf("%d, %d\t", node->node_type, node->token_number);
	if(node->node_type == TERMINAL)
		printf("%s\n", node->token_value);
	else
		printf("\n");

	treverse(node->child, tab + 1);
	treverse(node->sibling, tab);
}

void print_stack(char *s)
{
	int i;
	printf("%s\n", s);
	for(i = sp - 1; 0 <= i; --i) {

		printf("[%d] %s, %d ", i, AST_stack[i]->node_type ? "NON" : "TER", AST_stack[i]->token_number);

		if(AST_stack[i]->node_type == TERMINAL) {
			printf(": %s\n", AST_stack[i]->token_value);
		} else
			printf("\n");
	}
}

///*
int main(void)
{
	sp = 0;
	cmp_stmt_cnt_sp = 0;
	loop_label_count = 0;
	cmp_label_count = 0;

	yyparse();

	printf("Abstract Syntax Tree\n");
	treverse(AST_root, 0);

	printf("\nGenerate LMC assembler Code\n");
	generate_lmc_asm_code(stdout, AST_root);

	return 0;
}
// */

void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
}
#line 637 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 2:
#line 116 "rusper.y"
{
			AST_node *iter;
			int i;

			iter = AST_root = AST_stack[0];
			for(i = 1; i < sp; ++i) {
				iter->sibling = AST_stack[i];
				iter = iter->sibling;
			}
		}
break;
case 5:
#line 133 "rusper.y"
{
				AST_node *ptr;
				AST_node *iter;
				int stmt_sp;
				int cmp_stmt_sp;

				cmp_stmt_sp = stmt_sp = sp - cmp_stmt_cnt;

				ptr = build_tree(COMPOUND_STATEMENT);
				iter = ptr->child = AST_stack[stmt_sp];

				++stmt_sp;
				while(stmt_sp < sp) {
					iter->sibling = AST_stack[stmt_sp];
					iter = iter->sibling;
					++stmt_sp;
				}

				AST_stack[cmp_stmt_sp] = ptr;
				sp = cmp_stmt_sp + 1;
			}
break;
case 7:
#line 158 "rusper.y"
{
			/* build tree*/
			AST_node *ptr;

			ptr = build_tree(DECLARATION_STATEMENT);
			ptr->child = AST_stack[--sp];

			/* push*/
			AST_stack[sp++] = ptr;
		}
break;
case 9:
#line 170 "rusper.y"
{
			/* build tree*/
			AST_node *ptr;

			ptr = build_tree(SELECTION_STATEMENT);
			ptr->child = AST_stack[--sp];

			/* push*/
			AST_stack[sp++] = ptr;

		}
break;
case 10:
#line 182 "rusper.y"
{
			/* build tree*/
			AST_node *ptr;

			ptr = build_tree(BREAK_STATEMENT);
			ptr->child = AST_stack[--sp];

			/* push*/
			AST_stack[sp++] = ptr;

		}
break;
case 11:
#line 194 "rusper.y"
{
			/* build tree*/
			AST_node *ptr;

			ptr = build_tree(FOR_STATEMENT);
			ptr->child = AST_stack[--sp];

			/* push*/
			AST_stack[sp++] = ptr;

		}
break;
case 12:
#line 206 "rusper.y"
{
			/* build tree*/
			AST_node *ptr;

			ptr = build_tree(DO_STATEMENT);
			ptr->child = AST_stack[--sp];

			/* push*/
			AST_stack[sp++] = ptr;
		}
break;
case 13:
#line 217 "rusper.y"
{
			/* build tree*/
			AST_node *ptr;

			ptr = build_tree(PRINT_STATEMENT);
			ptr->child = AST_stack[--sp];

			/* push*/
			AST_stack[sp++] = ptr;

		}
break;
case 14:
#line 229 "rusper.y"
{
			/* build tree*/
			AST_node *ptr;

			ptr = build_tree(OUTPUT_STATEMENT);
			ptr->child = AST_stack[--sp];

			/* push*/
			AST_stack[sp++] = ptr;

		}
break;
case 16:
#line 244 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;

				ptr = build_node(T_VAR, "VAR");
				ptr->sibling = AST_stack[--sp];

				AST_stack[sp++] = ptr;
			}
break;
case 18:
#line 259 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_IF, "IF");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 19:
#line 275 "rusper.y"
{
				AST_stack[sp++] = build_node(T_BREAK, "BREAK");
			}
break;
case 20:
#line 281 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;
				AST_node *cmp_stmt;

				ptr = build_node(T_FOR, "FOR");

				cmp_stmt = AST_stack[--sp];
				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;
				ptr->sibling->sibling->sibling = cmp_stmt;

				AST_stack[sp++] = ptr;
			}
break;
case 21:
#line 300 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_DO, "DO");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 22:
#line 316 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;

				ptr = build_node(T_LBRACKET, "PRINT");
				ptr->sibling = AST_stack[--sp];

				AST_stack[sp++] = ptr;
			}
break;
case 24:
#line 329 "rusper.y"
{
				AST_node *ptr;
				AST_node *iter;
				int stmt_sp;
				int print_stmt_sp;

				print_stmt_sp = stmt_sp = sp - print_stmt_cnt;

				ptr = build_tree(PRINT_EXPR_LIST);
				iter = ptr->child = AST_stack[stmt_sp];

				++stmt_sp;
				while(stmt_sp < sp) {
					iter->sibling = AST_stack[stmt_sp];
					iter = iter->sibling;
					++stmt_sp;
				}

				AST_stack[print_stmt_sp] = ptr;
				sp = print_stmt_sp + 1;
			}
break;
case 27:
#line 357 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;

				ptr = build_node(T_OUTPUT, "OUTPUT");
				ptr->sibling = AST_stack[--sp];

				AST_stack[sp++] = ptr;
			}
break;
case 29:
#line 372 "rusper.y"
{
				/* build tree*/
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				/* push*/
				AST_stack[sp++] = ptr;
			}
break;
case 30:
#line 383 "rusper.y"
{
				/* build tree*/
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				/* push*/
				AST_stack[sp++] = ptr;
			}
break;
case 31:
#line 394 "rusper.y"
{
				/* build tree*/
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				/* push*/
				AST_stack[sp++] = ptr;
			}
break;
case 32:
#line 405 "rusper.y"
{
				/* build tree*/
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				/* push*/
				AST_stack[sp++] = ptr;
			}
break;
case 33:
#line 416 "rusper.y"
{
				/* build tree*/
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				/* push*/
				AST_stack[sp++] = ptr;
			}
break;
case 34:
#line 427 "rusper.y"
{
				/* build tree*/
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				/* push*/
				AST_stack[sp++] = ptr;
			}
break;
case 35:
#line 438 "rusper.y"
{
				/* build tree*/
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				/* push*/
				AST_stack[sp++] = ptr;
			}
break;
case 38:
#line 453 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_ASSIGNMENT, "=");
				
				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 39:
#line 469 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_PLUS, "+");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
break;
case 40:
#line 484 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_MINUS, "-");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
break;
case 41:
#line 499 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_MUL, "*");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
break;
case 42:
#line 514 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_DIV, "/");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
break;
case 43:
#line 529 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_REMAINDER, "%");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
break;
case 44:
#line 546 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_EQUAL, "==");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 45:
#line 560 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_NOT_EQUAL, "!=");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 46:
#line 576 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;

				ptr = build_node(T_NOT, "!");

				ptr->sibling = AST_stack[--sp];

				AST_stack[sp++] = ptr;

			}
break;
case 47:
#line 588 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_AND, "&&");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 48:
#line 602 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_OR, "||");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 49:
#line 618 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_LT, "<");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 50:
#line 632 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_GT, ">");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 51:
#line 646 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_LT, "<=");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 52:
#line 660 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_LT, ">=");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 53:
#line 676 "rusper.y"
{
				/* build sibling*/
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_RANDOM, "RANDOM");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
break;
case 54:
#line 691 "rusper.y"
{ AST_stack[sp++] = build_node(T_ITERATOR, yylval.str); }
break;
case 56:
#line 697 "rusper.y"
{ AST_stack[sp++] = build_node(T_STRING_LITERAL, yylval.str); }
break;
case 57:
#line 700 "rusper.y"
{ AST_stack[sp++] = build_node(T_INTEGER, yylval.str); }
break;
case 58:
#line 703 "rusper.y"
{ AST_stack[sp++] = build_node(T_IDENTIFIER, yylval.str); }
break;
#line 1434 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
