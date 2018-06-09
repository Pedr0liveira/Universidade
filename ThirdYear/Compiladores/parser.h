/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    FLOATER = 259,
    LSTRING = 260,
    ID = 261,
    BOOLLIT = 262,
    ASP = 263,
    LCBRACE = 264,
    RCBRACE = 265,
    LSBRACE = 266,
    RSBRACE = 267,
    LPAR = 268,
    RPAR = 269,
    DOT = 270,
    DPOINTS = 271,
    INT = 272,
    FLOAT = 273,
    STRING = 274,
    BOOL = 275,
    VOID = 276,
    DEFINE = 277,
    IF = 278,
    THEN = 279,
    ELSE = 280,
    WHILE = 281,
    DO = 282,
    RETURN = 283,
    BREAK = 284,
    NEXT = 285,
    ASSIGN = 286,
    PRINT = 287,
    INPUT = 288,
    SEMI = 289,
    COMMA = 290,
    OR = 291,
    AND = 292,
    NOT = 293,
    EQUALS = 294,
    LESS = 295,
    BIGGER = 296,
    LESSEQU = 297,
    BIGGEREQU = 298,
    NOTEQU = 299,
    ADD = 300,
    SUB = 301,
    DIV = 302,
    MUL = 303,
    MOD = 304,
    POW = 305
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define FLOATER 259
#define LSTRING 260
#define ID 261
#define BOOLLIT 262
#define ASP 263
#define LCBRACE 264
#define RCBRACE 265
#define LSBRACE 266
#define RSBRACE 267
#define LPAR 268
#define RPAR 269
#define DOT 270
#define DPOINTS 271
#define INT 272
#define FLOAT 273
#define STRING 274
#define BOOL 275
#define VOID 276
#define DEFINE 277
#define IF 278
#define THEN 279
#define ELSE 280
#define WHILE 281
#define DO 282
#define RETURN 283
#define BREAK 284
#define NEXT 285
#define ASSIGN 286
#define PRINT 287
#define INPUT 288
#define SEMI 289
#define COMMA 290
#define OR 291
#define AND 292
#define NOT 293
#define EQUALS 294
#define LESS 295
#define BIGGER 296
#define LESSEQU 297
#define BIGGEREQU 298
#define NOTEQU 299
#define ADD 300
#define SUB 301
#define DIV 302
#define MUL 303
#define MOD 304
#define POW 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 10 "yalang.y" /* yacc.c:1909  */

	
	int integer;
	float floater;
	char *string;
	char *id;
	int boolean;

	struct decls *decls;
	struct decl *decl;
	struct type *type;
	struct ids *ids;
	struct stms *stms;
	struct argdefs *argdefs;
	struct argdef *argdef;
	struct exp *exp;

#line 172 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
