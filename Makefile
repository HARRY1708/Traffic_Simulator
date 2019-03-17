all: Simulation

Simulation: simulation.o
	g++ -o sim simulation.o -lglut -lGL -lGLEW -lGLU
simulation.o: simulation.cpp
	g++ -c simulation.cpp  -lglut -lGL -lGLEW -lGLU 	
Initializer.o: Initializer.cpp
	g++ -c Initializer.cpp 
debug:
	g++ -g simulation.cpp Initializer.cpp -lglut -lGL -lGLEW -lGLU
run:
	./sim
clean:
	rm *.o Simulation      	
