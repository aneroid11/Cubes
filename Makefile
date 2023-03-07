LIBS = -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lm -ldl
OBJ = main.o Shader.o StbImage.o Game.o Camera.o Player.o
OUTPUT = main
OPTIONS = -std=c++0x 


$(OUTPUT): obj/main.o obj/StbImage.o obj/Shader.o obj/Game.o obj/Camera.o obj/Player.o
	g++ -o $(OUTPUT) obj/*.o $(LIBS)
	
	
obj/main.o: main.cpp object
	g++ $(OPTIONS) -c -o obj/main.o main.cpp

obj/StbImage.o: StbImage.cpp object
	g++ $(OPTIONS) -c -o obj/StbImage.o StbImage.cpp
	
obj/Shader.o: Shader.cpp object
	g++ $(OPTIONS) -c -o obj/Shader.o Shader.cpp
	
obj/Game.o: Game.cpp object
	g++ $(OPTIONS) -c -o obj/Game.o Game.cpp
	
obj/Camera.o: Camera.cpp object
	g++ $(OPTIONS) -c -o obj/Camera.o Camera.cpp
	
obj/Player.o: Player.cpp object
	g++ $(OPTIONS) -c -o obj/Player.o Player.cpp

object:
	mkdir obj

clean:
	rm -rf obj main
