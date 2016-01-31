/*
 * utils.c
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
    #include "fcvc.h"
#endif


void checkArgc (int keySet, int *argc, int numElts)
{

    if (*argc != numElts)
        helpAndExit ();
    if (keySet != 1 && keySet != 'a')
        helpAndExit ();

}

void helpAndExit (void)
{

    fprintf (stderr, "\n");
    help ();
    exit (EXIT_FAILURE);

}

/* Print the help function.  */
void help (void)
{

    fprintf (stderr,
"Usage: %s {OPTION1} [OPTION2]\n"
"An ANSI C, fast and efficient implementation of Caesar and Vigenere cipher.\n"
"\n"
"Only one or two options are permitted.\n"
"\tfcvc {-a,-v} \"INPUT STRING\"\n"
"\tfcvc -k KEY {-c,-d} \"INPUT STRING\"\n"
"\n"
"\t-a\tTry all 26 alphabets for the INPUT STRING.\n"
"\t-c\tEncipher INPUT STRING.\n"
"\t-d\tDecipher INPUT STRING.\n"
"\t-h\tPrint this help.\n"
"\t-k\tUse KEY to encipher or decipher INPUT STRING.\n"
"\t-v\tDecipher Vigenere INPUT STRING.\n"
"\n", PRG_NAME);
    fprintf (stderr,
"Exit value:\n"
"\t0\tno error occurred,\n"
"\t!= 0\tsome error occurred.\n"
"\n"
"Report bugs to: franco.masotti@student.unife.it or franco.masotti@live.com\n"
"Full documentation at: <https://github.com/frnmst/%s>\n"
"or available locally via: %s -h\n"
"\n", REPO_NAME, PRG_NAME);
    fprintf (stderr,
"%s  Copyright © 2016  frnmst (Franco Masotti)\n"
"This program comes with ABSOLUTELY NO WARRANTY; for details see\n"
"'LICENSE' file or <https://www.gnu.org/licenses/gpl-3.0.en.html>\n"
"This is free software, and you are welcome to redistribute it\n"
"under certain conditions; see 'LICENSE' file or\n"
"<https://www.gnu.org/licenses/gpl-3.0.en.html> for details.\n"
, REPO_NAME);

}

void toUpper (char *str, char *key, int *keyIsNotAlpha)
{

    int i = 0, j = 0;

    while (str[i] != '\0')
    {
        str[i] = toupper (str[i]);
        i++;
    }
    while (key[j] != '\0')
    {
        key[j] = toupper (key[j]);

        if (isalpha (key[j]) == 0)
            *keyIsNotAlpha = *keyIsNotAlpha + 1;

        j++;
    }

}

void prepareStrings (char action, char *str, char *key)
{
    int p = 0, *keyIsNotAlpha = &p;

    toUpper (str, key, keyIsNotAlpha);
    setDefaultKey (key, keyIsNotAlpha);
    work (action, str, key);

}

