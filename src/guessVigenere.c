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

static char *getSpacedSubstring( char *str, int factor, int offset );
static float *getFreqs( char *str );
static char *getShiftedStr( char *str, char alphabet );
static int *getLangsIds( float *strScore );

/* Function that finds the distances between at least couples repeating
 * consecutive characters in the input string str. The result is saved into
 * the integer array string.  */
size_t findSpacings( char *str, int *spacings )
{

    /* Positional string.  */
    size_t i = 0, j = 1, k = 0, ip = 0, strLen = strlen( str );
    /* Find repeating sequences of size of at least substrOff.  */
    const size_t substrOff = 2;


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
size_t factor( int *factors, int *spacings, size_t spacingsArraySize )
{

    size_t i = 0, k = 0;
    int j = 0;


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

size_t countOccurrences( struct occurrences * occur, int *factors,
                         size_t factorsArraySize )
{

    size_t i = 0, k = 0;


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
int *getKeyLens( struct occurrences *occur, size_t len )
{

    int *keyLens;
    size_t i = 0;


    keyLens = NULL;
    if ( ( keyLens =
           calloc( NUMBER_OF_FACTORS_TO_KEEP, sizeof( int ) ) ) == NULL )
        exit( EXIT_FAILURE );

    /* Keep up to NUMBER_OF_FACTORS_TO_KEEP key lengths (or factors).
     * Do not overflow with i < len.  */
    while ( i < NUMBER_OF_FACTORS_TO_KEEP && i < len ) {
        keyLens[i] = occur[len - 1 - i].factor;
        i++;
    }

    return keyLens;

}


/* Get every factor character staring from offset index.  */
static char *getSpacedSubstring( char *str, int factor, int offset )
{

    int i = 0, step;
    size_t strLen = strlen( str );
    char *spacedStr;


    /* (strLen / factor ) + 1 is the size of spacedStr. +1 is used to avoid
     * problems concerning rounding, so in the worst case we will get a
     * useless character allocated.  */
    spacedStr = NULL;
    if ( ( spacedStr =
           calloc( ( strLen / factor ) + 1, sizeof( char ) ) ) == NULL )
        exit( EXIT_FAILURE );

    step = offset + ( factor * i );

    while ( step < ( int ) strLen ) {
        spacedStr[i] = str[step];
        i++;
        step = offset + ( factor * i );
    }

    return spacedStr;

}


/* Compare langs and get languages.  */
static int *getLangsIds( float *strScore )
{

    size_t i = 0, j = 0, k = 0;
    int *langs;


    langs = NULL;

    if ( ( langs = calloc( TOTAL_LANGS + 2, sizeof( int ) ) ) == NULL )
        exit( EXIT_FAILURE );


    while ( i < TOTAL_LANGS ) {
        j = 0;
        while ( j < ALPHABET_NUMS
                && fabsf( strScore[j] - lF[i].score[j] ) < FREQ_TOL )
            j++;
        /* If every letter is inside tolerance, save it into langs.  */
        if ( j == ALPHABET_NUMS ) {
            langs[k] = ( int ) i + 1;
            k++;
        }
        i++;
    }

    return langs;

}


/* Given an input string str, get the frequency of each letter
 * (ALPHABET_NUMS) like this:
 * #ofLetterOccurrences / strLen)
 * Save the score of each letter in an array.
 * Call getFreqs(float *strScores)
 * Repeat this for all ALPHABET_NUMS alphabets.
 */
static float *getFreqs( char *str )
{

    int strLen = strlen( str ), i = 0, j = 0;
    float *strScores;
    char letter;


    strScores = NULL;
    if ( ( strScores = calloc( ALPHABET_NUMS, sizeof( float ) ) ) == NULL )
        exit( EXIT_FAILURE );

    /* Get the frequency of each letter in the string str .  */
    while ( i < ALPHABET_NUMS ) {
        letter = 'A' + ( char ) i;
        j = 0;
        while ( str[j] != '\0' ) {
            if ( str[j] == letter )
                strScores[i]++;
            j++;
        }
        strScores[i] /= strLen;
        i++;
    }

    return strScores;

}

/* Caesar shift algorithm for the whole string.  */
static char *getShiftedStr( char *str, char alphabet )
{

    size_t i = 0;
    char *tmpStr;


    tmpStr = NULL;
    if ( ( tmpStr = strdup( str ) ) == NULL )
        exit( EXIT_FAILURE );

    while ( tmpStr[i] != '\0' ) {
        tmpStr[i] =
            ( ( tmpStr[i] - alphabet + ALPHABET_NUMS ) % ALPHABET_NUMS ) +
            LETTER_OFFSET;
        i++;
    }

    return tmpStr;

}

static void callGetFreqs( char *str )
{

    size_t i = 0;
    char shift;
    char *tmpStr;
    int *langsIds;
    float *strScores;

    size_t j = 0;


    tmpStr = NULL;
    langsIds = NULL;

    while ( i < ALPHABET_NUMS ) {
        shift = 'A' + ( char ) i;
        tmpStr = getShiftedStr( str, shift );
        strScores = getFreqs( tmpStr );
        langsIds = getLangsIds( strScores );

        j = 0;
        while ( langsIds[j] != 0 ) {
            /* Save letter offset + i somewhere and return all of them as char*.  */
            printf( "lang = %s, key = %c\n", lF[langsIds[j - 1]].language,
                    ( char ) LETTER_OFFSET + ( char ) i );
            j++;
        }

        free( langsIds );
        free( strScores );
        free( tmpStr );
        i++;
    }

/*        for ( j = 0; j < 26; j++ )
            printf( "%d %c = %f\n", ( int ) i, ( char ) j + 65,
                    strScoresPtr[i][j] );
*/

    return;

}

void freqAnalysis( char *str, int *keyLens, size_t len )
{

    size_t i = 0;
    int offset = 0;
    char *tmpStr;


    tmpStr = NULL;

    while ( i < len ) {
        /* Get every keyLens[i] letter (starting from the jth letter) from str
         * then do frequency analysis.  */
        offset = 0;
        while ( offset < keyLens[i] && keyLens[i] != 0 ) {
            tmpStr = getSpacedSubstring( str, keyLens[i], offset );
            printf( "%s\n", tmpStr );
            callGetFreqs( tmpStr );
            /* Test all keys... TODO */

            offset++;
        }

        i++;
    }

    return;
}
