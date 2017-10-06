OUT := libcaux.a

SHELL := sh
OS := $(shell uname)
MINGW := /c/MinGW

IDIR := include
SDIR := src
ODIR := obj
DDIR := dep

SPAT = $(SDIR)/%.c
DPAT = $(DDIR)/%.d
OPAT = $(ODIR)/%.o

DFILE = $(DDIR)/$*.d
OFILE = $(ODIR)/$*.o

CC := gcc
CFLAGS := -march=native -Wall -Wextra
DFLAGS = -MT "$(OFILE) $(DFILE)" -MMD -MP -MF $(DFILE)
COMPILE = $(CC) $(CFLAGS) $(DFLAGS)

IDIRS := ./$(IDIR)
LDIRS :=

ifneq (,$(findstring MINGW,$(OS)))
	IDIRS += $(MINGW)/include
	LDIRS += $(MINGW)/lib
endif

CFLAGS += $(IDIRS:%=-I%)
CFLAGS += $(LDIRS:%=-L%)

CFILES := $(wildcard $(SDIR)/*.c)
DFILES := $(CFILES:$(SPAT)=$(DPAT))
OFILES := $(CFILES:$(SPAT)=$(OPAT))

$(OPAT) $(DPAT): $(SPAT)
	$(COMPILE) -o $(OFILE) -c $<

.PHONY: all
all: $(OUT)

$(OUT): $(OFILES)
	$(AR) rcs $@ $^

$(DFILES): | $(DDIR)
$(OFILES): | $(ODIR)

$(ODIR):
	mkdir $(ODIR)

$(DDIR):
	mkdir $(DDIR)

-include $(DFILES)

.PHONY: clean
clean:
	rm -rf $(ODIR) $(DDIR) $(OUT)
