all: scan_convert.o
	g++ -std=c++11 -Wno-deprecated -framework GLUT -framework OpenGL -framework Cocoa \
	scan_convert.o -o main
	
scan_convert.o: scan_convert.cpp
	g++ -std=c++11 -c scan_convert.cpp
	
clean:
	rm *.o main
