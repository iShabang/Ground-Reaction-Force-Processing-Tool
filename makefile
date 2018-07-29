edpt: main.o readFunc.o formulas.o subClass.o
	g++ -g main.o readFunc.o formulas.o subClass.o -o edpt -lboost_iostreams -lboost_system -lboost_filesystem


main.o: main.cpp 
	g++ -std=c++11 -g -c main.cpp

readFunc.o: readFunc.cpp
	g++ -std=c++11 -g -c readFunc.cpp

formulas.o: formulas.cpp
	g++ -std=c++11 -g -c formulas.cpp

subClass.o: subClass.cpp
	g++ -std=c++11 -g -c subClass.cpp

clean:
	rm *.o read
