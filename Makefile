# List all the drivers
all: openhtdriver orderedhtdriver

openhtdriver: openhttest.cpp
	g++ -std=c++11 -o openhtdriver openhttest.cpp Open_List.cpp
	
orderedhtdriver: orderedhttest.cpp
	g++ -std=c++11 -o orderedhtdriver orderedhttest.cpp Ordered_List.cpp Node.cpp

# List all the executables under 'all:'
clean:
	rm openhtdriver
	rm orderedhtdriver