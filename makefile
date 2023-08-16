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
	@echo "Usage: make build type=[type] action=[action]"
	@echo "--[type  ]: interpreter, vm, compiler"
	@echo "--[action]: build, clean, test, tools"

.PHONY: premake
premake:
	${MKDIR} cc/${type}/build

#============================================================
# 编译cc
#============================================================
type=""
action=""

.PHONY:build 
build: premake
	@${MAKE} -C cc/${type} ${action}
