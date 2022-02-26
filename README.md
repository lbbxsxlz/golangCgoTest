# golangCgoTest
Go语言使用cgo嵌套C语言函数调用demo

## 源码编译
C语言代码和Go语言代码在同一目录下，使用cgo编译，[代码目录](codeCompiler)

## 链接C语言静态库
```
gcc -c elf_section.c -o elf_section.o
ar rcs libelfsection.a elf_section.o
```

### cmake 方式
修改CMakeLists.txt文件，将add_library修改成如下：
```
add_library(elfsection	
	STATIC
	elf_section.c
)

```
然后
```
mkdir -p build;
cd build; cmkae ..
make
```

然后在go代码中使用cgo语句链接静态库，如下，但必须在注释段中
```
#cgo LDFLAGS: -L. amd64/libelfsection.a
```
详见[代码](linkStaticLib/elf.go)


## 链接C语言动态库
```
gcc -shared -fPIC -o libelfsection.so elf_section.c 
```

### cmake 方式
修改CMakeLists.txt文件，将add_library修改成如下：
```
add_library(elfsection
        SHARED
        elf_section.c
)

```
然后
```
mkdir -p build;
cd build; cmkae ..
make
```

然后在go代码中使用cgo语句链接静态库,如下，但必须包含在注释段中
```
//cgo LDFLAGS: -L amd64 -lelfsection
```
详见[代码](linkDynamicLib/elf.go)

## 编译
进入对应的目录，go build即可，例如
```
cd codeCompiler; go build
```

