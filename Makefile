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

CFLAGS += $(patsubst %,-I%,$(IDIRS))
CFLAGS += $(patsubst %,-L%,$(LDIRS))

CFILES := $(wildcard $(SDIR)/*.c)
DFILES := $(patsubst $(SDIR)/%.c,$(DDIR)/%.d,$(CFILES))
OFILES := $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(CFILES))

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
