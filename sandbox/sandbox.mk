BINDIR 			:= bin
SRCDIR 			:= source
INCDIR 			:= $(SRCDIR)/include

ifeq ($(PLATFORM), Windows)
_APDIR 			:= ..\$(APDIR)
_SBDIR 			:= .\\
_LIBDIR 		:= ..\$(LIBDIR)
else
_APDIR 			:= ../$(APDIR)
_SBDIR 			:= .//
_LIBDIR 		:= ../$(LIBDIR)
endif

CFLAGS 			+= -Wall -Wpedantic
CFLAGS 			+= -O2
CFLAGS 			+= --sysroot=./
LDFLAGS 		:= -L$(BINDIR)
LDFLAGS			+= -llibApollo -lopengl32 -lgdi32

ifeq ($(PLATFORM), Windows)
	LDFLAGS 	+= -lkernel32 -luser32
endif

ifeq ($(CONFIG), DEBUG)
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

EXE 			:= $(BINDIR)/Sandbox.exe

default_target: all


.PHONY: all clean run

all: dirs $(_APDIR)/bin/libApollo.dll $(EXE)


files:
	@echo CPP files to compile
	@echo $(SRCFILES)
	@echo H files to compile
	@echo $(INCFILES)


$(_APDIR)/bin/libApollo.dll:
	copy $(_APDIR)\bin\libApollo.dll $(BINDIR)


dirs: 
	@if not exist $(BINDIR) $(MKDIR) $(BINDIR)


$(EXE): $(OBJFILES) | $(INCFILES)
	$(CXX) -o $@ $^ $(LDFLAGS)


%.o: %.cpp
	$(CXX) -o $@ -c $^ $(CFLAGS)


%.cpp:


%.h:


clean:
	$(RMDIR) $(BINDIR)

run:
	$(EXE)