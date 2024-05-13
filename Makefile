CC 				:= gcc
CXX 			:= g++

MKDIR 			:= md
RMDIR		 	:= rd /s /q
DELFILE 		:= 

APDIR 			:= apollo
SBDIR 			:= sandbox
EXTDIR 			:= library
LIBDIR 			:= libs

CVER 			?= 11
CXXVER 			?= 20
PLATFORM 		?= Windows

CONFIG 			?= DEBUG

INCLUDES 		:= -I$(EXTDIR)/glfw/include -I$(EXTDIR)/glm -I$(EXTDIR)/glad/include -I$(EXTDIR)/spdlog/include

CFLAGS 			:= -DAPOLLO_CXX_STANDARD=$(CXXVER) -DAPOLLO_C_STANDARD=$(CVER)
# CFLAGS 			+= -I$(EXTDIR)/glfw/include -I$(EXTDIR)/glm -I$(EXTDIR)/glad/include -I$(EXTDIR)/spdlog/include
CFLAGS 			+= -DAPOLLO_CONFIG_$(CONFIG)

EXEPARAMS 		?= "DefWorld"

ifeq ($(PLATFORM), Windows)
	CFLAGS 		+= -DAPOLLO_PLATFORM_WINDOWS
	DELFILE 	:= del /S /Q
endif

ifeq ($(CXXVER), 20)
	CFLAGS 		+= -std=c++2a
else
	CFLAGS 		+= -std=c++$(CXXVER)
endif

ifeq ($(CONFIG), DEBUG)
	CFLAGS += -g
else
	CFLAGS += -s
endif

export CC
export CXX
export MKDIR
export RMDIR
export DELFILE
export APDIR
export SBDIR
export EXTDIR
export LIBDIR
export CVER
export CXXVER
export CFLAGS
export PLATFORM
export CONFIG
export INCLUDES
export EXEPARAMS

default_target: all


.PHONY: all libraries libs md-lib clean-all clean-apollo clean-sandbox clean-lib run apollo sandbox


all: libraries apollo sandbox


libraries: md-lib libs


libs:
	@$(MAKE) -C $(EXTDIR) -flibrary.mk --no-print-directory


md-lib:
	@if not exist $(LIBDIR) $(MKDIR) $(LIBDIR)


apollo:
	@echo Making apollo
	@$(MAKE) -C $(APDIR) -fapollo.mk --no-print-directory


sandbox:
	@echo Making sandbox
	@$(MAKE) -C $(SBDIR) -fsandbox.mk --no-print-directory


clean-all: clean-lib clean-apollo clean-sandbox


clean-lib:
	$(MAKE) clean -C $(EXTDIR) -flibrary.mk --no-print-directory

clean-apollo:
	$(MAKE) clean -C $(APDIR) -fapollo.mk --no-print-directory


clean-sandbox:
	$(MAKE) clean -C $(SBDIR) -fsandbox.mk --no-print-directory


run:
	@$(MAKE) run -C $(SBDIR) -fsandbox.mk --no-print-directory


%.c:
%.h: