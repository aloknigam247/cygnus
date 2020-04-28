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

#ifndef YY_LANG_C_BISON_H_INCLUDED
# define YY_LANG_C_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef LANGDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define LANGDEBUG 1
#  else
#   define LANGDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define LANGDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined LANGDEBUG */
#if LANGDEBUG
extern int langdebug;
#endif

/* Token type.  */
#ifndef LANGTOKENTYPE
# define LANGTOKENTYPE
  enum langtokentype
  {
    TYPE = 258
  };
#endif

/* Value type.  */
#if ! defined LANGSTYPE && ! defined LANGSTYPE_IS_DECLARED
typedef int LANGSTYPE;
# define LANGSTYPE_IS_TRIVIAL 1
# define LANGSTYPE_IS_DECLARED 1
#endif


extern LANGSTYPE langlval;

int langparse (void);
/* "%code provides" blocks.  */
#line 3 "c.y" /* yacc.c:1909  */

  #define YY_DECL int langlex ()
  YY_DECL;

#line 78 "c-bison.h" /* yacc.c:1909  */

#endif /* !YY_LANG_C_BISON_H_INCLUDED  */
