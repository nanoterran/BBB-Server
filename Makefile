# Makefile to compile for the TARGET_NAME board.
# 
# Program name for executable
TARGET_NAME = Server

# Project Home Directoy
PROJECT_HOME_DIR ?= .

# Build Directoy
BUILD_DIR ?= $(PROJECT_HOME_DIR)/Build

TARGET = $(BUILD_DIR)/$(TARGET_NAME)

# ARM Compiler for BBB
CC = arm-linux-gnueabihf-gcc-7

# Source files
SOURCE = $(wildcard $(PROJECT_HOME_DIR)/*.c)

# Object files
OBJS = $(SOURCE:%=$(BUILD_DIR)/%.o)

# Dependencies
DEP := $(OBJs:.o=.d) 

# Compiler and Linker Flags
CFLAGS += -Wall -c
LFLAGS += -Wall

# Links all the object files
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(TARGET)

# Compiles
$(BUILD_DIR)/%.c.o: $(SOURCE)
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo "Removing $(BUILD_DIR)";
	@$(RM) -r $(BUILD_DIR);

.PHONY: help
help:
	@echo "\tflash: To flash the .hex file into TARGET_NAME."
	@echo "\tsize: To get the size of executable file."

# include all Dependencies
-include $(DEP)

MKDIR_P ?= mkdir -p
RM ?= rm