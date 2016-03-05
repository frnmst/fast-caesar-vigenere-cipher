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

    parseArgs( &argc, argv );

    exit( EXIT_SUCCESS );

}

void parseArgs( int *argc, char **argv )
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

    int i = 0, dummy;
    char *str, key[2];


    str = NULL;

    /* Copy original string so that function input is not modified.  */
    if ( ( str = strdup( inputString ) ) == NULL )
        exit( EXIT_FAILURE );

    toUpper( str, key, &dummy );
    key[0] = 'A' + 0;
    key[1] = '\0';

    /* In the first loop: str = str - 'A' which is like: str = str - 0
     * Then: str = str - 1. */
    for ( i = 0; i < ALPHABET_NUMS; i++ ) {
        /* Print the current alphabet number.  */
        fprintf( stdout, "%d\t", i + 1 );

        /* str = str - key.  */
        work( 'd', str, key );

        /* Go to the next alphabet.
         * str = str - 1.  */
        key[0] = 'A' + 1;
    }

    free( str );

    return;
}

void crackVigenere( char *cryptogram )
{

    char *str;
    int strLen = strlen( cryptogram ), arraySize;
    int *spacings, *factors;
    int i;


    str = NULL;
    spacings = NULL;
    factors = NULL;


    if ( ( str = strdup( cryptogram ) ) == NULL )
        exit( EXIT_FAILURE );

    /* The following only sets the string to toupper. MIssing controls for non
     * alpha chars.  */
    prepareStrings( str, str );

    /* Using calloc is like setting all the array to zero.  */
    if ( ( spacings = calloc( strLen, sizeof( int ) ) ) == NULL )
        exit( EXIT_FAILURE );
    findSpacings( str, spacings );
    arraySize = trimArray( spacings, strLen );

    if ( ( factors =
           calloc( arraySize * arraySize, sizeof( int ) ) ) == NULL )
        exit( EXIT_FAILURE );
    factor( factors, spacings, arraySize );
    arraySize = trimArray( factors, arraySize * arraySize );

    /* Order factors array */
    orderArray( factors, arraySize );

    /* Get max element knowing that it's in position len(factors-1) */

    /* Declare an int array of len (max_element_ */

    /* Count occurrences of same number i and save it in position i */

    /* Get the three indices with the highest value:  These three numbers
     * represent the possible key lengths.  */


    i = 0;
    while ( i < arraySize ) {
        printf( "%d ", factors[i] );
        i++;
    }


    return;

}
