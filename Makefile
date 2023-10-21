.PHONY: all test cover gcov_report style gost clean

# UTILITIES
CC = gcc
MK = mkdir -p
RM = rm -rf
OPEN_TXT = open -e
OS := $(shell uname)
ifeq ($(OS), Darwin)
	LEAKS = CK_FORK=no leaks --atExit --
	REPORT_OPEN = open
else ifeq ($(OS), Linux)
	LEAKS =
	REPORT_OPEN = xdg-open
endif

# UTILITIES OPTIONS
CF = -Wall -Werror -Wextra -lstdc++ -I./
STD = -std=c++17
ifeq ($(OS), Darwin)
	TEST_FLAGS = -lcheck
else ifeq ($(OS), Linux)
	TEST_FLAGS = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif
GTESTF = -lgtest -pthread
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# FILENAMES
MODEL_DIR = ./MVCModel/
CONTROLLER_DIR = ./MVCController/
VIEW_DIR = ./MVCView/

SRC = $(wildcard $(MODEL_DIR)*.cc)
SRC += $(wildcard $(CONTROLLER_DIR)*.cc)

BUILD_DIR = ./build/
APP = SmartCalc_v2.app

TESTS_DIR = ./tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.cc)
TESTS_OBJ_DIR = ./tests_obj/
TESTS_OBJ = $(patsubst $(TESTS_DIR)%.cc, $(TESTS_OBJ_DIR)%.o, $(TESTS_SRC))
TESTS_RUNNER = tests_runner
TESTS_REPORT = u_tests_report.txt

EXE = a.out $(TESTS_RUNNER)

# BUILD
all: clean style test gcov_report install dvi dist

# APP
install:
	$(MK) $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake ../$(VIEW_DIR)SmartCalc_v2.pro && make -j6 && make clean && rm -rf .qmake.stash Makefile

launch:
	open $(BUILD_DIR)$(APP)

uninstall:
	rm -rf $(BUILD_DIR)*

dvi:
	open README.MD

dist:
	tar -zcvf SmartCalc_v2.tar $(ALL_DIRS) Makefile

app_leaks:
	$(LEAKS) $(BUILD_DIR)$(APP)/Contents/MacOS/SmartCalc_v2

# TESTS && COVERAGE
test: clean testobjects
	$(CC) $(CF) $(STD) $(GTESTF) $(TESTS_OBJ) $(SRC) -o $(TESTS_RUNNER)
	./$(TESTS_RUNNER) > $(TESTS_REPORT)
	$(OPEN_TXT) $(TESTS_REPORT)
	@$(RM) $(TESTS_RUNNER)

cover: gcov_report

gcov_report: clean testobjects
	$(CC) $(CF) $(STD) $(GTESTF) $(GCOV_FLAGS) $(ASAN) $(TESTS_OBJ) $(SRC) -o $(TESTS_RUNNER)
	./$(TESTS_RUNNER) > $(TESTS_REPORT)
	@$(RM) $(TESTS_RUNNER)
	open $(TESTS_REPORT)
	@lcov -t "gcov_report" --ignore-errors mismatch -o report.info --no-external -c -d .
	@genhtml -o report report.info
	@$(REPORT_OPEN) ./report/index.html
	@$(RM) *.gcno *.gcda *.info

testobjects: maketestobjdir $(TESTS_OBJ)
	@echo "\033[0;32m$(CC): TEST OBJECT FILES COMPILATION SUCCESS\033[0m"

maketestobjdir:
	@$(MK) $(TESTS_OBJ_DIR)

$(TESTS_OBJ_DIR)%.o: $(TESTS_DIR)%.cc
	$(CC) $(CF) $(STD) $(ASAN) -c $^ -o $@


# SERVICE
style:
	@echo "┏==================================┓"
	@echo "┃  Checking code for Google Style  ┃"
	@echo "┗==================================┛"
	@find . -name "*.h" -o -name "*.cc" | xargs clang-format --style=google -n

gost:
	@echo "┏====================================┓"
	@echo "┃  Formatting code for Google Style  ┃"
	@echo "┗====================================┛"
	@find . -name "*.h" -o -name "*.cc" | xargs clang-format --style=google -i

clean:
	@$(RM) $(EXE)
	@$(RM) *.txt
	@rm -rf *.out *.dSYM ./tests/*.dSYM ./units/*dSYM
	@rm -rf *.gcno *.gcda ./report gcov_test *.info
