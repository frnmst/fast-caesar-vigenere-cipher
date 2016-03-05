/*
 * guessVigenere.c
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


#ifndef M_GUESSVIGENERE_H
#define M_GUESSVIGENERE_H
#include "guessVigenere.h"
#endif


/* Function that finds the distances between at least copies repeating
 * consecutive characters in the input string str. The result is saved into
 * the integer array string.  */
void findSpacings( char *str, int *spacings )
{

    /* Positional string.  */
    int strLen = strlen( str ), i = 0, j = 1, k = 0;
    int ip = 0;
    /* Find repeating sequences of size of at least substrOff.  */
    const short int substrOff = 2;


    j = 1;
    while ( i <= strLen ) {
        while ( j <= strLen && str[i] != str[j] )
            j++;

        j += ( substrOff - 1 );
        ip = substrOff - 1;
        while ( j <= strLen && str[i + ip] == str[j] ) {
            spacings[k] = abs( j - ( i + ip ) );
            k++;
            j++;
            ip++;
        }
        if ( j >= strLen ) {
            i++;
            j = i + 1;
        }
    }

}

/* spacings is a subset of factors.  */
/* This function is awful but it can be changed with a more efficient one.  */
void factor( int *factors, int *spacings, int spacingsArraySize )
{

    int i = 0, j = 0, k = 0;


    while ( i < spacingsArraySize ) {
        j = spacings[i];
        while ( j >= 2 ) {
            if ( ( spacings[i] % j ) == 0 ) {
                factors[k] = j;
                k++;
            }
            j--;
        }
        i++;
    }

    return;

}
