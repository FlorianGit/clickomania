CXX = g++

objects = Coor.o Grid.o Group.o

clickomania : $(objects)
	$(CXX) -std=c++11 clickomania.cpp $(objects)

Coor.o : Coor.cpp
	$(CXX) -std=c++11 -c Coor.cpp Coor.h

Grid.o : Grid.cpp
	$(CXX) -std=c++11 -c Grid.cpp Grid.h Group.h Coor.h
