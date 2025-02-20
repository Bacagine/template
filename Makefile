# Makefile
# 
# Written by Gustavo Bacagine <gustavo.bacagine@protonmai.com>
# 
# Description: Makefile of the project template
# 
# Date: 15/10/2024

TARGET  = template

BUILD_KEY := $(shell uuidgen)

INCDIR  = include
SRCDIR  = src
OBJDIR  = obj
BINDIR  = bin
LIBDIR  = lib
LOGDIR  = log

SRC     = $(wildcard $(SRCDIR)/*.c)
OBJS    = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.c=.o))
BIN     = $(BINDIR)/$(TARGET)

LDFLAGS = 
LDLIBS  = 
CFLAGS  = -I $(INCDIR) -Wall -Wextra
CC      = gcc

TIMESTAMP := $(shell date +"%d%m%Y%H%M%S")
LOGFILE := $(LOGDIR)/compilation-$(TIMESTAMP).log

ifdef APPLE
  CFLAGS += -DAPPLE
endif

ifdef LINUX
  CFLAGS  += -DLINUX
  LDLIBS  += -lpthread
endif

ifdef _WIN32
  CFLAGS  += -D_WIN32
endif

ifdef DEBUG
  CFLAGS  += -DDEBUG -g -O0
else
  CFLAGS += -O2
endif

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) 2>&1 | tee -a $(LOGFILE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>&1 | tee -a $(LOGFILE)

all: clean check_goto genbuildinfo $(LOGDIR) $(OBJDIR) $(BINDIR) $(BIN)

genbuildinfo:
	./gen_build_info.sh

check_goto:
	@grep -rn --color "goto" $(SRC) && { echo "\033[1;31mError:\033[m '\033[1;33mgoto\033[m' detected in source file!\nCompilation aborted..." && grep -rn --color "goto" $(SRC) >> $(LOGFILE) && echo "Error: 'goto' detected in source file!\nCompilation aborted..." >> $(LOGFILE); exit 1;} || true

$(LOGDIR):
	mkdir -p $(LOGDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rvf $(OBJDIR)

distclean: clean
	rm -rvf $(BINDIR)
	rm -rvf $(LOGDIR)

install: all
ifdef _WIN32
	.\install.bat
endif

ifdef LINUX
	./install.sh
endif

ifdef APPLE
	./install.sh
endif

uninstall:
ifdef _WIN32
	.\uninstall.bat
endif

ifdef LINUX
	./uninstall.sh
endif

ifdef APPLE
	./uninstall.sh
endif

run: $(BIN)
	./$(BIN)

.PHONY: all clean check_goto distclean install run uninstall

