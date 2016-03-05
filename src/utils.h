/*
 * utils.h
 *
 * Copyright (C) 2016 frnmst (Franco Masotti) <franco.masotti@live.com>
 *                                            <franco.masotti@student.unife.it>
 *
 * This file is part of fast-caesar-vigenere-cipher.
 *
 * fast-caesar-vigenere-cipher is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fast-caesar-vigenere-cipher is distributed in the hope that it will be
 * useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fast-caesar-vigenere-cipher.  If not, see
 * <http://www.gnu.org/licenses/>.
 */


#ifndef M_GLOBALDEFINES_H
#define M_GLOBALDEFINES_H
#include "globalDefines.h"
#endif

#ifndef M_STDIO_H
#define M_STDIO_H
#include <stdio.h>              /* io functions */
#endif

#ifndef M_UNISTD_H
#define M_UNISTD_H
#include <unistd.h>             /* getopt */
#endif

#ifndef M_CTYPE_H
#define M_CTYPE_H
#include <ctype.h>              /* isalpha, toupper */
#endif

#ifndef M_STRING_H
#define M_STRING_H
#include <string.h>             /* strlen, strdup */
#endif

#ifndef M_STDLIB_H
#define M_STDLIB_H
#include <stdlib.h>             /* malloc, free */
#endif


/* Function/procedure prototypes.  */
int compareIntegers( const void *a, const void *b );
void orderArray( int *array, int len );
void help( void );
void helpAndExit( void );
void checkArgc( int keySet, int *argc, int numElts );
void toUpper( char *str, char *key, int *keyIsNotAlpha );
int *reallocArray( int *array, int len );
int trimArray( int *array, int len );