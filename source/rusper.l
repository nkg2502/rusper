%{

/*
 *
 * rusper.l 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

enum {
	STACK_MAX = 1024,
};

extern int cmp_stmt_cnt_stack[STACK_MAX];
extern int cmp_stmt_cnt_sp;
extern int cmp_stmt_cnt;
extern int print_stmt_cnt;
extern int sp;

%}
letter	[a-zA-Z_]
nonzero_digit	[1-9]
digit	[0-9]
%%
"VAR"		{ yylval.str = yytext; return T_VAR; }
"IF"		{ yylval.str = yytext; return T_IF; }
"("		{ yylval.str = yytext;return T_LPAREN;}
")"		{ yylval.str = yytext;return T_RPAREN;}
"::"		{ yylval.str = yytext; cmp_stmt_cnt_stack[cmp_stmt_cnt_sp++] = sp; return T_DCOLON;}
":"		{ yylval.str = yytext; cmp_stmt_cnt = sp - cmp_stmt_cnt_stack[--cmp_stmt_cnt_sp]; return T_COLON;}
"BREAK"		{ yylval.str = yytext;return T_BREAK;}
"FOR"		{ yylval.str = yytext;return T_FOR;}
","		{ yylval.str = yytext;return T_SEPARATOR;}
"DO"		{ yylval.str = yytext;return T_DO;}
"["		{ yylval.str = yytext; print_stmt_cnt = sp; return T_LBRACKET;}
"]"		{ yylval.str = yytext; print_stmt_cnt = sp - print_stmt_cnt; return T_RBRACKET; }
"{"		{ yylval.str = yytext;return T_LCURLYBRACE;}
"}"		{ yylval.str = yytext;return T_RCURLYBRACE;}
"="		{ yylval.str = yytext;return T_ASSIGNMENT;}
"+"		{ yylval.str = yytext;return T_PLUS;}
"-"		{ yylval.str = yytext;return T_MINUS;}
"*"		{ yylval.str = yytext;return T_MUL;}
"/"		{ yylval.str = yytext;return T_DIV;}
"%"		{ yylval.str = yytext;return T_REMAINDER;}
"=="		{ yylval.str = yytext;return T_EQUAL;}
"!="		{ yylval.str = yytext;return T_NOT_EQUAL;}
"!"		{ yylval.str = yytext;return T_NOT;}
"&&"		{ yylval.str = yytext;return T_AND;}
"||"		{ yylval.str = yytext;return T_OR;}
"<"		{ yylval.str = yytext;return T_LT;}
">"		{ yylval.str = yytext;return T_GT;}
"<="		{ yylval.str = yytext;return T_LT_EQUAL;}
">="		{ yylval.str = yytext;return T_GT_EQUAL;}
"RANDOM"	{ yylval.str = yytext;return T_RANDOM;}
"$"		{ yylval.str = yytext;return T_ITERATOR;}
"OUTPUT"	{ yylval.str = yytext;return T_OUTPUT;}
";".*		{ yylval.str = yytext;return T_COMMENT;}
\".*\"		{ yylval.str = yytext;return T_STRING_LITERAL;}

{letter}({letter}|{digit})*	{ yylval.str = yytext; return T_IDENTIFIER; }
[-+]?{digit}+			{ yylval.str = yytext; return T_INTEGER; }

[ \t\n\r]	;
.		return T_ERROR;

%%

/*

int main(void)
{
	int token_number;

	printf("Start of rusper\n");
	while(0 != (token_number = yylex())) {
		printf("<%d, %s>\n", token_number, yytext);
	}

	printf("End of rusper\n");

	return 0;
}
// */

int yywrap(void)
{
	return 1;
}
