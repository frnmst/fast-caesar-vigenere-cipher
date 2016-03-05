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


int main (int argc, char **argv)
{

	/*
	 * Input: switch
	 *		-a = try all alphabets
	 *		-c = crypt, requires -k
	 *		-d = decrypt, requires -k
	 *		-h = help
	 *		-k = key, used by -c and -d
     *      -v = decipher a vigenere input text.
     *
	 */

	parseArgs (&argc, argv);

	exit (EXIT_SUCCESS);

}

void parseArgs (int *argc, char **argv)
{

    int c, keySet = 0;
    char *key = NULL;
    extern char *optarg;
    extern int optind, opterr, optopt;
    const char *optionsString = "a:c:d:hk:v:";


    /* Input argument parsing.  */
    while ((c = getopt (*argc, (char * const *) argv, optionsString)) != -1)
    {

        switch (c)
        {
			case 'a':
				checkArgc ('a', argc, 3);
				crackCaesar (optarg);
				break;

			case 'c':
				checkArgc (keySet, argc, 5);
                prepareStrings ('c', optarg, key);
                free (key);
				break;

			case 'd':
				checkArgc (keySet, argc, 5);
                prepareStrings ('d', optarg, key);
                free (key);
				break;

			case 'h':
				help ();
				break;

			case 'k':
                keySet = 1;
				checkArgc (keySet, argc, 5);
				key = strdup (optarg);
                if (key == NULL)
                    exit (EXIT_FAILURE);
				break;

            case 'v':
                fprintf (stderr, "Unimplemented\n");
                crackVigenere (optarg);
                exit (EXIT_FAILURE);
                break;

			default:
                helpAndExit ();
				break;
		}
	}

    /* If no argument has been given, exit with help.  */
    if (optind == 1)
        helpAndExit ();

    return;

}

void prepareStrings (char action, char *str, char *key)
{
    int p = 0, *keyIsNotAlpha = &p;

    toUpper (str, key, keyIsNotAlpha);
    setDefaultKey (key, keyIsNotAlpha);
    work (action, str, key);

}

void crackCaesar (char *inputString)
{

    int i = 0, dummy;
    char *str, key[2];


    str = NULL;

    /* Copy original string so that function input is not modified.  */
    if ((str = strdup (inputString)) == NULL)
        exit (EXIT_FAILURE);

    toUpper (str, key, &dummy);
    key[0] = 'A' + 0;
    key[1] = '\0';

    /* In the first loop: str = str - 'A' which is like: str = str - 0
     * Then: str = str - 1. */
    for (i = 0; i < ALPHABET_NUMS; i++)
    {
        /* Print the current alphabet number.  */
        fprintf (stdout, "%d\t", i + 1);

        /* str = str - key.  */
        work ('d', str, key);

        /* Go to the next alphabet.
         * str = str - 1.  */
        key[0] = 'A' + 1;
    }

    free (str);

    return;
}

void crackVigenere (char *str)
{
    int strLen = strlen (str), spacingsArraySize;
    int *spacings;
    int i;


    spacings = NULL;

    /* Transform input string in an alpha(toupper(string)).  */
    /*TODO.  */

    /* Using calloc is like setting all the array to zero.  */
    if ((spacings = (int *) calloc (strLen, strLen * sizeof (int))) == NULL)
        exit (EXIT_FAILURE);

    findSpacings (str, spacings);
    spacingsArraySize = reallocSpacingArray (spacings, strLen);

    /* Print spacings.  */
    i = 0;
    while (i < spacingsArraySize)
    {
        printf ("%d ", spacings[i]);
        i++;
    }

}

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

    return;

}

