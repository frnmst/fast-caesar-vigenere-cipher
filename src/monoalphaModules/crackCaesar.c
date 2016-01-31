/*
 * crackCaesar.c
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

void crackCaesar (char *inputString)
{

    int i = 0, dummy;
    char *str = NULL, *alpha = NULL;


    alpha = (char *) malloc (sizeof (char) * 2);
    if (alpha == NULL)
        exit (EXIT_FAILURE);

    alpha[1] = '\0';

    for (i = 0; i < ALPHABET_NUMS; i++)
    {
        /* Copy original string.  */
        str = strdup (inputString);
        if (str == NULL)
            exit (EXIT_FAILURE);

        alpha[0] = 'A' + i; /* Go to next alphabet. */

        fprintf (stdout, "%d\t", i + 1); /* Print the alphabet number.  */

        toUpper (str, alpha, &dummy);
        work ('d', str, alpha);

        free (str);
    }

    free (alpha);

}

