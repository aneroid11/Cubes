#include "include/Camera.hpp"

Camera::Camera( const glm::vec3& pos, const glm::vec3& frnt, GLfloat p, GLfloat y ) {
	position = pos;
	front = frnt;
	up = glm::vec3( 0.0f, 1.0f, 0.0f );
	pitch = p;
	yaw = y;
	speed = CAMERA_SPEED;
}

void Camera::Set( const Shader& shader ) {
	glm::mat4 viewMatrix;
	viewMatrix = glm::lookAt( position, position + front, up );
	shader.SetMatrix4f( "view", viewMatrix );
		
	glm::mat4 projectionMatrix;
	projectionMatrix = glm::perspective( glm::radians( 60.0f ), ( float )( SCREEN_WIDTH / SCREEN_HEIGHT ), 0.1f, 100.0f );
	shader.SetMatrix4f( "projection", projectionMatrix );
}

void Camera::Rotate( float y, float p ) {
	yaw += y;
	pitch += p;
	
	if ( pitch >= 89.0f ) { pitch = 89.0f; }
	if ( pitch <= -89.0f ) { pitch = -89.0f; }
	
	glm::vec3 direction;
	direction.x = cos( glm::radians( yaw ) ) * cos( glm::radians( pitch ) );
	direction.y = sin( glm::radians( pitch ) );
	direction.z = sin( glm::radians( yaw ) ) * cos( glm::radians( pitch ) );
	
	front = glm::normalize( direction );
}
