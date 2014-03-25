/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DATA_TYPE = 258,
     ID = 259,
     EQUALS = 260,
     CONTINUE = 261,
     BREAK = 262,
     RETURN = 263,
     NUM = 264,
     FLOAT = 265,
     CHAR = 266,
     IF = 267,
     ELSE = 268,
     WHILE = 269,
     FOR = 270,
     PLUS = 271,
     TIMES = 272,
     LP = 273,
     RP = 274,
     LESSTHAN = 275,
     GREATERTHAN = 276,
     EQUALTO = 277,
     SEMI = 278,
     LFP = 279,
     RFP = 280,
     COMMA = 281,
     VOID = 282,
     MINUS = 283,
     DIVIDE = 284
   };
#endif
/* Tokens.  */
#define DATA_TYPE 258
#define ID 259
#define EQUALS 260
#define CONTINUE 261
#define BREAK 262
#define RETURN 263
#define NUM 264
#define FLOAT 265
#define CHAR 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define FOR 270
#define PLUS 271
#define TIMES 272
#define LP 273
#define RP 274
#define LESSTHAN 275
#define GREATERTHAN 276
#define EQUALTO 277
#define SEMI 278
#define LFP 279
#define RFP 280
#define COMMA 281
#define VOID 282
#define MINUS 283
#define DIVIDE 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


