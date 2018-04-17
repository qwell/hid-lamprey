-include config.out

MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP

APPS:=lamprey
APPSUFFIX:=
SOS:=liblamprey.so

ifeq ($(OS),mingw32)
APPSUFFIX:=.exe
SOS:=$(SOS:.so=.dll)
else ifeq ($(OS),cygwin)
APPSUFFIX:=.exe
SOS:=$(SOS:.so=.dll)
else
CFLAGS+=-fPIC
endif

CFLAGS+=-Wall
SO_LIBS+=-lm
LIBS+=-L. -llamprey -Wl,-rpath=.
FILTER_SRC:=

ifeq ($(OS),windows)
else
FILTER_SRC+=input-xinput.c display-win32.cpp
endif

ifeq ($(DEBUG),1)
CFLAGS+=-DDEBUG
endif
ifeq ($(HAVE_EVDEV),1)
CFLAGS+=$(EVDEV_CFLAGS)
SO_LIBS+=$(EVDEV_LIBS)
else
FILTER_SRC+=input-evdev.c
endif
ifeq ($(HAVE_XML2),1)
CFLAGS+=$(XML2_CFLAGS)
SO_LIBS+=$(XML2_LIBS)
else
FILTER_SRC+=settings-xml2.c
endif
ifeq ($(HAVE_CLI),1)
else
FILTER_SRC+=display-cli.c
endif
ifeq ($(HAVE_GTK3),1)
CFLAGS+=$(GTK3_CFLAGS)
SO_LIBS+=$(GTK3_LIBS)
else
FILTER_SRC+=display-gtk.c
endif
ifeq ($(HAVE_XDO),1)
CFLAGS+=$(XDO_CFLAGS)
SO_LIBS+=$(XDO_LIBS)
else
FILTER_SRC+=xdo.c
endif

SRCS_C:=$(filter-out $(FILTER_SRC),$(wildcard *.c))
SRCS_CC:=$(filter-out $(FILTER_SRC),$(wildcard *.cpp))
OBJS_C:=$(SRCS_C:.c=.o)
OBJS_CC:=$(SRCS_CC:.cpp=.oo)

ALLFLAGS:=$(CFLAGS) $(LIBS) $(SO_LIBS) $(SRCS_C) $(SRCS_CC)

COLOR_RED=\033[31m
COLOR_GREEN=\033[32m
COLOR_BLUE=\033[34m
COLOR_DEFAULT=\033[39m

ifeq ($(shell echo '$(ALLFLAGS)' | cmp -s - Makefile.deps; echo $$?),1)
REBUILD:=rebuild
.PHONY: $(REBUILD)
endif

all: $(APPS:%=%$(APPSUFFIX))

lamprey$(APPSUFFIX): lamprey.o

$(APPS:%=%$(APPSUFFIX)):
	@$(CC) -o $@ $< $(CFLAGS) $(LIBS) $(SO_LIBS)
	@printf "[$(COLOR_RED)%-20s$(COLOR_DEFAULT)] < $(COLOR_GREEN)$<$(COLOR_DEFAULT)\n" "$@"

$(APPS:%=%$(APPSUFFIX)): $(SOS)

-include $(patsubst %.o,.%.o.d,$(OBJS_C))
-include $(patsubst %.oo,.%.oo.d,$(OBJS_CC))

$(SOS): $(filter-out $(APPS:%$(APPSUFFIX)=%.o),$(OBJS_C)) #$(filter-out $(APPS:%$(APPSUFFIX)=%.oo),$(OBJS_CC))
	@$(CC) -o $@ $^ $(CFLAGS) $(SO_LIBS) -shared
	@printf "[$(COLOR_RED)%-20s$(COLOR_DEFAULT)] < $(COLOR_GREEN)$^$(COLOR_DEFAULT)\n" "$@"

%.o: %.c Makefile.deps
	@$(CC) -o $@ -c $< $(MAKE_DEPS) $(CFLAGS)
	@printf "[$(COLOR_BLUE)%-20s$(COLOR_DEFAULT)] < $(COLOR_GREEN)$<$(COLOR_DEFAULT)\n" "$@"

%.oo: %.cpp Makefile.deps
	@$(CPP) -o $@ -c $< $(MAKE_DEPS) $(CFLAGS)
	@printf "[$(COLOR_BLUE)%-20s$(COLOR_DEFAULT)] < $(COLOR_GREEN)$<$(COLOR_DEFAULT)\n" "$@"

Makefile.deps: $(REBUILD) config.out
	@echo '$(ALLFLAGS)' > $@

clean:
	@rm -rf $(APPS)
	@rm -rf $(APPS:%=%$(APPSUFFIX))
	@rm -rf *.so
	@rm -rf *.dll
	@rm -rf *.o
	@rm -rf .*.o.d
	@rm -rf config.out
	@rm -rf include/config.h
	@rm -rf Makefile.deps
	@rm -rf config.log
	@rm -rf config.status
