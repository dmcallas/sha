# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ==========================================

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OSTYPE),cygwin)
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=
else ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q
	MKDIR = mkdir
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=
endif

UNITY_ROOT=Unity
C_COMPILER=gcc

CFLAGS = -std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror 
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wmissing-declarations

TARGET_TEST_F=all_tests
TARGET_TEST = $(TARGET_TEST_F)$(TARGET_EXTENSION)
TARGET_BUILD_F=sha
TARGET_BUILD = $(TARGET_BUILD_F)$(TARGET_EXTENSION)
SRC_FILES_BUILD=\
  src/bit_manip.c \
  src/sha1.c \
  src/main.c
SRC_FILES_TEST=\
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  src/bit_manip.c \
  src/sha1.c \
  test/bit_manip_test.c \
  test/test_runners/bit_manip_test_runner.c \
  test/test_runners/all_tests.c
INC_DIRS=-Isrc -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src
SYMBOLS=

all: clean default test

default: $(TARGET_BUILD)

$(TARGET_BUILD):
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES_BUILD) -o $(TARGET_BUILD)


test: $(TARGET_TEST)

$(TARGET_TEST):
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES_TEST) -o $(TARGET_TEST)
	./$(TARGET_TEST)

clean:
	$(CLEANUP) $(TARGET_BUILD) $(TARGET_TEST)

get_unity:
	git checkout https://github.com/ThrowTheSwitch/Unity.git
