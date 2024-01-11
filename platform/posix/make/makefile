################################################################################
#                                                                              #
# makefile.os                                                                  #
#                                                                              #
# delimit utility                                                              #
#                                                                              #
# version 9.7.0 release 1                                                      #
#                                                                              #
# copyright (c) 1993-2024 Code Construct Systems (CCS) [CONFIDENTIAL]          #
#                                                                              #
################################################################################

# Open Systems OS/OE port

#
# Delimit text file utility application name
#
TARGET = delimit

#
# Application installation location
#
INSTALLATION = ../bin

#
# C compiler flags
#
CC = gcc
CFLAGS = -c

#
# C compiler definitions flags
#
CDEFINITIONS = \
	-D_POSIX_ENVIRONMENT \
	-D_ARCH_32 \
	-D_FREE_LEXICAL_BUFFERS \
	-D_FORMAT_P_SPECIFIER \
	-DYY_NO_UNPUT \
	-DYY_NO_LEAKS

#
# C compiler debug and optimize flags
#
CDEBUG = -g
COPTIMIZE = -O3 -fno-strict-overflow

#
# C compiler warnings flags
#
CWARNINGS = \
	-Werror \
	-Wall \
	-Wextra \
	-Wwrite-strings \
	-Winit-self \
	-Wcast-align \
	-Wpointer-arith \
	-Wstrict-aliasing \
	-Wformat=2 \
	-Wmissing-declarations \
	-Wmissing-include-dirs \
	-Wno-unused-parameter \
	-Wuninitialized \
	-Wold-style-definition \
	-Wstrict-prototypes \
	-Wmissing-prototypes

#
# Parser generator and flags
#
PARSER = yacc
PARSERFLAGS = -d

#
# Lexical scanner generator and flags
#
LEXER = flex
LEXERFLAGS = -I

#
# Object files
#
OBJECTS = \
	delimit.o \
	options.o \
	parse.o \
	lex.o \
	delimiter.o \
	dct.o \
	fio.o \
	util.o \
	port.o

all: $(TARGET)

#
# Rule for creating delimit text file utility application file
#
$(TARGET): $(OBJECTS)
	@echo "building application: $@"
	@$(CC) $(OBJECTS) -o $@

#
# Rule for creating parser file
#
parse.c: parse.y
	@echo "creating: parse.c"
	@$(PARSER) $(PARSERFLAGS) parse.y
	@mv -f y.tab.c parse.c
	@mv -f y.tab.h parse.h

#
# Rule for creating lexical scanner file
#
lex.c: lex.l
	@echo "creating: lex.c"
	@$(LEXER) $(LEXERFLAGS) lex.l
	@mv -f lex.yy.c lex.c

#
# Rule for creating parser object file
#
parse.o: parse.c
	@echo "building: $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CDEBUG) $(COPTIMIZE) $(CDEFINITIONS) -o $@ $<

#
# Rule for creating lexical scanner object file
#
lex.o: lex.c
	@echo "building: $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CDEBUG) $(COPTIMIZE) $(CDEFINITIONS) -o $@ $<

#
# Rule for creating object files
#
.c.o:
	@echo "building: $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNINGS) $(CDEBUG) $(COPTIMIZE) $(CDEFINITIONS) -o $@ $<

#
# Rule for deploying application and other files
#
deploy: $(TARGET)
	cp -f $(TARGET) $(INSTALLATION)
	cp -f $(TARGET).doc $(INSTALLATION)

#
# Rule for cleaning out generated files
#
clean:
	rm -f *.o
	rm -f parse.c
	rm -f parse.h
	rm -f lex.c
	rm -f $(TARGET)
