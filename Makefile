CXX = g++

objects = Coor.o Grid.o helper.o findMove.o testSolver.o

clickomania : $(objects)
	$(CXX) -std=c++11 -g clickomania.cpp $(objects) Block.h Group.h

Coor.o : Coor.cpp
	$(CXX) -std=c++11 -c -ggdb Coor.cpp Coor.h

Grid.o : Grid.cpp
	$(CXX) -std=c++11 -c -ggdb Grid.cpp Grid.h Group.h Coor.h Block.h

helper.o : helper.cpp
	$(CXX) -std=c++11 -c -ggdb helper.cpp helper.h

findMove.o : findMove.cpp
	$(CXX) -std=c++11 -c -ggdb findMove.cpp findMove.h

testSolver.o : testSolver.cpp
	$(CXX) -std=c++11 -c -ggdb testSolver.cpp testSolver.h findMove.h Grid.h Coor.h
