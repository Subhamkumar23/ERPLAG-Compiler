#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#ifndef _parserdef_
#define _parserdef_
// parse table ----------------------------------------
//		t1	t2	t3	$
// Nt1
// NT2
// NT3

// pt[NT][T] <- char * 

#define NON_TERMINALS 55
#define TERMINALS 60

typedef enum 
{
    program,moduleDeclarations,moduleDeclaration,otherModules, driverModule, module,
    ret, input_plist, input_plist_dash, output_plist, output_plist_dash, dataType, range_array,
    type, moduleDef, statements, statement, ioStmt, var, var_id_num, boolConstt, whichId,
    simpleStmt, assignmentStmt, whichStmt, lvalueIDStmt, lvalueARRStmt, Index, moduleReuseStmt,
    optional, idList, idList_dash, expression, unaryOrExpr, arithmeticOrBooleanExpr, anyTerm,
    arithmeticExpr_dash, bool, arithmeticExpr, arithmeticExpr_recur, term, term_dash, factor, 
    op_plus_minus, op_mul_div, logicalOp, relationalOp, declareStmt, conditionalStmt, caseStmts,
    caseStmt, value,Default,iterativeStmt, range 
} NonTerminal;

typedef enum {
    INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, 
    USE, WITH, PARAMETERS, TRUE, FALSE, TAKES, INPUT, RETURNS, AND, OR, FOR, IN, SWITCH, CASE, BREAK,
    DEFAULT, WHILE, PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, DRIVERDEF, DRIVERENDDEF,
    COLON, RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, COMMENTMARK,ID,NUM,RNUM,ERROR,DOLLAR,EPSILON
}Terminal;

char* nonTerminalEnumToString[] = {
    "program","moduleDeclarations","moduleDeclaration","otherModules", "driverModule", "module",
    "ret", "input_plist", "input_plist_dash", "output_plist", "output_plist_dash", "dataType", "range_array",
    "type", "moduleDef", "statements", "statement", "ioStmt", "var", "var_id_num", "boolConstt", "whichId",
    "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDStmt", "lvalueARRStmt", "index", "moduleReuseStmt",
    "optional", "idList", "idList_dash", "expression", "unaryOrExpr", "arithmeticOrBooleanExpr", "anyTerm",
    "arithmeticExpr_dash", "bool", "arithmeticExpr", "arithmeticExpr_recur", "term", "term_dash", "factor", 
    "op_plus_minus", "op_mul_div", "logicalOp", "relationalOp", "declareStmt", "conditionalStmt", "caseStmts",
    "caseStmt", "value", "default", "iterativeStmt", "range"
};

char* TerminalEnumToString[] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START", "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE", "PRINT", 
	"USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS", "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK",
	"DEFAULT", "WHILE", "PLUS", "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "ENDDEF", "DRIVERDEF", "DRIVERENDDEF",
	"COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", "SQBO", "SQBC", "BO", "BC", "COMMENTMARK","ID","NUM","RNUM","ERROR","$","e"};


// Following structures are used for representing the grammar
typedef union symbol
{
    Terminal t;
    NonTerminal nt;
}Symbol;

typedef enum 
{
    
    terminal,
    nonterminal
}Type;

struct RHSNode
{
    Symbol s;
    Type type;
    struct RHSNode * next;
};

typedef struct RHSNode RHSNode;

typedef struct
{
    NonTerminal nt;
    int num_rules;
    RHSNode **rules;
}LHSNode;

typedef struct
{
    int num_non_terminals;
    LHSNode * non_terminals;
}Grammar;




// first and follow -----------------------------------

typedef struct
{
	int *firstSet;
}First;
// typedef struct First[NON_TERMINALS] First;

typedef struct
{
	int *followSet;
}Follow;
// typedef struct Follow_[NON_TERMINALS] Follow;

typedef struct
{
	First* first;
	Follow* follow;
}FirstAndFollow;


//Parse Table structs

typedef struct parse
{
	int rule_no;
}parse;

typedef struct ParseTable
{
	parse Parse[NON_TERMINALS][TERMINALS];
}ParseTable;
// g -> non_terminals [i] -> rules [ruleno] RHSNode*


//Trie--------------------------------------------------------------
typedef union
{
    char c;
    int pos;
}entry;

typedef struct node{
    entry data;
    struct node* next[28];
}node;

typedef struct trie{
    int num;
    node* children;
}trie;

// mapping table -----------------------------------------------

// typedef struct
// {
// 	char str[100];
// 	Symbol s;
// 	Type t;
// }table;

// table table[10]; // set size appropriately

// typedef union{
// 	int intValue;
// 	float fValue;
// }value;

// parse tree ------------------------------------------
// struct ParseTree
// {
// 	// display  info
// 	char lexeme[100]; // --- if not leaf node
// 	int lineno;
// 	char tokenname[25]; 
// 	int isLeafNode;
// 	Symbol ParentSymbol; // ROOT for root node
// 	Symbol NodeSymbol; // if not leaf
// 	value * val;

// 	// misc
// 	struct ParseTree *children;
// };

// typedef struct ParseTree ParseTree;
#endif