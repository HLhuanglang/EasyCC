##封装一些功能
MAKE  = make --no-print-directory
MAKEF = $(MAKE) -f makefile.in
MKDIR = -mkdir -p 2>/dev/null
CP    = -cp -r 2>/dev/null
RM    = -rm -r 2>/dev/null

#============================================================
# 通用编译步骤
#============================================================
.PHONY: default
default:
	@echo "Usage: make type=[type] [action]"
	@echo "--[type  ]: interpreter, vm, compiler"
	@echo "--[action]: build, clean, test"

.PHONY: all
all: interpreter vm compiler

.PHONY: premake
premake:
	mkdir -p cc/${type}/build


#============================================================
# 编译cc
#============================================================
type=""

.PHONY: build
build: premake
	@${MAKE} -C cc/${type}

.PHONY: test
test:
	@${MAKE} -C cc/${type} test

.PHONY: clean
clean:
	@${MAKE} -C cc/${type} clean
