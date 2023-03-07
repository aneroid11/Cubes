#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <cmath>
#include <cstdlib>

#include <unistd.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "Shader.hpp"
#include "Player.hpp"
#include "Map.hpp"

const float MOUSE_SENSITIVITY = 0.1f;

class Game {
public:
	Game();
	void Run();

private:
	Player player;
	
	void InitMap( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ] );
	void DrawMap( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ], const Shader& shader, GLuint vertexArrayObject );
	
	void ProcessKeyboardInput( GLFWwindow* window );
	void ProcessMouseInput( GLFWwindow* window );
	
	GLFWwindow* InitGraphics();
	void DestroyGraphics( GLFWwindow* window );
	
	void LoadTexture( GLuint& texture0 );
	void DestroyTexture( GLuint& texture0 );
	void SetTextureParameters();
	
	void CreateObject( GLfloat vertices[], size_t size, GLuint& vertexBufferObject, GLuint& vertexArrayObject );
	void DestroyObject( GLuint& vertexBufferObject, GLuint vertexArrayObject );
	void DrawObjects( const Shader& shader, glm::vec3 objects[], GLuint num, GLuint vertexArrayObject );
};

#endif //GAME_HPP
