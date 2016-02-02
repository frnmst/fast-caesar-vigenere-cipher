/*
 * findRepeatingSubstrings.c
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
    #include "../fcvc.h"
#endif


/* Comments TODO better.  */

/* Function that finds the distances between at least copies repeating
 * consecutive characters in the input string str. The result is saved into
 * the integer array string.  */
void findSpacings (char *str, int *spacings)
{

    /* Positional string.  */
    int strLen = strlen (str), i = 0, j = 1, k = 0;
    int ip = 0;
    /* Find repeating sequences of size of at least substrOff.  */
    const short int substrOff = 2;


    j = 1;
    while (i <= strLen)
    {
        while (j <= strLen && str[i] != str[j])
            j++;

        j += (substrOff - 1);
        ip = substrOff - 1;
        while (j <= strLen && str [i + ip] == str [j])
        {
            spacings [k] = abs (j - (i + ip));
            k++;
            j++;
            ip++;
        }
        if (j >= strLen)
        {
            i++;
            j = i + 1;
        }
    }

}

/* Since the array spacings is as long as the str and we know it will not be
 * entirely used, it must be reallocated both to avoid zeros in that array, and
 * also to free space.  */
int reallocSpacingArray (int *spacings, int len)
{

    int i = 0, spacingArraySize = 0, *tmp = NULL;


    /* Ignore zeros in the array (since spacings cannot be equal to zero).  */
    for (i = 0; i < len; i++)
        if (spacings [i] != 0)
            spacingArraySize ++;

    /* Safe realloc using a temporary pointer.  */
    if ((tmp = (int *) realloc (spacings, sizeof (int) * spacingArraySize)) == NULL)
        exit (EXIT_FAILURE);
    else
        spacings = tmp;

    return spacingArraySize;

}

