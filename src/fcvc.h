/*
 * fcvc.h
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


#ifndef M_CORE_H
#define M_CORE_H
#include "core.h"
#endif

#ifndef M_UTILS_H
#define M_UTILS_H
#include "utils.h"
#endif

#ifndef M_GUESSVIGENERE_H
#define M_GUESSVIGENERE_H
#include "guessVigenere.h"
#endif

/* C headers */
#ifndef M_STDIO_H
#define M_STDIO_H
#include <stdio.h>              /* io functions */
#endif

#ifndef M_UNISTD_H
#define M_UNISTD_H
#include <getopt.h>
#endif
/*#include <unistd.h>*/             /* getopt */


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
/* Added to adhere to ANSI standard to avoid using getopt.h */
extern int getopt( int, char *const *, const char * );
static void parseArgs( size_t *argc, char **argv );
static void crackCaesar( char *inputString );
static void crackVigenere( char *inputString );
static void prepareStrings( char *str, char *key );
