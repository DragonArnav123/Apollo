GLFW_CMAKE_FLAGS 	?= -DGLFW_LIBRARY_TYPE=STATIC -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF
GLM_CMAKE_FLAGS  	?= -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF
SPDLOG_CMAKE_FLAGS 	?= -DSPDLOG_BUILD_EXAMPLE=OFF
GLAD_FLAGS 			?= 

_LIBDIR 		:= ../$(LIBDIR)
_WLIBDIR 		:= ..\$(LIBDIR)

.PHONY: make-libs clean-all clean-lib clean-libsrc

make-libs: $(_LIBDIR)/libglfw3.a $(_LIBDIR)/libglm.a $(_LIBDIR)/libspdlog.a $(_LIBDIR)/glad.o $(_LIBDIR)/libs-copied-proof

# GLFW_LIBRARY_TYPE=STATIC/SHARED/OBJECT GLFW_BUILD_EXAMPLES=ON/OFF GLFW_BUILD_TESTS=ON/OFF GLFW_BUILD_DOCS=ON/OFF
$(_LIBDIR)/libglfw3.a:
	cd glfw && if not exist ./bin/src/libglfw3.a cmake -S . -B ./bin -G "MinGW Makefiles" $(GLFW_CMAKE_FLAGS) && $(MAKE) -C ./bin --no-print-directory


# GLM_BUILD_TESTS=ON/OFF BUILD_SHARED_LIBS(CMAKE DEFINITION)=ON/OFF
$(_LIBDIR)/libglm.a:
	cd glm && if not exist ./bin/libglm.a cmake -S . -B ./bin -G"MinGW Makefiles"  $(GLM_CMAKE_FLAGS) && $(MAKE) -C ./bin --no-print-directory


$(_LIBDIR)/libspdlog.a:
	cd spdlog && if not exist ./bin/libspdlog.a cmake -S . -B ./bin -G"MinGW Makefiles" $(SPDLOG_CMAKE_FLAGS) && $(MAKE) -C ./bin --no-print-directory


$(_LIBDIR)/glad.o: glad/bin/glad.o


glad/bin/glad.o: glad/src/glad.c glad/include/glad/glad.h glad/include/KHR/khrplatform.h
	if not exist ./glad/bin $(MKDIR) ./glad/bin
	$(CC) -o $@ -c glad/src/glad.c -std=c$(CVER) -Iglad/include $(GLAD_FLAGS)


ifeq ($(PLATFORM), Windows)
$(_LIBDIR)/libs-copied-proof:
	copy .\glfw\bin\src\libglfw3.a $(_WLIBDIR)
	copy .\glm\bin\glm\libglm.a $(_WLIBDIR)
	copy .\glad\bin\glad.o $(_WLIBDIR)
	copy .\spdlog\bin\libspdlog.a $(_WLIBDIR)
	echo > $@

else
$(_LIBDIR)/libs-copied-proof:
	copy glfw/bin/src/libglfw3.a $(_LIBDIR)
	copy glm/bin/glm/libglm.a $(_LIBDIR)
	copy spdlog/bin/libspdlog.a $(_LIBDIR)
	copy glad/bin/glad.o $(_LIBDIR)
	touch $@
endif


clean-all: clean-lib clean-libsrc


clean-lib:
	$(RMDIR) $(_LIBDIR)


ifeq ($(PLATFORM), Windows)
clean-libsrc:
	$(RMDIR) .\glfw\bin
	$(RMDIR) .\glm\bin
	$(RMDIR) .\spdlog\bin
	$(RMDIR) .\glad\bin
else
clean-libsrc:
	$(RMDIR) glfw/bin
	$(RMDIR) glm/bin
	$(RMDIR) spdlog/bin
	$(RMDIR) glad/bin
endif