CXX = g++

objects = Coor.o Grid.o helper.o findMove.o

clickomania : $(objects)
	$(CXX) -std=c++11 clickomania.cpp $(objects) Block.h Group.h

Coor.o : Coor.cpp
	$(CXX) -std=c++11 -c Coor.cpp Coor.h

Grid.o : Grid.cpp
	$(CXX) -std=c++11 -c Grid.cpp Grid.h Group.h Coor.h Block.h

helper.o : helper.cpp
	$(CXX) -std=c++11 -c helper.cpp helper.h

findMove.o : findMove.cpp
	$(CXX) -std=c++11 -c findMove.cpp findMove.h
