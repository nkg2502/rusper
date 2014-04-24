%{
/*
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


%}

%union {
	int integer;
	char *str;
}

%token T_EOF
%token T_ERROR
%token T_VAR
%token T_IF
%token T_LPAREN
%token T_RPAREN
%token T_COLON
%token T_DCOLON
%token T_BREAK
%token T_FOR
%token T_SEPARATOR
%token T_DO
%token T_LBRACKET
%token T_RBRACKET
%token T_LCURLYBRACE
%token T_RCURLYBRACE
%token T_ASSIGNMENT
%token T_PLUS
%token T_MINUS
%token T_MUL
%token T_DIV
%token T_REMAINDER
%token T_EQUAL
%token T_NOT_EQUAL
%token T_NOT
%token T_AND
%token T_OR
%token T_LT
%token T_GT
%token T_LT_EQUAL
%token T_GT_EQUAL
%token T_RANDOM
%token T_ITERATOR
%token T_OUTPUT
%token T_IDENTIFIER
%token T_INTEGER
%token T_COMMENT
%token T_STRING_LITERAL

%%
program:	file
		;

file:		statement_list
    		{
			AST_node *iter;
			int i;

			iter = AST_root = AST_stack[0];
			for(i = 1; i < sp; ++i) {
				iter->sibling = AST_stack[i];
				iter = iter->sibling;
			}
		}
    		;

statement_list:	statement
	      	| statement statement_list
		;

compound_statement:	statement 
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
		  	| statement compound_statement
			;

statement:	declaration_statement
	 	{
			// build tree
			AST_node *ptr;

			ptr = build_tree(DECLARATION_STATEMENT);
			ptr->child = AST_stack[--sp];

			// push
			AST_stack[sp++] = ptr;
		}
		| expression_statement
	 	| selection_statement
		{
			// build tree
			AST_node *ptr;

			ptr = build_tree(SELECTION_STATEMENT);
			ptr->child = AST_stack[--sp];

			// push
			AST_stack[sp++] = ptr;

		}
		| break_statement
		{
			// build tree
			AST_node *ptr;

			ptr = build_tree(BREAK_STATEMENT);
			ptr->child = AST_stack[--sp];

			// push
			AST_stack[sp++] = ptr;

		}
		| for_statement
		{
			// build tree
			AST_node *ptr;

			ptr = build_tree(FOR_STATEMENT);
			ptr->child = AST_stack[--sp];

			// push
			AST_stack[sp++] = ptr;

		}
		| do_statement
	 	{
			// build tree
			AST_node *ptr;

			ptr = build_tree(DO_STATEMENT);
			ptr->child = AST_stack[--sp];

			// push
			AST_stack[sp++] = ptr;
		}
		| print_statement
		{
			// build tree
			AST_node *ptr;

			ptr = build_tree(PRINT_STATEMENT);
			ptr->child = AST_stack[--sp];

			// push
			AST_stack[sp++] = ptr;

		}
		| output_statement
		{
			// build tree
			AST_node *ptr;

			ptr = build_tree(OUTPUT_STATEMENT);
			ptr->child = AST_stack[--sp];

			// push
			AST_stack[sp++] = ptr;

		}
		| comment_statement
		;

declaration_statement:	T_VAR identifier 
			{
				// build sibling
				AST_node *ptr;

				ptr = build_node(T_VAR, "VAR");
				ptr->sibling = AST_stack[--sp];

				AST_stack[sp++] = ptr;
			}
		     	;

expression_statement:	expression
			;

selection_statement:	T_IF T_LPAREN expression T_RPAREN T_DCOLON compound_statement T_COLON 
		   	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_IF, "IF");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
		   	;

break_statement:	T_BREAK 
	       		{
				AST_stack[sp++] = build_node(T_BREAK, "BREAK");
			}
	       		;

for_statement:		T_FOR T_LPAREN integer T_SEPARATOR integer T_RPAREN T_DCOLON compound_statement T_COLON 
	     		{
				// build sibling
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
	     		;

do_statement:		T_DO T_LPAREN integer T_RPAREN T_DCOLON compound_statement T_COLON 
			{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_DO, "DO");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
	    		;

print_statement:	T_LBRACKET print_expression_list T_RBRACKET 
	       		{
				// build sibling
				AST_node *ptr;

				ptr = build_node(T_LBRACKET, "PRINT");
				ptr->sibling = AST_stack[--sp];

				AST_stack[sp++] = ptr;
			}
			;

print_expression_list:	print_expression  
	  		| print_expression print_expression_list 
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
			;

print_expression:	string_literal  
     			| T_LCURLYBRACE expression T_RCURLYBRACE 
			;

output_statement:	T_OUTPUT T_LPAREN string_literal T_RPAREN 
			{
				// build sibling
				AST_node *ptr;

				ptr = build_node(T_OUTPUT, "OUTPUT");
				ptr->sibling = AST_stack[--sp];

				AST_stack[sp++] = ptr;
			}
			;

comment_statement:	T_COMMENT
		 	;

expression:		assignment_expression
	  		{
				// build tree
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				// push
				AST_stack[sp++] = ptr;
			}
	  		| arithmetic_expression
			{
				// build tree
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				// push
				AST_stack[sp++] = ptr;
			}
			| equality_expression
			{
				// build tree
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				// push
				AST_stack[sp++] = ptr;
			}
			| relational_expression
			{
				// build tree
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				// push
				AST_stack[sp++] = ptr;
			}
			| logical_expression
			{
				// build tree
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				// push
				AST_stack[sp++] = ptr;
			}
			| random_expression
			{
				// build tree
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				// push
				AST_stack[sp++] = ptr;
			}
			| iterator_expression
			{
				// build tree
				AST_node *ptr;
	
				ptr = build_tree(EXPRESSION);
				ptr->child = AST_stack[--sp];
	
				// push
				AST_stack[sp++] = ptr;
			}
			| integer
			| identifier
			;

assignment_expression:	T_ASSIGNMENT T_LPAREN lvalue T_SEPARATOR expression T_RPAREN 
		     	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_ASSIGNMENT, "=");
				
				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
		     	;

arithmetic_expression:	T_PLUS T_LPAREN expression T_SEPARATOR expression T_RPAREN 
		     	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_PLUS, "+");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
		     	| T_MINUS T_LPAREN expression T_SEPARATOR expression T_RPAREN 
		     	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_MINUS, "-");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
			| T_MUL T_LPAREN expression T_SEPARATOR expression T_RPAREN 
		     	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_MUL, "*");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
			| T_DIV T_LPAREN expression T_SEPARATOR expression T_RPAREN 
		     	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_DIV, "/");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
			| T_REMAINDER T_LPAREN expression T_SEPARATOR expression T_RPAREN 
		     	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_REMAINDER, "%");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;

			}
		     	;

equality_expression:	T_EQUAL T_LPAREN expression T_SEPARATOR expression T_RPAREN 
		   	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_EQUAL, "==");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
			| T_NOT_EQUAL T_LPAREN expression T_SEPARATOR expression T_RPAREN 
			{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_NOT_EQUAL, "!=");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
			;

relational_expression:	T_NOT T_LPAREN expression T_RPAREN 
		     	{
				// build sibling
				AST_node *ptr;

				ptr = build_node(T_NOT, "!");

				ptr->sibling = AST_stack[--sp];

				AST_stack[sp++] = ptr;

			}
		     	| T_AND T_LPAREN expression T_SEPARATOR expression T_RPAREN 
			{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_AND, "&&");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
		     	| T_OR T_LPAREN expression T_SEPARATOR expression T_RPAREN 
			{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_OR, "||");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
			;

logical_expression:	T_LT T_LPAREN expression T_SEPARATOR expression T_RPAREN 
		  	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_LT, "<");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
		     	| T_GT T_LPAREN expression T_SEPARATOR expression T_RPAREN 
			{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_GT, ">");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
		     	| T_LT_EQUAL T_LPAREN expression T_SEPARATOR expression T_RPAREN 
			{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_LT, "<=");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
		     	| T_GT_EQUAL T_LPAREN expression T_SEPARATOR expression T_RPAREN 
			{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_LT, ">=");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
			;

random_expression:	T_RANDOM T_LPAREN integer T_SEPARATOR integer T_RPAREN 
		    	{
				// build sibling
				AST_node *ptr;
				AST_node *param;

				ptr = build_node(T_RANDOM, "RANDOM");

				param = AST_stack[--sp];
				ptr->sibling = AST_stack[--sp];
				ptr->sibling->sibling = param;

				AST_stack[sp++] = ptr;
			}
		 	;

iterator_expression:	T_ITERATOR { AST_stack[sp++] = build_node(T_ITERATOR, yylval.str); }
		   	;

lvalue:			identifier 
      			;

string_literal:		T_STRING_LITERAL { AST_stack[sp++] = build_node(T_STRING_LITERAL, yylval.str); }
	      		;

integer:		T_INTEGER { AST_stack[sp++] = build_node(T_INTEGER, yylval.str); }
       			;

identifier:		T_IDENTIFIER { AST_stack[sp++] = build_node(T_IDENTIFIER, yylval.str); }
	 		;

%%

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
