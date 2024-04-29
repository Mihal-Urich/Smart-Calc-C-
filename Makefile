CC=gcc
CFLAG=-c 
CFLAGS=-lstdc++ -std=c++17 -pedantic -Wall -Werror -Wextra
SRC_DIR=backend
OS := $(shell uname)
TEST_LIBS = -lgtest -lgtest_main -lpthread


all: clean install dvi

install: clean
	cd SmartCalc2 && cmake CMakeLists.txt && make && rm Makefile && mv SmartCalc2.app ../SmartCalc2.app

uninstall:
	rm -rf SmartCalc2.app

dvi:
	@open SmartCalc2/README.html

tests: clean
	@$(CC) $(CFLAGS) unit_tests.cc SmartCalc2/model.cc -g -o unit_tests $(TEST_LIBS)
	@./unit_tests

dist: install
	rm -rf Archive_calc/
	mkdir Archive_calc/
	mv SmartCalc2.app Archive_calc
	tar -cvzf Archive_calc.tar.gz Archive_calc

gcov_report: clean
	@$(CC) $(CFLAGS) --coverage unit_tests.cc SmartCalc2/model.cc -o test $(TEST_LIBS)
	chmod +x *
	./test
	lcov -t "test" -o test.info --no-external -c -d . --ignore-errors mismatch
	genhtml -o report/ test.info
	open ./report/index.html

clang:
	clang-format -style=Google -n SmartCalc2/*.cc SmartCalc2/*.h *.cc

clean:
	@rm -rf *.o
	@rm -rf *.gcda *.gcno *.info
	@rm -rf gcov_report
	@rm -rf gcov_test
	@rm -rf report
	@rm -rf SmartCalc2/unit_test
	@rm -rf build/
	@rm -rf SmartCalc2.app
	@rm -rf SmartCalc2/SmartCalc2_autogen
	@rm -rf SmartCalc2/CMakeFiles
	@rm -rf SmartCalc2/CMakeCache.txt
	@rm -rf SmartCalc2/cmake_install.cmake
	@rm -rf Archive_calc
	@rm -rf dist-newstyle/
	@rm -rf unit_tests.dSYM
	@rm -rf unit_tests
	@rm -rf test


.PHONY: all install uninstall dvi test dist format clean
