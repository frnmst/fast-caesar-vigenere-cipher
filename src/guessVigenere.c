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


/* Function that finds the distances between at least couples repeating
 * consecutive characters in the input string str. The result is saved into
 * the integer array string.  */
int findSpacings( char *str, int *spacings )
{

    /* Positional string.  */
    int strLen = strlen( str ), i = 0, j = 1, k = 0;
    int ip = 0;
    /* Find repeating sequences of size of at least substrOff.  */
    const short int substrOff = 2;


    j = 1;
    while ( i < strLen ) {
        while ( j < strLen && str[i] != str[j] )
            j++;

        j += ( substrOff - 1 );
        ip = substrOff - 1;
        while ( j < strLen && str[i + ip] == str[j] ) {
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

    return k;

}

/* spacings is a subset of factors.  */
/* This function is awful but it can be changed with a more efficient one.  */
int factor( int *factors, int *spacings, int spacingsArraySize )
{

    int i = 0, j = 0, k = 0;


    /* j = ceil (spacings  [i] / 2) avoid iterating half the number of
     * numbers. You only need to save the first number before entering the
     * second while loop.  */
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

    return k;

}

int countOccurrences( struct occurrences *occur, int *factors,
                      int factorsArraySize )
{

    int i = 0, k = 0;


    /* assert (occur is orderered creasingly).  */
    /* assert (factorsArraySize >= 1)  */

    occur[0].factor = factors[0];
    occur[0].count = 1;

    i = 1;
    while ( i < factorsArraySize ) {
        /* Current factor == previous  */
        if ( factors[i] == factors[i - 1] )
            /* Increase occurence counter.  */
            occur[k].count++;
        else {
            /* New factor.  */
            k++;
            occur[k].factor = factors[i];
            occur[k].count = 1;
        }
        i++;
    }


    return ( k + 1 );

}

/* Get significant key lengths (ordered by decreasing score).  */
int *getKeyLens( struct occurrences *occur, int len )
{

    int *keyLens;
    int i = 0;


    keyLens = NULL;
    if ( ( keyLens = calloc( NUMBER_OF_FACTORS_TO_KEEP, sizeof( int ) ) ) == NULL )
        exit( EXIT_FAILURE );

    /* Keep up to NUMBER_OF_FACTORS_TO_KEEP key lengths (or factors).
     * Do not overflow with i < len.  */
    while ( i < NUMBER_OF_FACTORS_TO_KEEP && i < len) {
        keyLens[i] = occur[len - 1 - i].factor;
        i++;
    }

    return keyLens;

}


/* Get every factor character staring from offset index.  */
char *getSpacedSubstring( char *str, int factor, int offset )
{

    int i = 0, step, strLen = strlen( str );
    char *spacedStr;


    /* (strLen / factor ) + 1 is the size of spacedStr. +1 is used to avoid
     * problems concerning rounding, so in the worst case we will get a
     * useless character allocated.  */
    spacedStr = NULL;
    if ( ( spacedStr =
           calloc( ( strLen / factor) + 1, sizeof( char ) ) ) == NULL )
        exit( EXIT_FAILURE );

    step = offset + ( factor * i );

    while ( step < strLen ) {
        spacedStr[i] = str[step];
        i++;
        step = offset + ( factor * i );
    }

    return spacedStr;

}



/* TODO  */
/*
void getFreqs(float *strScores)
{
    while (j < TOTAL_LANGS)
    {
        while (i < ALPHABET_NUMS)
        {
            if (strScore [i] - languageFreq[j].score[i] < tol)
                i++;
            else
                break;
        }
        if (i == ALPHABET_NUMS)
???            possibleLan
    }
}
 */

/* TODO  */
/* Given an input string str, get the frequency of each letter
 * (ALPHABET_NUMS) like this:
 * #ofLetterOccurrences / strLen)
 * Save the score of each letter in an array.
 * Call getFreqs(float *strScores)
 * Repeat this for all ALPHABET_NUMS alphabets.
 */
/* void getFreqs(char *str)*/


void freqAnalysis( char *str, int *keyLens, int len )
{

    int i = 0, offset = 0;
    char *tmpStr;


    tmpStr = NULL;

    while ( i < len ) {
        /* Get every keyLens[i] letter (starting from the jth letter) from str
         * then do frequency analysis.  */
        offset = 0;
        while ( offset < keyLens[i] && keyLens[i] != 0) {
            tmpStr = getSpacedSubstring( str, keyLens[i], offset );
            printf( "%s\n", tmpStr );
/*            getFreqs (tmpStr)*/
            offset++;
        }

        i++;
    }

    return;
}
