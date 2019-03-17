CPP = g++
CPPFLAGS = -Wall -std=c++11
LIBDIR  = -L/usr/lib/

LIBRARIES =  -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

all: main clean

main: city.o main.o builings.o
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBDIR) $(LIBRARIES)

%.o : %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $(LIBDIR) $< $(LIBRARIES)

clean:
	rm -f *~ *# *.o

clean-all: clean
	rm -f main
