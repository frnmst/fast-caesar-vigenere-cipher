#!/usr/bin/make -f

#
# Makefile
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


# macros
CC = /usr/bin/gcc
BIN_DIR = /usr/bin
INSTALL = /usr/bin/install

CFLAGS = -Wall -Wextra -Wpedantic -Werror -march=native -O0
CSTANDARD = -ansi
MACRO_REQ = -D_DEFAULT_SOURCE

PRG_NAME = fcvc
PRG_OBJFILES = fcvc.o


# targets

default : link # default target

all : link install clean

# compilation of single files, which keeps track of the changes of all header files (*.h) as well as the .c files
# @echo "$(CC) $< $(CFLAGS) $(CSTANDARD) $(MACRO_REQ)"
%.o: %.c *.h
	@$(CC) $(CFLAGS) $(CSTANDARD) $(MACRO_REQ) -c -o $@ $< # single object file compiling

# executables linking
link : $(PRG_OBJFILES) *.h
	@echo "Compiling ..."
	@echo "$(CC) -o $(PRG_NAME) $(CFLAGS) $(CSTANDARD) $(MACRO_REQ)"
	@$(CC) $(CFLAGS) $(CSTANDARD) $(MACRO_REQ) $(PRG_OBJFILES) -o $(PRG_NAME)
	@echo "Compiling terminated."

# 611 permissions
install :
	@echo "Installing executable in $(BIN_DIR) ..."
	@$(INSTALL) -Dm 611 --owner=$(USER) $(PRG_NAME) $(BIN_DIR)
	@echo "Installation completed."

uninstall:
	@echo "Removing $(PRG_NAME) from system ..."
	@rm -fv $(BIN_DIR)/$(PRG_NAME)
	@echo "$(PRG_NAME) removed."

clean :
	@echo "Removing object files..."
	@rm -fv *.o $(PRG_NAME)
	@echo "Object files removed."

# to protect files with the following names, the .PHONY rule is used
.PHONY : all link install uninstall clean
