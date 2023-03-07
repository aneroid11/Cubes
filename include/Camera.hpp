#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

const float CAMERA_SPEED = 0.05f;
const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1080.0f;

class Camera {
public:
	glm::vec3 position, front, up;
	float pitch, yaw, speed;
	
	Camera( const glm::vec3& pos, const glm::vec3& frnt, float p, float y );
	void Set( const Shader& shader );
	void Rotate( float y, float p );
};

#endif //CAMERA_HPP
