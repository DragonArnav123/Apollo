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
_EXTDIR 		:= ../$(EXTDIR)

# CFLAGS 			+= $(INCLUDES:$(EXTDIR)=$(_LIBDIR))
CFLAGS 			+= -I$(_EXTDIR)/glfw/include -I$(_EXTDIR)/glm -I$(_EXTDIR)/glad/include -I$(_EXTDIR)/spdlog/include
CFLAGS 			+= -Wall -Wpedantic
CFLAGS 			+= -DAPOLLO_INCLUDE_UTILS -DAPOLLO_INCLUDE_GLM
# CFLAGS 			+= --sysroot=./
LDFLAGS 		:= -L$(BINDIR)
LDFLAGS			+= -llibApollo -lopengl32 -lgdi32

ifeq ($(PLATFORM), Windows)
	LDFLAGS 	+= -lkernel32 -luser32
endif

ifeq ($(CONFIG), DEBUG)
	CFLAGS 			+= -save-temps -time
else
ifeq ($(CONFIG), RELEASE)
	CFLAGS 			+= -O2
else
ifeq ($(CONFIG), DIST)
	CFLAGS 			+= -O3
endif
endif
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


.PHONY: all clean run copy

all: dirs $(_APDIR)/bin/libApollo.dll $(EXE)


files:
	@echo CPP files to compile
	@echo $(SRCFILES)
	@echo H files to compile
	@echo $(INCFILES)


dirs: 
	@if not exist $(BINDIR) $(MKDIR) $(BINDIR)


$(EXE): $(OBJFILES) | copy $(INCFILES)
	$(CXX) -o $@ $^ $(LDFLAGS)


%.o: %.cpp
	$(CXX) -o $@ -c $^ $(CFLAGS)


%.cpp:


%.h:


ifeq ($(CONFIG), DEBUG)
ifeq ($(PLATFORM), Windows)
clean:
	$(RMDIR) $(BINDIR)
	$(DELFILE) $(SRCDIR)\*.o
	$(DELFILE) $(SRCDIR)\*.s
	$(DELFILE) $(SRCDIR)\*.ii
else
clean:
	$(RMDIR) $(BINDIR)
	$(DELFILE) $(SRCDIR)/*.o
	$(DELFILE) $(SRCDIR)/*.s
	$(DELFILE) $(SRCDIR)/*.ii

endif
else
ifeq ($(PLATFORM), Windows)
clean:
	$(RMDIR) $(BINDIR)
	$(DELFILE) $(SRCDIR)\*.o
else
clean:
	$(RMDIR) $(BINDIR)
	$(DELFILE) $(SRCDIR)/*.o
endif
endif 


run:
	$(EXE) $(EXEPARAMS)

ifeq ($(PLATFORM), Windows)
copy:
	copy $(_APDIR)\bin\libApollo.dll $(BINDIR)
	@echo Copied apollo/bin/libApollo.dll to sandbox/bin
else
copy:
	copy $(_APDIR)/bin/libApollo.dll $(BINDIR)
	@echo Copied apollo/bin/libApollo.dll to sandbox/bin
endif