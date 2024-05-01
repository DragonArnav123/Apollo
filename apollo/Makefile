# CC 				?= gcc
# CXX 			?= g++

# MKDIR 			?= md
# RMDIR		 	?= rd /s /q

# _APDIR 			:= ..\$(APDIR)
# _SBDIR 			:= ..\$(SBDIR)
# _EXTDIR 		:= ..\$(EXTDIR)
# _LIBDIR 		:= ..\$(LIBDIR)

# CVER 			?= 11
# CXXVER 			?= 20
# PLATFORM 		?= Windows

# DEFS 			+= -DAPOLLO_CORE

BINDIR 			:= .\bin
SRCDIR 			:= .\source
INCDIR 			:= $(SRCDIR)\include

CFLAGS 			+= -Wall -Wpedantic
CFLAGS 			+= -O2
CFLAGS 			+= --sysroot=./
CFLAGS 			+= -DAPOLLO_CORE -DAPOLLO_ASSETS_DIR=\"./assets\" 
LDFLAGS 		:= $(_LIBDIR)\glad.o
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

APOLLOLIB 		:= $(BINDIR)\libApollo.dll

.PHONY: all clean

all: dirs $(APOLLOLIB)


files:
	@echo CPP files to compile
	@echo $(SRCFILES)
	@echo H files to compile
	@echo $(INCFILES)


dirs: 
	@if not exist $(BINDIR) $(MKDIR) $(BINDIR)


$(APOLLOLIB): $(OBJFILES) | $(INCFILES)
	$(CXX) -shared -o $@ $< $(LDFLAGS)


%.o: %.cpp
	$(CXX) -o $@ -c $^ $(CFLAGS)


%.cpp:


%.h:


clean:
	$(RMDIR) $(BINDIR)