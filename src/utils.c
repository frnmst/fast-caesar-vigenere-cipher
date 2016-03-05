/*
 * utils.c
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


/* Main header.  */
#ifndef M_FCVC_H
#define M_FCVC_H
    #include "fcvc.h"
#endif


void checkArgc (int keySet, int *argc, int numElts)
{

    if (*argc != numElts)
        helpAndExit ();
    if (keySet != 1 && keySet != 'a')
        helpAndExit ();

}

void helpAndExit (void)
{

    fprintf (stderr, "\n");
    help ();
    exit (EXIT_FAILURE);

}

void toUpper (char *str, char *key, int *keyIsNotAlpha)
{

    int i = 0, j = 0;

    while (str[i] != '\0')
    {
        str[i] = toupper (str[i]);
        i++;
    }
    while (key[j] != '\0')
    {
        key[j] = toupper (key[j]);

        if (isalpha (key[j]) == 0)
            *keyIsNotAlpha = *keyIsNotAlpha + 1;

        j++;
    }

}

