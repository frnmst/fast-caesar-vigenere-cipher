/*
 * fcvc.c
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


/*
 *
 * Implementation file.
 * A very simple yet powerful implementation of Vigenère's and Ceaser's cipher.
 * This program is able to cipher and decipher Caesar's and Vigenere's ciphers
 * as well as to crack Caesar's cipher (by testing all 26 alphabets) very
 * quickly. This has been possible by passing values by reference to functions
 * (i.e. memory addresses not values). Input could be any arbitrary length string.
 * If the string contains spaces then it must be surrounded by double quotations
 * : ' " '.
 * The key as well as the string characters must be 7 bit ASCII. The only
 * working range is: [a-z,A-Z]. Characters included in this range are
 * guaranteed to work. The space character (ASCII 32) for example will not be
 * translated along with the working range characters. It will just stay there.
 * The key has another condition: it must not contain spaces.
 */
/* The following are high level functions that call the low level ones.  */


/* Main header.  */
#ifndef M_FCVC_H
#define M_FCVC_H
#include "fcvc.h"
#endif


int main( int argc, char **argv )
{

    /*
     * Input: switch
     *              -a = try all alphabets
     *              -c = crypt, requires -k
     *              -d = decrypt, requires -k
     *              -h = help
     *              -k = key, used by -c and -d
     *      -v = decipher a vigenere input text.
     *
     */
    parseArgs( (size_t *) &argc, argv );

    exit( EXIT_SUCCESS );

}

void parseArgs( size_t *argc, char **argv )
{

    int c, keySet = 0;
    char *key = NULL;
    extern char *optarg;
    extern int optind, opterr, optopt;
    const char *optionsString = "a:c:d:hk:v:";


    /* Input argument parsing.  */
    while ( ( c =
              getopt( *argc, ( char *const * ) argv,
                      optionsString ) ) != -1 ) {

        switch ( c ) {
        /* 3 or 5 arguments are possible.  */
        case 'a':
            checkArgc( 'a', argc, 3 );
            crackCaesar( optarg );
            break;

        case 'c':
            checkArgc( keySet, argc, 5 );
            prepareStrings( optarg, key );
            work( 'c', optarg, key );
            free( key );
            break;

        case 'd':
            checkArgc( keySet, argc, 5 );
            prepareStrings( optarg, key );
            work( 'd', optarg, key );
            free( key );
            break;

        case 'h':
            help(  );
            break;

        case 'k':
            keySet = 1;
            checkArgc( keySet, argc, 5 );
            key = strdup( optarg );
            if ( key == NULL )
                exit( EXIT_FAILURE );
            break;

        case 'v':
            fprintf( stderr, "Unimplemented\n" );
            crackVigenere( optarg );
            exit( EXIT_FAILURE );
            break;

        default:
            helpAndExit(  );
            break;
        }
    }

    /* If no argument has been given, exit with help.  */
    if ( optind == 1 )
        helpAndExit(  );

    return;

}

void prepareStrings( char *str, char *key )
{
    int p = 0, *keyIsNotAlpha = &p;

    toUpper( str, key, keyIsNotAlpha );
    setDefaultKey( key, keyIsNotAlpha );

}

void crackCaesar( char *inputString )
{

    size_t i = 0;
    int dummy;
    char *str, key[2];


    str = NULL;

    /* Copy original string so that function input is not modified.  */
    if ( ( str = strdup( inputString ) ) == NULL )
        exit( EXIT_FAILURE );

    toUpper( str, key, &dummy );
    key[0] = 'A' + (char) 0;
    key[1] = '\0';

    /* In the first loop: str = str - 'A' which is like: str = str - 0
     * Then: str = str - 1. */
    for ( i = 0; i < ALPHABET_NUMS; i++ ) {
        /* Print the current alphabet number.  */
        fprintf( stdout, "%d\t", (int) i + 1 );

        /* str = str - key.  */
        work( 'd', str, key );

        /* Go to the next alphabet.
         * str = str - 1.  */
        key[0] = 'A' + (char) 1;
    }

    free( str );

    return;
}

void crackVigenere( char *cryptogram )
{

    char *str;
    size_t strLen = strlen( cryptogram ), size = 0;
    int *spacings, *factors, *keyLens;
    struct occurrences *occur;

    int i;


    str = NULL;
    spacings = NULL;
    factors = NULL;
    keyLens = NULL;


    if ( ( str = strdup( cryptogram ) ) == NULL )
        exit( EXIT_FAILURE );

    /* The following only sets the string to toupper. MIssing controls for non
     * alpha chars.  */
/*    prepareStrings( str, str );*/

    /* In the worst case the space complexity for spacings =
     *  O(strLen * strLen).  */
    if ( ( spacings = calloc( strLen * strLen, sizeof( int ) ) ) == NULL )
        exit( EXIT_FAILURE );
    size = findSpacings( str, spacings );
    trimArray( spacings, size );

    if ( ( factors = calloc( size * size, sizeof( int ) ) ) == NULL )
        exit( EXIT_FAILURE );
    size = factor( factors, spacings, size );
    trimArray( factors, size );

    free( spacings );

    /* Order factors array */
    orderArray( factors, size );

    /* Maybe the following is better implemented with lists...  */
    /* Get max_element knowing that it's in position len(factors-1).  */
    /* Declare an struct with max_element elements.  */
    if ( ( occur =
           calloc( factors[size - 1],
                   sizeof( struct occurrences ) ) ) == NULL )
        exit( EXIT_FAILURE );


    /* Count occurrences of same number i and save it in position i */
    size = countOccurrences( occur, factors, size );

    free( factors );

    orderStruct( occur, size );

    /* Get the three indices with the highest value:  These three numbers
     * represent the possible key lengths.  */
    keyLens = getKeyLens( occur, size );

    free( occur );

    freqAnalysis( str, keyLens, NUMBER_OF_FACTORS_TO_KEEP );

    i = 0;
    while ( i < NUMBER_OF_FACTORS_TO_KEEP ) {
        printf( "%d ", keyLens[i] );
        i++;
    }

    free ( keyLens );

    return;

}
