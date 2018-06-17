read: readFuncTest.o readFunc.o formulas.o
	g++ readFuncTest.o readFunc.o formulas.o -o read -lboost_iostreams -lboost_system -lboost_filesystem


readFuncTest.o: readFuncTest.cpp 
	g++ -std=c++11 -c readFuncTest.cpp

readFunc.o: readFunc.cpp
	g++ -std=c++11 -c readFunc.cpp

formulas.o: formulas.cpp
	g++ -std=c++11 -c formulas.cpp

clean:
	rm *.o read
