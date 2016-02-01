/*
 * crackVigenere.c
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


void crackVigenere (char *str)
{
    int *dist = NULL, i, spacingsArraySize;
    int *spacings;


    dist = (int *) malloc (strlen (str)* sizeof (int));
    if (dist == NULL)
        exit (EXIT_FAILURE);

    findSpacings (str, dist);
    spacingsArraySize = orderArray (dist, strlen (str));

    spacings = (int *) malloc (strlen (str)* sizeof (int));
    if (spacings == NULL)
        exit (EXIT_FAILURE);

    copyInNewArray (dist, spacings, spacingsArraySize);

    free (dist);

    /* Print spacings.  */
    i = 0;
    while (i < spacingsArraySize)
    {
        printf ("%d ", spacings[i]);
        i++;
    }

}
