# Makefile variables

MAIN = ./src/main.cc

SRCDIR=./src/
OBJDIR=./objects/

BUILDIR=./build/
EXECNAME=aoc

# 

EXECUTABLE=$(BUILDIR)$(EXECNAME)

COMPILER=g++
COMPILER_FLAGS=-std=c++23 -Wall -Wextra -g -pedantic -Wformat=0
LIBRARIES_FLAGS=-lm

SOURCES = $(shell find -type f -name '*.cc' -a -not -name 'main.cc')
OBJECTS = $(subst .cc,.o,$(subst $(SRCDIR),$(OBJDIR),$(SOURCES)))

# 

# MAKEFLAGS += --jobs=$(shell nproc)

# 

# Define task functions to generate some pretty task logs

define TASK_LOG
@echo "\e[38;2;128;128;128m\e[1m╠╾\e[0m ${1}\e[0m"
endef

define TASK_BEGIN
@echo ""
@echo "\e[38;2;128;128;128m\e[1m╔═\e[0m \e[38;2;255;255;255m\e[1mBegin of \e[38;2;0;255;255m\e[1m${1}\e[0m \e[38;2;255;255;255m\e[1mtask\e[0m"
@$(call TASK_LOG,\e[3mCurrent workdir: \e[0m\e[38;2;255;0;255m$(shell pwd))
endef

define TASK_END
@echo "\e[38;2;128;128;128m\e[1m╚═\e[0m \e[38;2;255;255;255m\e[1mEnd of task\e[0m"
endef

define TASK_COMMAND_EXECUTION
@$(call TASK_LOG,\e[3mExecuting: \e[0m\e[38;2;255;255;0m${1})
@$(call TASK_LOG,\e[3mLogs:)
@${1}
endef

# 

test:
	@echo $(SOURCES)
	@echo $(OBJECTS)

# MAKE ALL

all:
	@$(MAKE) $(EXECUTABLE) -s
	@$(MAKE) compile -s

# PROJECT COMPILATION

$(EXECUTABLE): $(OBJECTS)

compile:
	@$(call TASK_BEGIN,project compilation)

	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(BUILDIR))

	@$(call TASK_LOG,Compiling project from \e[38;2;128;0;255m$(PROJECT_MAIN)\e[0m to \e[38;2;128;0;255m$@\e[0m)

	@$(call TASK_COMMAND_EXECUTION,$(COMPILER) $(COMPILER_FLAGS) $(MAIN) $(OBJECTS) -o $(EXECUTABLE) $(LIBRARIES_FLAGS))

	@$(call TASK_END)

#

# OBJECTS GENERATION

$(OBJDIR)%.o: $(SRCDIR)%.cc $(SRCDIR)%.hh
	@$(call TASK_BEGIN,object generation)

	@$(call TASK_LOG,Generating object from \e[38;2;128;0;255m$<\e[0m to \e[38;2;128;0;255m$@\e[0m)

	@$(call TASK_COMMAND_EXECUTION,mkdir -p $(dir $@))
	@$(call TASK_COMMAND_EXECUTION,$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@ $(LIBRARIES_FLAGS))

	@$(call TASK_END)

# 

# PROJECT CLEANING

clean:
ifneq (rv-make,$(firstword $(MAKECMDGOALS)))
	@$(call TASK_BEGIN,clean)
	
	@$(call TASK_COMMAND_EXECUTION,find $(OBJECT_DIRECTORY) -name '*.o' | xargs rm -f )

	@$(call TASK_END)
endif

# 