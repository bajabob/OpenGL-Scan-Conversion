all: polygon.o polygon_manager.o scan_convert.o
	g++ -std=c++11 -Wno-deprecated -framework GLUT -framework OpenGL -framework Cocoa \
	polygon.o \
	polygon_manager.o \
	scan_convert.o -o main

polygon.o: polygon.cpp
	g++ -std=c++11 -c polygon.cpp

polygon_manager.o: polygon_manager.cpp
	g++ -std=c++11 -c polygon_manager.cpp
	
scan_convert.o: scan_convert.cpp
	g++ -std=c++11 -c scan_convert.cpp
	
clean:
	rm *.o main
