/*
 * globalDefines.h
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


/* Program constants.  */
#define PRG_NAME "fcvc"
#define REPO_NAME "fast-caesar-vigenere-cipher"

/* Numeric constants.  */
#define ALPHABET_NUMS 26
#define LETTER_OFFSET 65

/* Other defines */
#define NUMBER_OF_FACTORS_TO_KEEP 3
#define TOTAL_LANGS 1
/* Tolerance must be auto adaptive.  */
#define FREQ_TOL 0.07

/* Struct that stores the number of occurrences of each factor.  */
struct occurrences {
    int factor;
    int count;
};


/* TODO  */
struct languageFreq {
    char language[3]; /* ISO 639-1 code.  */
    float score[ALPHABET_NUMS];
};


/* Scores of each letter from A to Z.
 * Data adapted from Wikipedia at:
 * https://en.wikipedia.org/wiki/Letter_frequency
 * (CC BY-SA 3.0)
 * The original data was expressed with percentages while here is divided by
 * 100.
 */
static const struct languageFreq lF[] = { \
    { "en", { \
/* A */     0.0867, \
/* B */     0.01492, \
/* C */     0.02782, \
/* D */     0.04253, \
/* E */     0.12702, \
/* F */     0.02228, \
/* G */     0.02015, \
/* H */     0.06094, \
/* I */     0.06966, \
/* J */     0.00153, \
/* K */     0.00772, \
/* L */     0.04025, \
/* M */     0.02406, \
/* N */     0.06749, \
/* O */     0.07507, \
/* P */     0.01929, \
/* Q */     0.00095, \
/* R */     0.05987, \
/* S */     0.06327, \
/* T */     0.09056, \
/* U */     0.02758, \
/* V */     0.0978, \
/* W */     0.02361, \
/* X */     0.00150, \
/* Y */     0.01974, \
/* Z */     0.00074 } },
/*    { "it", { \
            0.5, \
            0.5 } },
*/
};
