read: main.o readFunc.o formulas.o subClass.o
	g++ main.o readFunc.o formulas.o subClass.o -o read -lboost_iostreams -lboost_system -lboost_filesystem


main.o: main.cpp 
	g++ -std=c++11 -c main.cpp

readFunc.o: readFunc.cpp
	g++ -std=c++11 -c readFunc.cpp

formulas.o: formulas.cpp
	g++ -std=c++11 -c formulas.cpp

subClass.o: subClass.cpp
	g++ -std=c++11 -c subClass.cpp

clean:
	rm *.o read
