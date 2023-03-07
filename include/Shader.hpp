#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    unsigned int id;
  
    Shader( const char* vertexPath, const char* fragmentPath );
    
    void Use();
    
    void SetBool( const std::string& name, bool value ) const;  
    void SetInt( const std::string& name, int value ) const;   
    void SetFloat( const std::string& name, float value ) const;
    void SetMatrix4f( const std::string& name, const glm::mat4& value ) const;
};

#endif //SHADER_HPP
