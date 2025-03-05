commit ?= Unspecified Commit
MAX_RASTER_DEPTH ?= 10
PROGRAM = main.cpp
OUTPUT = UntitledGam
SOURCES = src/OS/*.cpp src/OS/Windows/*.cpp src/Error/*.cpp src/Input/*.cpp src/Time/*.cpp src/Rendering/RendPipeline/*.cpp src/Rendering/CLManagement/*.cpp  src/Rendering/Shaders/Default/*.cpp
LIBRARIES = -L${OPENCL_LIB} -lx64\OpenCL -lgdi32 -static-libgcc -static-libstdc++
INCLUDES = -I${OPENCL_INCLUDE}
CFLAGS = -std=c++11 -msse2 -O2

all:
	windres my.rc -O coff -o my.res
	g++ -DDEBUG=1 -DMAX_RASTER_DEPTH=\"$(MAX_RASTER_DEPTH)\" $(CFLAGS) $(PROGRAM) $(SOURCES) -o $(OUTPUT) $(INCLUDES) $(LIBRARIES)

release:
	windres my.rc -O coff -o my.res
	g++ -mwindows $(CFLAGS) $(PROGRAM) $(SOURCES) -o $(OUTPUT) $(INCLUDES) $(LIBRARIES)

github-nocompile:
	git add *
	git commit -m "$(commit)" -a
	git push

restore:
	git fetch
	git stash save
	git pull --hard
