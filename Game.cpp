#include "include/Game.hpp"

Game::Game()
: player( glm::vec3( ( MAP_SIZE / 2 ) * BLOCK_SIZE + BLOCK_SIZE / 2,
				     ( MAP_SIZE / 2 ) * BLOCK_SIZE + BLOCK_SIZE / 2,
                     ( MAP_SIZE - 1 ) * BLOCK_SIZE + BLOCK_SIZE / 2 ),
          glm::vec3( 0.0f, 0.0f, -1.0f ),
	      0.0f,
	      -90.0f )
{
	srand( time( nullptr ) );
}

void Game::Run() {
	/*char g[ 5 ];
	std::cin >> g;
	*/
	GLFWwindow* window = InitGraphics();
	Shader shader( "VertexShader.glsl", "FragmentShader.glsl" );

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ];
	InitMap( map );

	GLuint texture0;
	LoadTexture( texture0 );

	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	CreateObject( vertices, sizeof ( vertices ), vertexBufferObject, vertexArrayObject );
	
	GLuint score = 0;
	
	while ( !glfwWindowShouldClose( window ) && player.IsAlive() ) {
		glfwPollEvents();

		ProcessKeyboardInput( window );
		//ProcessMouseInput( window );
	
		player.Update( map );
		player.Set( shader );
		score++;

		
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		shader.Use();

		DrawMap( map, shader, vertexArrayObject );
		
		glfwSwapInterval( 1 );
		glfwSwapBuffers( window );

		usleep( 10000 );
	}

	DestroyObject( vertexBufferObject, vertexArrayObject );
	DestroyTexture( texture0 );
	DestroyGraphics( window );
	
	std::cout << "\n\n\n\nYou scored " << score << "\n\n\n\n";
}

void Game::InitMap( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ] ) {
	for ( int x = 0; x < MAP_SIZE; x++ ) {
		for ( int y = 0; y < MAP_SIZE; y++ ) {
			for ( int z = 0; z < MAP_SIZE; z++ ) {
				map[ x ][ y ][ z ] = false;
			}
		}
	}
	
	for ( int z = 0; z < MAP_SIZE; z++ ) {
		map[ 5 ][ 5 ][ z ] = false;
	}
}

void Game::ProcessKeyboardInput( GLFWwindow* window ) {
    glm::vec3 mv = glm::vec3( 0.0f, 0.0f, 0.0f );

	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) {
		glfwSetWindowShouldClose( window, GL_TRUE );
	}
	if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS ) {
        mv += CAMERA_SPEED * player.up;
	}
    if ( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS ) {
        mv -= CAMERA_SPEED * player.up;
	}
	if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS ) {
        mv -= CAMERA_SPEED * glm::normalize( glm::cross( player.front, player.up ) );
	}
	if ( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS ) {
        mv += CAMERA_SPEED * glm::normalize( glm::cross( player.front, player.up ) );
	}

	player.Move( mv );
}

void Game::ProcessMouseInput( GLFWwindow* window ) {
	static float lastX = SCREEN_WIDTH / 2.0f, lastY = SCREEN_HEIGHT / 2.0f;

	double xPos, yPos;
	glfwGetCursorPos( window, &xPos, &yPos );

	float xOffset = xPos - lastX;
	float yOffset = yPos - lastY;
	lastX = xPos;
	lastY = yPos;

	xOffset *= MOUSE_SENSITIVITY;
	yOffset *= MOUSE_SENSITIVITY;

	player.Rotate( xOffset, -yOffset );
}

void Game::SetTextureParameters() {
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

GLFWwindow* Game::InitGraphics() {
	glfwInit();

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	GLFWwindow* window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Eeeeee", nullptr, nullptr );
	//GLFWwindow* window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Eeeeee", glfwGetPrimaryMonitor(), nullptr );
	glfwMakeContextCurrent( window );

	//glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize( window, &width, &height );
	glViewport( 0, 0, width, height );

	glEnable( GL_DEPTH_TEST );

	return window;
}

void Game::DestroyGraphics( GLFWwindow* window ) {
	glfwDestroyWindow( window );
	glfwTerminate();
}

void Game::LoadTexture( GLuint& texture0 ) {
	glGenTextures( 1, &texture0 );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, texture0 );
	SetTextureParameters();

	stbi_set_flip_vertically_on_load( true );
	GLint texWidth, texHeight, hrChannels;
	GLubyte* data = stbi_load( "textures/texture.png", &texWidth, &texHeight, &hrChannels, 0 );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
	glGenerateMipmap( GL_TEXTURE_2D );

	stbi_image_free( data );
}

void Game::DestroyTexture( GLuint& texture0 ) {
	glDeleteTextures( 1, &texture0 );
}

void Game::CreateObject( GLfloat vertices[], size_t size, GLuint& vertexBufferObject, GLuint& vertexArrayObject ) {
	glGenVertexArrays( 1, &vertexArrayObject );
	glGenBuffers( 1, &vertexBufferObject );

	glBindVertexArray( vertexArrayObject );

	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );
	glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid* )nullptr );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid* )( 3 * sizeof( GLfloat ) ) );
	glEnableVertexAttribArray( 1 );

	glBindVertexArray( 0 );
}

void Game::DestroyObject( GLuint& vertexBufferObject, GLuint vertexArrayObject ) {
	glDeleteVertexArrays( 1, &vertexArrayObject );
	glDeleteBuffers( 1, &vertexBufferObject );
}

void Game::DrawMap( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ], const Shader& shader, GLuint vertexArrayObject ) {
	glBindVertexArray( vertexArrayObject );

	shader.SetInt( "texture0", 0 );

	for ( int x = 0; x < MAP_SIZE; x++ ) {
		for ( int y = 0; y < MAP_SIZE; y++ ) {
			for ( int z = 0; z < MAP_SIZE; z++ ) {
				if ( map[ x ][ y ][ z ] ) {
					float xPos = x * BLOCK_SIZE + BLOCK_SIZE / 2;
					float yPos = y * BLOCK_SIZE + BLOCK_SIZE / 2;
					float zPos = z * BLOCK_SIZE + BLOCK_SIZE / 2;
					glm::vec3 pos = glm::vec3( xPos, yPos, zPos );

					glm::mat4 modelMatrix = glm::mat4( 1.0f );
					modelMatrix = glm::translate( modelMatrix, pos );

					shader.SetMatrix4f( "model", modelMatrix );

					glDrawArrays( GL_TRIANGLES, 0, 36 );
				}
			}
		}
	}

	glBindVertexArray( 0 );
}
