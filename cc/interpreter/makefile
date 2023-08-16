CXX      	 := g++
CXXFLAGS 	 := -ggdb -std=c++17 -I./src

COMPILE  	 := $(CXX) $(CXXFLAGS)
CPPLOXSRCS	 := $(wildcard ./*.cpp ./src/*.cpp)
CPPLOX   	 := build/cpplox


.PHONY:build
build:
	$(COMPILE) $(CPPLOXSRCS) -o ${CPPLOX}

.PHONY:tools
tools:
	$(COMPILE) ./tools/gen_ast.cpp -o build/gen_ast

.PHONY: clean
clean:
	rm -f ${CPPLOX}

.PHONY: test
test:build
	@echo "testing cpplox with test-lexing.lox ..."
	@${CPPLOX} tests/test-lexing.lox | diff -u --color tests/test-lexing.lox.expected -;
