/*
 * core.c
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
#ifndef M_CORE_H
#define M_CORE_H
#include "core.h"
#endif


/* Low level common crypt functions.  */

void setDefaultKey( char *key, int *keyIsNotAlpha )
{

    /* If key has no valid character, set 'A' as default key. This way the
     *  input string is not modified.  */
    if ( *keyIsNotAlpha == ( int ) strlen( key ) ) {
        key[0] = 'A';
        key[1] = '\0';
    }

}

void work( char action, char *str, char *key )
{

    int i = 0, j = 0, keyLen = strlen( key ), strLen = strlen( str );
    int setBreak = 0;


    while ( i < strLen ) {
        /* Key loop.  */
        if ( j == keyLen )
            j = 0;

        /* Non alphabetical characters of the key are ignored.  */
        while ( isalpha( key[j] ) == 0 && j < keyLen ) {
            j++;
            if ( j == keyLen )
                j = 0;
        }

        /* Non alphabetical characters of the string are ignored and printed
           as is.  */
        while ( isalpha( str[i] ) == 0 && i < strLen ) {
            fprintf( stdout, "%c", str[i] );
            i++;
            if ( i >= strLen )
                setBreak = 1;
        }

        /* Avoid string overflow if the last character is not in the isalpha
           range.  */
        if ( setBreak == 1 )
            break;

        /* Print the transformed char.  */
        fprintf( stdout, "%c",
                 *( transform( action, &str[i], &key[j] ) ) );

        i++;
        j++;

    }

    fprintf( stdout, "\n" );

}

/* Shared function used for both Caesar and Vigenère ciphers.
 * cipher 'c'
 * decipher 'd'
 */
char *transform( char action, char *letter, char *alphabet )
{

    if ( action == 'c' )
        *letter =
            ( ( *letter + *alphabet ) % ALPHABET_NUMS ) + LETTER_OFFSET;
    /* Adding ALPHABET_NUMS keeps the mod operation > 0, so it is well
     * defined.  */
    else
        *letter =
            ( ( *letter - *alphabet + ALPHABET_NUMS ) % ALPHABET_NUMS ) +
            LETTER_OFFSET;

    return letter;

}
