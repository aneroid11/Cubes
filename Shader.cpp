#include "include/Shader.hpp"

Shader::Shader( const char* vertexPath, const char* fragmentPath ) {
	std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    vShaderFile.open( vertexPath);
    fShaderFile.open( fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();		
    
    vShaderFile.close();
    fShaderFile.close();
    
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();	
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    GLuint vertex, fragment;

	vertex = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertex, 1, &vShaderCode, nullptr );
	glCompileShader( vertex );
	
	fragment = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragment, 1, &fShaderCode, nullptr );
	glCompileShader( fragment );
  
	id = glCreateProgram();
	glAttachShader( id, vertex );
	glAttachShader( id, fragment );
	glLinkProgram( id );
	
	glDeleteShader( vertex );
	glDeleteShader( fragment );
}

void Shader::Use() {
	glUseProgram( id );
}

void Shader::SetBool( const std::string& name, bool value ) const {         
    glUniform1i( glGetUniformLocation( id, name.c_str() ), ( int )value ); 
}

void Shader::SetInt( const std::string& name, int value ) const { 
    glUniform1i( glGetUniformLocation( id, name.c_str() ), value ); 
}

void Shader::SetFloat( const std::string& name, float value ) const { 
    glUniform1f( glGetUniformLocation( id, name.c_str() ), value ); 
} 

void Shader::SetMatrix4f( const std::string& name, const glm::mat4& value ) const {
	GLint location = glGetUniformLocation( id, name.c_str() );
	glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr( value ) );
}
