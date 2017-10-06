OUT := libcaux.a

SHELL := sh
OS := $(shell uname)
MINGW := /c/MinGW

IDIR := include
SDIR := src
ODIR := obj
DDIR := dep

DFILE = $(DDIR)/$*.d

CC := gcc
CFLAGS := -march=native -Wall -Wextra
DFLAGS = -MT "$@ $(DFILE)" -MMD -MP -MF $(DFILE)
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
DFILES := $(CFILES:$(SDIR)/%.c=$(DDIR)/%.d)
OFILES := $(CFILES:$(SDIR)/%.c=$(ODIR)/%.o)

$(ODIR)/%.o: $(SDIR)/%.c | $(DDIR)
	$(COMPILE) -o $@ -c $<

.PHONY: all
all: $(OUT)

$(OUT): $(OFILES)
	$(AR) rcs $@ $^

$(OFILES): | $(ODIR)

$(ODIR):
	mkdir $(ODIR)

$(DDIR):
	mkdir $(DDIR)

-include $(DFILES)

.PHONY: clean
clean:
	rm -rf $(ODIR) $(DDIR) $(OUT)
