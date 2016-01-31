#!/bin/bash

#
# compile.sh
#
# Copyright (C) 2016 frnmst (Franco Masotti) <franco.masotti@live.com>
#                                            <franco.masotti@student.unife.it>
#
# This file is part of fast-caesar-vigenere-cipher.
#
# fast-caesar-vigenere-cipher is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# fast-caesar-vigenere-cipher is distributed in the hope that it will be
# useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with fast-caesar-vigenere-cipher.  If not, see
# <http://www.gnu.org/licenses/>.
#


# -O0 = no optimization = slower compilation but smaller binary and less mem used at runtime
# -march=native = compiled only for that particular arch
# ANSI standard (C90)
# -D_DEFAULT_SOURCE are compiler headers that make possible to use -ansi
gcc fcvc.c core.c utils.c monoalphaModules/* -Wall -Wextra -Wpedantic -Werror \
-march=native -O0 -std=c90 -D_DEFAULT_SOURCE -o fcvc
