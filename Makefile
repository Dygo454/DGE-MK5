commit ?= Unspecified Commit
PROGRAM = main.cpp
OUTPUT = UntitledGam
SOURCES = src/OS/*.cpp src/OS/Windows/*.cpp src/Error/*.cpp src/Input/*.cpp
LIBRARIES = -L${OPENCL_LIB} -lWin32\OpenCL -lgdi32 -static-libgcc -static-libstdc++
INCLUDES = -I${OPENCL_INCLUDE}
CFLAGS = -std=c++11 -msse2 -O2

all:
	windres my.rc -O coff -o my.res
	g++ -DDEBUG=1 $(CFLAGS) $(PROGRAM) $(SOURCES) -o $(OUTPUT) $(INCLUDES) $(LIBRARIES)

release:
	windres my.rc -O coff -o my.res
	g++ -mwindows $(CFLAGS) $(PROGRAM) $(SOURCES) -o $(OUTPUT) $(INCLUDES) $(LIBRARIES)

github-nocompile:
	git add *
	git commit -m "$(commit)"
	git push -u origin main --force

restore:
	git fetch
	git stash save
	git pull --hard
