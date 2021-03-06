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
    for ( i = 0; i < spacingsArraySize; i++ ) {
        j = spacings[i];
        while ( j >= 2 ) {
            if ( ( spacings[i] % j ) == 0 ) {
                factors[k] = j;
                k++;
            }
            j--;
        }
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

    for ( i = 1; i < factorsArraySize; i++ ) {
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
    }


    return ( k + 1 );

}

/* Get significant key lengths (ordered by decreasing score).  */
int *getKeyLens( struct occurrences *occur, size_t n )
{

    int *keyLens;
    size_t i = 0;


    if ( ( keyLens =
           calloc( NUMBER_OF_FACTORS_TO_KEEP, sizeof( int ) ) ) == NULL )
        exit( EXIT_FAILURE );

    /* Keep up to NUMBER_OF_FACTORS_TO_KEEP key lengths (or factors).
     * Do not overflow with i < len.  */
    while ( i < NUMBER_OF_FACTORS_TO_KEEP && i < n ) {
        keyLens[i] = occur[n - 1 - i].factor;
        i++;
    }

    return keyLens;

}


/* Get every character, each one distant factor from each other, staring
 * from offset index.  */
static char *getSpacedSubstring( char *str, int factor, int offset )
{

    int step;
    size_t i, strLen = strlen( str );
    char *spacedStr;


    /* (strLen / factor ) + 1 is the size of spacedStr. +1 is used to avoid
     * problems concerning rounding, so in the worst case we will get a
     * useless character allocated.  */
    if ( ( spacedStr =
           calloc( ( strLen / factor ) + 1, sizeof( char ) ) ) == NULL )
        exit( EXIT_FAILURE );

    i = 0;
    step = offset;
    while ( step < ( int ) strLen ) {
        spacedStr[i] = str[step];
        i++;
        step = offset + ( factor * ( int ) i );
    }

    return spacedStr;

}


static char *getKeyLetters( int *langsIds, char alphabet )
{

    size_t i;
    char *keyLetters;


    if ( ( keyLetters = calloc( TOTAL_LANGS, sizeof( char ) ) ) == NULL )
        exit( EXIT_FAILURE );

    /* TO DO better  */
    i = 0;
    while ( langsIds[i] != -1 && i < TOTAL_LANGS ) {
        keyLetters[i] = alphabet;
        i++;
    }


    return keyLetters;

}

/* Calculate kolmogorov quantile using the formula which can be found at:
 * http://www.mathematik.uni-kl.de/~schwaar/Exercises/Tabellen/table_kolmogorov.pdf
 */


static size_t indexMaxdoubleArray( double *array, size_t n )
{

    double maximum;
    size_t i, maxInd;


    maximum = array[0];
    maxInd = 0;
    for ( i = 1; i < n - 1; i++ ) {
        if ( array[i] > maximum ) {
            maximum = array[i];
            maxInd = i;
        }
    }

    return maxInd;

}

/* Input size of both arrays is ALPHABET_NUMS.  */
static double sup( double *strScore, const double *langScore )
{

    double sup, *diffArray;
    size_t i, maxInd;


    if ( ( diffArray =
           malloc( ALPHABET_NUMS * sizeof( double ) ) ) == NULL )
        exit( EXIT_FAILURE );

    for ( i = 0; i < ALPHABET_NUMS; i++ )
        diffArray[i] = fabs( langScore[i] - strScore[i] );

    maxInd = indexMaxdoubleArray( diffArray, ALPHABET_NUMS );
    sup = diffArray[maxInd];
    free( diffArray );

    return sup;

}

/* Statistical test to know if the string score fits the score of the current
 * language.  */
static boolean kolmogorovSmirnovFrequencyTest( double *strScore,
                                               size_t langId, double tol )
{

    /* Return true if accepted.  */
    return ( sup( strScore, lF[langId].score ) <= tol );

}

/* Compare langs scores with string scores and get languages ids.  */
static int *getLangsIds( double *strScore, double tol )
{

    size_t i, j = 0;
    int *langs;


    if ( ( langs = calloc( TOTAL_LANGS + 1, sizeof( int ) ) ) == NULL )
        exit( EXIT_FAILURE );

    langs[0] = -1;
    for ( i = 0; i < TOTAL_LANGS; i++ ) {
        if ( kolmogorovSmirnovFrequencyTest( strScore, i, tol ) ) {
            langs[j] = ( int ) i;
            langs[j + 1] = -1;
            j++;
        }
    }

    return langs;

}


/* Given an input string str, get the frequency of each letter
 * (ALPHABET_NUMS) like this:
 * #ofLetterOccurrences / strLen)
 * Save the score of each letter in an array.
 * Call getFreqs(double *strScores)
 * Repeat this for all ALPHABET_NUMS alphabets.
 */
static double *getFreqs( char *str )
{

    int strLen = strlen( str ), i, j;
    double *strScores;
    char letter;


    if ( ( strScores = calloc( ALPHABET_NUMS, sizeof( double ) ) ) == NULL )
        exit( EXIT_FAILURE );

    /* Get the frequency of each letter in the string str.  */
    for ( i = 0; i < ALPHABET_NUMS; i++ ) {
        letter = 'A' + ( char ) i;
        j = 0;
        /* How many occurrences of letter letter are in the string str?  */
        while ( str[j] != '\0' ) {
            if ( str[j] == letter )
                strScores[i]++;
            j++;
        }
        strScores[i] /= strLen;
    }

    return strScores;

}

/* Caesar shift algorithm for the whole string.  */
static char *getShiftedStr( char *str, char alphabet )
{

    size_t i;
    char *shiftedStr;


    if ( ( shiftedStr = strdup( str ) ) == NULL )
        exit( EXIT_FAILURE );

    i = 0;
    while ( shiftedStr[i] != '\0' ) {
        shiftedStr[i] =
            ( ( shiftedStr[i] - alphabet +
                ALPHABET_NUMS ) % ALPHABET_NUMS ) + LETTER_OFFSET;
        i++;
    }

    return shiftedStr;

}

/*static char *getKeyElements( char *str )*/
static char **getKeyElements( char *str, double tol )
{

    size_t i;
    char alphabet;
    char *shiftedStr, **keyElements;
    int *langsIds;
    double *strScores;


    if ( ( keyElements =
           calloc( ALPHABET_NUMS, sizeof( char * ) ) ) == NULL )
        exit( EXIT_FAILURE );

    for ( i = 0; i < ALPHABET_NUMS; i++ ) {
        alphabet = 'A' + ( char ) i;

        /* Get Caesar shift for str.  */
        shiftedStr = getShiftedStr( str, alphabet );

        /* Calculate frequecy of each letter inside the string str.  */
        strScores = getFreqs( shiftedStr );

        /* To what possible languages belongs the string.  */
        langsIds = getLangsIds( strScores, tol );

        /* Get string characters.  */
        keyElements[i] = getKeyLetters( langsIds, alphabet );

        free( langsIds );
        free( strScores );
        free( shiftedStr );
    }

    return keyElements;

}

static size_t countNumOfStr (char **keyElts)
{

    size_t nonZero, i = 0;


    while (i < ALPHABET_NUMS)
    {
        if (keyElts[i][0] != '\0')
            nonZero ++;
        i++;
    }

    return nonZero;

}

void freqAnalysis( char *str, int *keyLens, size_t n )
{

    size_t i, j;
    int offset = 0;
    char *spacedStr, **keyElts;
    double tol = 0.1;


    for ( i = 0; i < n; i++ ) {

        printf( "keyLens[%d] = %d\n", ( int ) i, keyLens[i] );

        /* Get every keyLens[i] letter (starting from the jth letter) from str
         * then do frequency analysis.  */
        offset = 0;
        while ( offset < keyLens[i] && keyLens[i] != 0 ) {
            spacedStr = getSpacedSubstring( str, keyLens[i], offset );

            printf( "%s\n", spacedStr );

            tol = 0.1;
            do {
                printf ("\n\ntol = %f\n\n", tol);
                keyElts = getKeyElements( spacedStr, tol );
                tol += 0.05;
            } while ( countNumOfStr (keyElts) < 1);

            for ( j = 0; j < ALPHABET_NUMS; j++ )
                if ( keyElts[j][0] != '\0' )
                    printf( "keyElement = %s\n", keyElts[j] );

            free( keyElts );

            /* Test all keys... TODO */

            offset++;
        }
    }

    return;
}
