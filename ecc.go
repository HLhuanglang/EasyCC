package main

import (
	"compiler"
	"linker"
)

func main() {
	linker.Link()
	compiler.Compile()
}
