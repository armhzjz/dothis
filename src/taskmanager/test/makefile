#.PHONY: tests
#test: tests
#@echo Hola Mundo

### If you wish to use extra libraries (math.h for instance),
### add their flags here in the "LIBS" variable.

LIBS =

###
CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

INC = -I../../datamodel
INC += -I../
INC += -I.

.PHONY: test
test: tests.out
	@./tests.out

.PHONY: memcheck
memcheck: *.c ../*.c ../*.h
	@echo Compiling $@
	@$(CC) $(ASANFLAGS) $(CFLAGS) ../*.c src/unity.c *.c -o memcheck.out $(LIBS) $(INC)
	@./memcheck.out
	@echo "Memory check passed"

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM

tests.out: *.c ../*.c ../*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) ../*.c src/unity.c *.c -o tests.out $(LIBS) $(INC)
