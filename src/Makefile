CC= g++ 
CFLAGS= -Wall -Wextra -Werror
STANDART= -std=c++17
TESTFLAGS=-lgtest
TESTFILES= tests/*.cc

all: gcov_report

test: clean
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test

gcov_report: clean
	$(CC) $(CFLAGS) --coverage $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test
	lcov -t "test" -o test.info -c -d . --no-external
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.out *.o s21_matrix_oop.a *.gcda *.gcno *.info test main
	rm -rf report