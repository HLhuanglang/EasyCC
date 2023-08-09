CXX      := g++
CXXFLAGS := -ggdb -std=c++17 -I./src
COMPILE  := $(CXX) $(CXXFLAGS) $(CPPFLAGS)
SRCS	 := $(wildcard ./*.cpp ./src/*.cpp)
TARGET   := build/cpplox

.PHONY:build
build:
	$(COMPILE) $(SRCS) -o ${TARGET}

.PHONY: clean
clean:
	rm -f ${TARGET}

.PHONY: test
test:build
	@echo "testing cpplox with test-lexing.lox ..."
	@${TARGET} tests/test-lexing.lox | diff -u --color tests/test-lexing.lox.expected -;
