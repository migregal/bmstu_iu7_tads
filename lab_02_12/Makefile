.PHONY : all run debug runmem gcov clean func check unit

SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out
UTESTS_DIR := ./unit_tests
FTESTS_DIR := ./func_tests

CC := gcc
CFLAGS := -std=c99 -I$(INC_DIR) -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
HEADERS := $(wildcard $(INC_DIR)/*.h)

U_CFLAGS := -lcheck -lpthread -lrt
U_SRCS := $(wildcard $(UTESTS_DIR)/*.c)
U_OBJS := $(U_SRCS:$(UTESTS_DIR)/%.c=$(OUT_DIR)/%.o)

EXEC := app.exe
UEXEC := unit_tests.exe

all: $(EXEC)

run: $(EXEC)
	@clear
	@./$^ $(args)

$(EXEC): $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ $^

debug : CFLAGS += -g -fno-inline -fno-omit-frame-pointer -O0 --coverage
debug : all

runmem : debug
	drmemory -- ./$(EXEC) $(args)

gcov :
	@$(RM) $(OUT_DIR)/*.c.gcov
	@gcov -d $(OUT_DIR)/*.gcda
	@mv *.c.gcov $(OUT_DIR)
	@$(RM) *.gcno

func: $(EXEC)
	@bash $(FTESTS_DIR)/run_tests.sh

unit : $(UEXEC)
	./$(UEXEC)

$(UEXEC) : $(U_OBJS) $(filter-out $(OUT_DIR)/main.o, $(OBJS)) $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ $^ $(U_CFLAGS)

cppcheck: $(SRCS)
	@cppcheck -I$(INC_DIR) -q --std=c99 --platform=unix64 \
--enable=all --template='{id} {file}:{line} {message}' $^

objdir:
	@mkdir -p $(OUT_DIR)

${OUT_DIR}/%.o : ${SRC_DIR}/%.c objdir
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_%.o : $(UTESTS_DIR)/check_%.c objdir
	@$(CC) $(CFLAGS) -o $@ -c $<

$(INC_DIR)/%.h:

clean:
	@$(RM) $(EXEC) $(UEXEC) ${OUT_DIR}/*
	@rm -rf $(OUT_DIR)
