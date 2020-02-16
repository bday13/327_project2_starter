#target exe
myexe: Project2.o utilities.o array_functions.o
		g++ $(CFLAGS) -o myexe Project2.o utilities.o array_functions.o
		
array.o: array_functions.cpp array_functions.h
		g++ $(CFLAGS) -c array_functions.cpp
		
utilities.o: utilities.cpp utilities.h
		g++ $(CFLAGS) -c utilities.cpp

Project2.o: Project2.cpp
		g++ $(CFLAGS) -c Project2.cpp
		
clean:
		rm -f *.o myexe
