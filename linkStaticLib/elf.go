package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"os"
)

/*
#include <stdlib.h>
#include "elf_section.h"
#cgo LDFLAGS: -L. amd64/libelfsection.a
*/
import "C"
import "unsafe"

func main() {
	fmt.Printf("args: %s ", os.Args[0])
	fmt.Println(os.Args[1])
	fileName := C.CString(os.Args[1])
	sectionName := C.CString(".uuid")

	defer C.free(unsafe.Pointer(fileName))
	defer C.free(unsafe.Pointer(sectionName))

	ptr := C.malloc(128)
	defer C.free(unsafe.Pointer(ptr))
	ret := C.findSection(fileName, sectionName, (*C.char)(ptr))
	if ret < 0 {
		log.Fatal("call c func fail \n")
	}

	data := C.GoBytes(ptr, 128)
	err := ioutil.WriteFile("uuid.txt", data, 0666)
	if err != nil {
		log.Fatal("create file fail \n")
	}
}
