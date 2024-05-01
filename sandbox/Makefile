# CC 				?= gcc
# CXX 			?= g++

# MKDIR 			?= md
# RMDIR		 	?= rd /s /q

_APDIR 			:= ..\$(APDIR)
_SBDIR 			:= ..\$(SBDIR)
_EXTDIR 		:= ..\$(EXTDIR)
_LIBDIR 		:= ..\$(LIBDIR)

# CVER 			?= 11
# CXXVER 			?= 2a
# PLATFORM 		?= Windows

BINDIR 			:= .\bin
SRCDIR 			:= .\source
INCDIR 			:= $(SRCDIR)\include

CFLAGS 			+= -Wall -Wpedantic
CFLAGS 			+= -O2
LDFLAGS 		:= -L$(BINDIR)
LDFLAGS 		+= -llibApollo

ifeq ($(PLATFORM), Windows)
	LDFLAGS 	+= -lkernel32 -luser32
endif

SRCFILES 		:= $(wildcard $(SRCDIR)/*.cpp)
SRCFILES 		+= $(wildcard $(SRCDIR)/**/*.cpp)
SRCFILES 		+= $(wildcard $(SRCDIR)/**/**/*.cpp)
INCFILES 		:= $(wildcard $(INCDIR)/*.h)
INCFILES 		+= $(wildcard $(INCDIR)/**/*.h)
INCFILES 		+= $(wildcard $(INCDIR)/**/**/*.h)
INCFILES 		+= $(wildcard $(INCDIR)/**/**/**/.h)
OBJFILES 		:= $(SRCFILES:.cpp=.o)

EXE		 		:= $(BINDIR)\Sandbox.exe

.PHONY: all clean run

all: dirs $(BINDIR)\libApollo.dll $(EXE)


$(BINDIR)\libApollo.dll:
	copy $(_APDIR)\bin\libApollo.dll $(BINDIR)


dirs: 
	@if not exist $(BINDIR) $(MKDIR) $(BINDIR)


$(EXE): $(OBJFILES) | $(INCFILES)
	$(CXX) -o $@ $< $(LDFLAGS)


%.o: %.cpp
	$(CXX) -o $@ -c $^ $(CFLAGS)


%.cpp:


%.h:


clean:
	$(RMDIR) $(BINDIR)


run: all
	$(EXE)