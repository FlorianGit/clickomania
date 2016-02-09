CXX = g++

objects = coorclass.o gridclass.o

clickomania : $(objects)
	$(CXX) -std=c++11 clickomania.cpp $(objects)

coorclass.o : coorclass.h
	$(CXX) -c coorclass.cpp gridclass.cpp

gridclass.o : gridclass.h
	$(CXX) -c gridclass.cpp
