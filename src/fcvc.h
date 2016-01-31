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



/* C headers */
#ifndef M_STDIO_H
#define M_STDIO_H
	#include <stdio.h> /* io functions */
#endif

#ifndef M_UNISTD_H
#define M_UNISTD_H
	#include <unistd.h> /* getopt */
#endif

#ifndef M_CTYPE_H
#define M_CTYPE_H
	#include <ctype.h> /* isalpha, toupper */
#endif

#ifndef M_STRING_H
#define M_STRING_H
	#include <string.h> /* strlen, strdup */
#endif

#ifndef M_STDLIB_H
#define M_STDLIB_H
	#include <stdlib.h> /* malloc, free */
#endif

/* Program constants.  */
#define PRG_NAME "fcvc"
#define REPO_NAME "fast-caesar-vigenere-cipher"
#define G 2

/* Numeric constants.  */
#define ALPHABET_NUMS 26
#define LETTER_OFFSET 65

/* Function/procedure prototypes.  */

/* Added to adhere to ANSI standard to avoid using getopt.h */
extern int getopt (int, char * const *, const char *);
void parseArgs (int *argc, char **argv);
void helpAndExit (void);
void help (void);
void checkArgc (int keySet, int *argc, int numElts);
void crackCaesar (char *inputString);
void crackvigenere (char *inputString);
void prepareStrings (char action, char *str, char *key);
void toUpper (char *str, char *key, int *keyIsNotAlpha);
void setDefaultKey (char *key, int *keyIsNotAlpha);
void work (char action, char *str, char *key);
char *transform (char *action, char *letter, char *alphabet);

