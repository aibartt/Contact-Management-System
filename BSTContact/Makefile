MyProject: main.o ContactBST.o contact.o MyVector.o
	  g++ main.o ContactBST.o contact.o MyVector.o -o MyProject

main.o: main.cpp
	g++ -c main.cpp

ContactBST.o: ContactBST.cpp ContactBST.h
	g++ -c ContactBST.cpp

contact.o: contact.cpp contact.h
	g++ -c contact.cpp

MyVector.o: MyVector.cpp MyVector.h
	g++ -c MyVector.cpp

clean :
	rm MyProject *.o 