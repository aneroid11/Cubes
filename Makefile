LIBS = -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lm -ldl
OBJ = main.o Shader.o StbImage.o Game.o Camera.o Player.o
OUTPUT = main
OPTIONS = -std=c++0x 


$(OUTPUT): $(OBJ)
	g++ -o $(OUTPUT) *.o $(LIBS)
	
obj/main.o: main.cpp
	g++ $(OPTIONS) -c -o main.o main.cpp

obj/StbImage.o: StbImage.cpp
	g++ $(OPTIONS) -c -o StbImage.o StbImage.cpp
	
obj/Shader.o: Shader.cpp
	g++ $(OPTIONS) -c -o Shader.o Shader.cpp
	
obj/Game.o: Game.cpp
	g++ $(OPTIONS) -c -o Game.o Game.cpp
	
obj/Camera.o: Camera.cpp
	g++ $(OPTIONS) -c -o Camera.o Camera.cpp
	
obj/Player.o: Player.cpp
	g++ $(OPTIONS) -c -o Player.o Player.cpp

clean:
	rm -rf main *.o
