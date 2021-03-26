package main

import (
	"debug/elf"
	"io/ioutil"
	"os"
	"strconv"
	"unsafe"
)

func LoadHeader(f []byte) *elf.Header64 {
	h := (*elf.Header64)(unsafe.Pointer(&f[0]))
	return h
}
func main() {

	if len(os.Args) < 4 {
		return
	}

	f, err := ioutil.ReadFile(os.Args[1])
	if err != nil {
		panic(err)
	}


	h := LoadHeader(f)
	entry, _ := strconv.ParseInt(os.Args[2], 0, 64)
	h.Entry = uint64(entry)

	out, err := os.Create(os.Args[3])
	if err != nil {
		panic(err)
	}

	out.Write(f)
}

func CheckBits(f []byte) byte {
	return f[4]
}
