
vpath %.c src

CC              ?= gcc
CFLAGS          ?= -O0 -g -ggdb
CPPFLAGS        ?= 
LDFLAGS         ?= 
LIBS            ?= 

ifeq ($(CC),cc)
    CC          := /usr/local/bin/gcc
endif

export CP       := $(strip cp -f)
export MKDIR    := $(strip mkdir -p)
export RM       := $(strip rm -f)

export CC       := $(strip $(CC))
export CFLAGS   := $(strip $(CFLAGS) -std=c17 -Wall -Wextra -Wpedantic)
export CPPFLAGS := $(strip $(CPPFLAGS) -I include -D_POSIX_C_SOURCE -D_GNU_SOURCE)
export LDFLAGS  := $(strip $(LDFLAGS))
export LIBS     := $(strip $(LIBS) $(LOADLIBES))

OBJS            := $(patsubst %.c,%.o,$(notdir $(wildcard src/*.c)))

TARGET          := options

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS)    -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)
