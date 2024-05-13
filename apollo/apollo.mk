BINDIR 			:= bin
SRCDIR 			:= source
INCDIR 			:= $(SRCDIR)/include

_APDIR 			:= .
_SBDIR 			:= ../$(SBDIR)
_LIBDIR 		:= ../$(LIBDIR)
_EXTDIR 		:= ../$(EXTDIR)

# CFLAGS 			+= $(INCLUDES:$(EXTDIR)=$(_LIBDIR))
CFLAGS 			+= -I$(_EXTDIR)/glfw/include -I$(_EXTDIR)/glm -I$(_EXTDIR)/glad/include -I$(_EXTDIR)/spdlog/include
CFLAGS 			+= -Wall -Wpedantic
CFLAGS 			+= --sysroot=./
CFLAGS 			+= -DAPOLLO_CORE -DAPOLLO_ASSETS_DIR=\"./assets\" 
LDFLAGS 		:= $(_LIBDIR)/glad.o
LDFLAGS 		+= -L$(_LIBDIR)
LDFLAGS			+= -lglfw3 -lglm -lspdlog -lopengl32 -lgdi32

ifeq ($(PLATFORM), Windows)
	LDFLAGS 	+= -lkernel32 -luser32
endif

ifeq ($(CONFIG), DEBUG)
	CFLAGS 			+= -save-temps -time
else
ifeq ($(CONFIG), RELEASE)
	CFLAGS 			+= -02
else
ifeq ($(CONFIG), DIST)
	CFLAGS 			+= -03
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

APOLLOLIB 		:= $(BINDIR)/libApollo.dll

default_target: all


.PHONY: all clean

all: dirs $(INCDIR)/APpch.h.gch $(APOLLOLIB)

try:
	@echo $(CFLAGS)

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