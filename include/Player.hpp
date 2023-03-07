#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Camera.hpp"
#include "Map.hpp"

const float ACCELERATION = 0.00001f;

class Player : public Camera {
public:
	Player( const glm::vec3& pos, const glm::vec3& frnt, float p, float y );
	void Update( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ] );
	void CheckPosition( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ] );
	void Move( const glm::vec3& mv );
	bool IsAlive() const;

private:
	glm::vec3 highLimit;
	glm::vec3 lowLimit;
	bool life;
	
	bool Collision( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ] );
};

#endif //PLAYER_HPP
