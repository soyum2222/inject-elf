package main

import (
	"fmt"
	"os"
)

func main() {

	if len(os.Args) < 3 {
		return
	}

	path := os.Args[1]

	f, err := os.ReadFile(path)
	if err != nil {
		return
	}

	tag := os.Args[2]

	fmt.Print(tag,":\n")
	for _, v := range f {
		fmt.Printf("db 0x%x \n", v)
	}
}
