BINDIR 			:= bin
SRCDIR 			:= source
INCDIR 			:= $(SRCDIR)/include

_APDIR 			:= .
_SBDIR 			:= ../$(SBDIR)
_LIBDIR 		:= ../$(LIBDIR)

CFLAGS 			+= -Wall -Wpedantic
CFLAGS 			+= -O2
CFLAGS 			+= --sysroot=./
CFLAGS 			+= -DAPOLLO_CORE -DAPOLLO_ASSETS_DIR=\"./assets\" 
LDFLAGS 		:= $(_LIBDIR)/glad.o
LDFLAGS 		+= -L$(_LIBDIR)
LDFLAGS			+= -lglfw3 -lglm -lopengl32 -lgdi32

ifeq ($(PLATFORM), Windows)
	LDFLAGS 	+= -lkernel32 -luser32
endif

ifeq ($(CONFIG), Debug)
	CFLAGS 			+= -save-temps -time
endif

SRCFILES 		:= $(wildcard $(SRCDIR)/*.cpp)
SRCFILES 		+= $(wildcard $(SRCDIR)/**/*.cpp)
SRCFILES 		+= $(wildcard $(SRCDIR)/**/**/*.cpp)
INCFILES 		:= $(wildcard $(INCDIR)/*.h)
INCFILES 		+= $(wildcard $(INCDIR)/**/*.h)
INCFILES 		+= $(wildcard $(INCDIR)/**/**/*.h)
INCFILES 		+= $(wildcard $(INCDIR)/**/**/**/.h)
OBJFILES 		:= $(SRCFILES:.cpp=.o)

APOLLOLIB 		:= $(BINDIR)/libApollo.dll

default_target: all


.PHONY: all clean

all: dirs $(INCDIR)/APpch.h.gch $(APOLLOLIB)


$(INCDIR)/APpch.h.gch: $(INCDIR)/APpch.h
	$(CXX) -o $@ $^ $(CFLAGS)


files:
	@echo CPP files to compile
	@echo $(SRCFILES)
	@echo H files to compile
	@echo $(INCFILES)


dirs: 
	@if not exist $(BINDIR) $(MKDIR) $(BINDIR)


$(APOLLOLIB): $(OBJFILES) | $(INCFILES)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)


%.o: %.cpp
	$(CXX) -o $@ -c $^ $(CFLAGS)


%.cpp:


%.h:


clean:
	$(RMDIR) $(BINDIR)