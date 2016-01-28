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
 * working range is: [a-z,A-Z]. Characters not included in this range are
 * guaranteed to work or they will be ignored. The space character (ASCII 32)
 * for example will not be translated along with the working range characters.
 * It will just stay there.
 * The key has another condition: it must not contain spaces.
 */

/* Main header.  */
#include "fcvc.h"


int main (int argc, char **argv)
{

	checkArgc (3, &argc, 5);

	/*
	 * Input: switch
	 *		-a = try all alphabets
	 *		-c = crypt, requires -k
	 *		-d = decrypt, requires -k
	 *		-h = help
	 *		-k = key, used by -c and -d
     *      -v = decipher a vigenere input text.
	 * 	  string
	 *
	 */

	parseArgs (&argc, argv);

	exit (EXIT_SUCCESS);

}

void parseArgs (int *argc, char **argv)
{

    int c, needsToCallWork = 0;
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
				checkArgc (3, argc, 3);
				crackCaesar (optarg);
				break;

			case 'c':
				checkArgc ('l', argc, 5);
				needsToCallWork = callWork ('c', optarg, key);
				break;

			case 'd':
				checkArgc ('l', argc, 5);
				needsToCallWork = callWork ('d', optarg, key);
				break;

			case 'h':
				help ();
				break;

			case 'k':
				checkArgc ('l', argc, 5);
				key = strdup (optarg);
				/* Check for return.  */
				break;

            case 'v':
                fprintf (stderr, "Unimplemented\n");
                exit (EXIT_FAILURE);
                break;
			default:
				help ();
				exit (EXIT_FAILURE);
				break;

		}
	}

	/* If -k switch is entered before -c or -d switch:  */
	if (needsToCallWork == 1)
		work (argv[1][1], argv[2], argv[4]);

}

void checkArgc (char action, int *argc, int numElts)
{

	if (action == 'l') /* less than */
	{
		if (*argc < numElts)
		{
			help ();
			exit (EXIT_FAILURE);
		}
	}
	else if (action == 'g') /* greater than */
	{
		if (*argc > numElts)
		{
			help ();
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		/* action is used as another numElts */
		if (*argc < (int) action || *argc > numElts)
		{
			help ();
			exit (EXIT_FAILURE);
		}
	}

}

/* print help function */
void help (void)
{

	fprintf (stdout,
"Usage: %s {OPTION1} [OPTION2]\n"
"An ANSI C, fast and efficient implementation of Caesar and Vigenere cipher.\n"
"\n"
"Only one or two options are permitted.\n"
"\t{-a,-v} \"INPUT STRING\"\n"
"\t-k KEY {-c,-d} \"INPUT STRING\"\n"
"\n"
"\t-a\tTry all 26 alphabets for the INPUT STRING.\n"
"\t-c\tEncipher INPUT STRING.\n"
"\t-d\tDecipher INPUT STRING.\n"
"\t-h\tPrint this help.\n"
"\t-k\tUse KEY to encipher or decipher INPUT STRING.\n"
"\t-v\tDecipher Vigenere INPUT STRING.\n"
"\n", PRG_NAME);
    fprintf (stdout,
"Exit value:\n"
"\t0\tno error occurred,\n"
"\t!= 0\tsome error occurred.\n"
"\n"
"Report bugs to: franco.masotti@student.unife.it or franco.masotti@live.com\n"
"Full documentation at: <https://github.com/frnmst/%s>\n"
"or available locally via: %s -h\n"
"\n", REPO_NAME, PRG_NAME);
    fprintf (stdout,
"%s  Copyright © 2016  frnmst (Franco Masotti)\n"
"This program comes with ABSOLUTELY NO WARRANTY; for details see\n"
"'LICENSE' file or <https://www.gnu.org/licenses/gpl-3.0.en.html>\n"
"This is free software, and you are welcome to redistribute it\n"
"under certain conditions; see 'LICENSE' file or\n"
"<https://www.gnu.org/licenses/gpl-3.0.en.html> for details.\n"
, REPO_NAME);

}

void crackCaesar (char *inputString)
{

	int i = 0;
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

		work ('d', str, alpha);

		free (str);
	}

	free (alpha);

}

int callWork (char action, char *str, char *key)
{

	if (key != NULL)
	{
		work (action, str, key);
		free (key);
		return 0;
	}
	else
		return 1;

}

void work (char action, char *str, char *key)
{

	int i = 0, j = 0;
	int keyLen = strlen (key); /* strlen calulates string length each time it's called.
				    * Assigning strlen (key) to a variable is much more
				    * efficient than using strlen inside the while loop. */


	while (str[i] != '\0')
	{
		str[i] = toupper (str[i]); /* original text upper case */
		key[j] = toupper (key[j]); /* key upper case */

		fprintf (stdout, "%c", *(transform (&action, &str[i], &key[j]))); /* print the transformed char */

		i++;
		j++;

		if (j == keyLen) /* Key loop.  */
			j = 0;

        /* Go back 1 in key pointer if str[i] !(>= 'A' || <= 'Z').  */
		if (isalpha (str[i]) == 0)
			j--;
	}

	fprintf (stdout, "\n");

}

/* Shared function used for both Caesar and Vigenère ciphers.
 * cipher 'c'
 * decipher 'd'
 */
char *transform (char *action, char *letter, char *alphabet)
{

    int offset;


     /* If it's a letter between 'A' and 'Z'  */
    if (isalpha (*letter) != 0)
    {
        if (*action == 'c')
            *letter = (((*letter + *alphabet) % (ALPHABET_NUMS)) + 
LETTER_OFFSET);
		else
		{
            /* This avoids overflow.  */
			if (*letter - *alphabet < 0)
				offset = 26;
			else
				offset = 0;

            *letter = (((*letter - *alphabet + offset) % (ALPHABET_NUMS)) + 
LETTER_OFFSET);
        }
    }

    return letter;

}
