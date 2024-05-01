CC 				:= gcc
CXX 			:= g++

MKDIR 			:= md
RMDIR		 	:= rd /s /q

APDIR 			:= .\apollo
SBDIR 			:= .\sandbox
EXTDIR 			:= .\library
LIBDIR 			:= .\libs

CVER 			?= 11
CXXVER 			?= 20
PLATFORM 		?= Windows

CONFIG 			?= Debug

CFLAGS 			:= -DCXX_STD_VERSION=$(CXXVER) -DC_STD_VERSION=$(CVER)
CFLAGS 			+= -I.\library\glfw\include -I.\library\glm -I.\library\glad\include

ifeq ($(PLATFORM), Windows)
	CFLAGS 		+= -DAPOLLO_PLATFORM_WINDOWS
endif

ifeq ($(CXXVER), 20)
	CFLAGS 		+= -std=c++2a
else
	CFLAGS 		+= -std=c++$(CXXVER)
endif

export CC
export CXX
export MKDIR
export RMDIR
export APDIR
export SBDIR
export EXTDIR
export LIBDIR
export CVER
export CXXVER
export CFLAGS

.PHONY: all clean-all clean-apollo clean-sandbox clean-lib run apollo sandbox


all: libraries apollo sandbox


libraries: md-lib $(LIBDIR)\libglfw3.a $(LIBDIR)\libglm.a $(LIBDIR)\glad.o


md-lib:
	@if not exist $(LIBDIR) $(MKDIR) $(LIBDIR)


# GLFW_LIBRARY_TYPE=STATIC/SHARED/OBJECT GLFW_BUILD_EXAMPLES=ON/OFF GLFW_BUILD_TESTS=ON/OFF GLFW_BUILD_DOCS=ON/OFF
$(LIBDIR)\libglfw3.a:
	cd $(EXTDIR)\glfw && if not exist .\bin\src\libglfw3.a cmake -S . -B .\bin -G "MinGW Makefiles" -DGLFW_LIBRARY_TYPE=STATIC -DGLFW_BUILD_EXAMPLES=OFF \
		-DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF && $(MAKE) -C .\bin --no-print-directory
	copy $(EXTDIR)\glfw\bin\src\libglfw3.a $(LIBDIR)


# GLM_BUILD_TESTS=ON/OFF BUILD_SHARED_LIBS(CMAKE DEFINITION)=ON/OFF
$(LIBDIR)\libglm.a:
	cd $(EXTDIR)\glm && if not exist .\bin\libglm.a cmake -S . -B .\bin -G"MinGW Makefiles" -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF && $(MAKE) -C .\bin --no-print-directory
	copy $(EXTDIR)\glm\bin\glm\libglm.a $(LIBDIR)


$(LIBDIR)\glad.o: $(EXTDIR)\glad\bin\glad.o
	copy $^ $(LIBDIR)


$(EXTDIR)\glad\bin\glad.o: $(EXTDIR)\glad\src\glad.c $(EXTDIR)\glad\include\glad\glad.h $(EXTDIR)\glad\include\KHR\khrplatform.h
	@if not exist $(EXTDIR)\glad\bin $(MKDIR) $(EXTDIR)\glad\bin
	$(CC) -o $@ -c $< -std=c$(CVER) -I$(EXTDIR)\glad\include


apollo:
	$(MAKE) -C $(APDIR) --no-print-directory


sandbox:
	$(MAKE) -C $(SBDIR) --no-print-directory


clean-all: clean-lib clean-apollo clean-sandbox


clean-lib:
	$(RMDIR) $(LIBDIR)
	$(RMDIR) $(EXTDIR)\glfw\bin
	$(RMDIR) $(EXTDIR)\glm\bin
	$(RMDIR) $(EXTDIR)\glad\bin

clean-apollo:
	$(MAKE) -C $(APDIR) clean --no-print-directory


clean-sandbox:
	$(MAKE) -C $(SBDIR) clean --no-print-directory


run:
	@$(MAKE) -C $(APDIR) --no-print-directory
	@$(MAKE) -C $(SBDIR) --no-print-directory
	@$(MAKE) -C $(SBDIR) run --no-print-directory


%.c:
%.h: