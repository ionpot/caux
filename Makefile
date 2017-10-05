CC := gcc
CFLAGS := -march=native -Wall -Wextra
OS := $(shell uname)
SHELL := sh

IDIR := ./include
SDIR := ./src
ODIR := ./obj

MINGW := /c/MinGW

IDIRS := $(IDIR)
LDIRS :=

ifneq (,$(findstring MINGW,$(OS)))
	IDIRS += $(MINGW)/include
	LDIRS += $(MINGW)/lib
endif

ifneq (,$(IDIRS))
	CFLAGS += $(patsubst %,-I%,$(IDIRS))
endif

ifneq (,$(LDIRS))
	CFLAGS += $(patsubst %,-L%,$(LDIRS))
endif

HFILES := $(wildcard $(IDIR)/*.h)
CFILES := $(wildcard $(SDIR)/*.c)
OFILES := $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(CFILES))

$(ODIR)/%.o: $(SDIR)/%.c $(HFILES)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all
all: $(OFILES)

$(OFILES): | $(ODIR)

$(ODIR):
	mkdir $@

.PHONY: info
info:
	@echo "OS: $(OS)"
	@echo "HEADERS: $(HFILES)"
	@echo "SOURCES: $(CFILES)"
	@echo "OBJECTS: $(OFILES)"
	@echo "COMPILE: $(CC) $(CFLAGS)"

.PHONY: clean
clean:
	rm -rf $(ODIR)
