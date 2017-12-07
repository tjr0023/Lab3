lab3: tjr0023_3.o Game.o Node.o
	g++ -o lab3 tjr0023_3.o Game.o Node.o
	
tjr0023_3.o: tjr0023_3.cpp Game.h
	g++ -c tjr0023_3.cpp

Game.o: Game.cpp Game.h
	g++ -c Game.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp
