# golangCgoTest
Go语言使用cgo嵌套C语言函数调用demo

## 源码编译
C语言代码和Go语言代码在同一目录下，使用cgo编译，[代码目录](codeCompiler)

## 链接C语言静态库
```
gcc -c elf_section.c -o elf_section.o
ar rcs libelfsection.a elf_section.o
```

然后在go代码中使用cgo语句链接静态库，在注释段中
```
//#cgo LDFLAGS: -L. amd64/libelfsection.a
```
详见[代码](linkStaticLib/elf.go)

## 链接C语言动态库
```
gcc -shared -fPIC -o libelfsection.so elf_section.c 
```
然后在go代码中使用cgo语句链接静态库
```
//cgo LDFLAGS: -L amd64 -lelfsection
```
详见[代码](linkDynamicLib/elf.go)

