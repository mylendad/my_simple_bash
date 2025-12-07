CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
LDFLAGS = -g
CHECK_LIBS =

ifeq ($(shell uname), Linux)
	CHECK_LIBS += -lm -lsubunit
endif

CAT_SRCS = cat/cat.c cat/main.c
CAT_OBJS = $(patsubst %.c, %.o, $(CAT_SRCS))
CAT_TARGET = s21_cat

GREP_SRCS = grep/grep.c grep/main.c
GREP_OBJS = $(patsubst %.c, %.o, $(GREP_SRCS))
GREP_TARGET = s21_grep

all: clean $(CAT_TARGET) $(GREP_TARGET)

$(CAT_TARGET): $(CAT_OBJS)
	$(CC) $(CFLAGS) $(CAT_OBJS) $(LDFLAGS) -o $(CAT_TARGET)

$(GREP_TARGET): $(GREP_OBJS)
	$(CC) $(CFLAGS) $(GREP_OBJS) $(LDFLAGS) -o $(GREP_TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(CAT_TARGET) $(GREP_TARGET)
	@echo "Running tests for s21_cat..."
	./tests/test_cat.sh
	@echo "Running tests for s21_grep..."
	./tests/test_grep.sh

valgrind: $(CAT_TARGET) $(GREP_TARGET)
	@echo "Running valgrind for s21_cat..."
	valgrind --tool=memcheck --leak-check=yes ./$(CAT_TARGET) tests/cat/test.txt
	@echo "Running valgrind for s21_grep..."
	valgrind --tool=memcheck --leak-check=yes ./$(GREP_TARGET) "pattern" /dev/null

clean:
	rm -f $(CAT_OBJS) $(CAT_TARGET) $(GREP_OBJS) $(GREP_TARGET)
	rm -rf report_s21_cat report_s21_grep
	rm -f *.gcda *.gcno *.info
