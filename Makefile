.PHONY: all test gcov gcov_report style gost clean

# UTILITIES
CC = gcc
MK = mkdir -p
RM = rm -rf
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
SRC += $(wildcard $(VIEW_DIR)*.c)

BUILD_DIR = ./build/
APP = SmartCalc_v2.app

TESTS_DIR = ./tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.cc)
TEST_EXE = ./tests_runner

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



# SERVICE
style:
	find . -name "*.h" -o -name "*.cc" | xargs clang-format --style=google -n

gost:
	find . -name "*.h" -o -name "*.cc" | xargs clang-format --style=google -i

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(SRC_DIR)*.o
	@$(RM) ./report/
	@$(RM) *.dSYM
	@$(RM) a.out *.tar
	@$(RM) *.gcno *.gcda
	@$(RM) $(TEST_EXE)
