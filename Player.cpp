#include "include/Player.hpp"

Player::Player( const glm::vec3& pos, const glm::vec3& frnt, float p, float y )
: Camera( pos, frnt, p, y )
{
	lowLimit = pos - glm::vec3( BLOCK_SIZE * 4, BLOCK_SIZE * 4, BLOCK_SIZE * 4 );
	highLimit = pos + glm::vec3( BLOCK_SIZE * 4, BLOCK_SIZE * 4, BLOCK_SIZE * 4 );
	life = true;
}

void Player::CheckPosition( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ] ) {
	if ( position.x < lowLimit.x ) { 
		position.x += BLOCK_SIZE * 4; 
		
		bool mapCopy[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ];
		
		for ( int y = 0; y < MAP_SIZE; y++ ) {
			for ( int z = 0; z < MAP_SIZE; z++ ) {
				for ( int x = 0; x < MAP_SIZE; x++ ) {
					mapCopy[ x ][ y ][ z ] = false;
				}
				
				for ( int x = 4; x < MAP_SIZE; x++ ) {
					mapCopy[ x ][ y ][ z ] = map[ x - 4 ][ y ][ z ];
				}
				
				for ( int x = 0; x < 4; x++ ) {
					if ( rand() % 5 == 0 ) {
						mapCopy[ x ][ y ][ z ] = true;
					}
				}
				
				for ( int x = 0; x < MAP_SIZE; x++ ) {
					map[ x ][ y ][ z ] = mapCopy[ x ][ y ][ z ];
				}
			}
		}
	}
	if ( position.x > highLimit.x ) { 
		position.x -= BLOCK_SIZE * 4; 
		
		bool mapCopy[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ];
		
		for ( int y = 0; y < MAP_SIZE; y++ ) {
			for ( int z = 0; z < MAP_SIZE; z++ ) {
				for ( int x = 0; x < MAP_SIZE; x++ ) {
					mapCopy[ x ][ y ][ z ] = false;
				}
				
				for ( int x = 0; x < MAP_SIZE - 4; x++ ) {
					mapCopy[ x ][ y ][ z ] = map[ x + 4 ][ y ][ z ];
				}
				
				for ( int x = MAP_SIZE - 4; x < MAP_SIZE; x++ ) {
					if ( rand() % 5 == 0 ) {
						mapCopy[ x ][ y ][ z ] = true;
					}
				}
				
				for ( int x = 0; x < MAP_SIZE; x++ ) {
					map[ x ][ y ][ z ] = mapCopy[ x ][ y ][ z ];
				}
			}
		}
	}
	
	if ( position.y < lowLimit.y ) { 
		position.y += BLOCK_SIZE * 4; 
		
		bool mapCopy[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ];
		
		for ( int x = 0; x < MAP_SIZE; x++ ) {
			for ( int z = 0; z < MAP_SIZE; z++ ) {
				for ( int y = 0; y < MAP_SIZE; y++ ) {
					mapCopy[ x ][ y ][ z ] = false;
				}
				
				for ( int y = 4; y < MAP_SIZE; y++ ) {
					mapCopy[ x ][ y ][ z ] = map[ x ][ y - 4 ][ z ];
				}
				
				for ( int y = 0; y < 4; y++ ) {
					if ( rand() % 5 == 0 ) {
						mapCopy[ x ][ y ][ z ] = true;
					}
				}
				
				for ( int y = 0; y < MAP_SIZE; y++ ) {
					map[ x ][ y ][ z ] = mapCopy[ x ][ y ][ z ];
				}
			}
		}
	}
	if ( position.y > highLimit.y ) { 
		position.y -= BLOCK_SIZE * 4; 
		
		bool mapCopy[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ];
		
		for ( int x = 0; x < MAP_SIZE; x++ ) {
			for ( int z = 0; z < MAP_SIZE; z++ ) {
				for ( int y = 0; y < MAP_SIZE; y++ ) {
					mapCopy[ x ][ y ][ z ] = false;
				}
				
				for ( int y = 0; y < MAP_SIZE - 4; y++ ) {
					mapCopy[ x ][ y ][ z ] = map[ x ][ y + 4 ][ z ];
				}
				
				for ( int y = MAP_SIZE - 4; y < MAP_SIZE; y++ ) {
					if ( rand() % 5 == 0 ) {
						mapCopy[ x ][ y ][ z ] = true;
					}
				}
				
				for ( int y = 0; y < MAP_SIZE; y++ ) {
					map[ x ][ y ][ z ] = mapCopy[ x ][ y ][ z ];
				}
			}
		}
	}
	
	if ( position.z < lowLimit.z ) { 
		position.z += BLOCK_SIZE * 4; 
		
		bool mapCopy[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ];
		
		for ( int x = 0; x < MAP_SIZE; x++ ) {
			for ( int y = 0; y < MAP_SIZE; y++ ) {
				for ( int z = 0; z < MAP_SIZE; z++ ) {
					mapCopy[ x ][ y ][ z ] = false;
				}
				
				for ( int z = 4; z < MAP_SIZE; z++ ) {
					mapCopy[ x ][ y ][ z ] = map[ x ][ y ][ z - 4 ];
				}
				
				for ( int z = 0; z < 4; z++ ) {
					if ( rand() % 5 == 0 ) {
						mapCopy[ x ][ y ][ z ] = true;
					}
				}
				
				for ( int z = 0; z < MAP_SIZE; z++ ) {
					map[ x ][ y ][ z ] = mapCopy[ x ][ y ][ z ];
				}
			}
		}
	}
}

bool Player::Collision( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ] ) {
	int mapX = floor( position.x / BLOCK_SIZE );
	int mapY = floor( position.y / BLOCK_SIZE );
	int mapZ = floor( position.z / BLOCK_SIZE );
	
	return map[ mapX ][ mapY ][ mapZ ];
}

void Player::Update( bool map[ MAP_SIZE ][ MAP_SIZE ][ MAP_SIZE ] ) {
	Move( glm::vec3( 0.0f, 0.0f, -speed ) );
	CheckPosition( map );
	
	speed += ACCELERATION;
	
	if ( Collision( map ) ) {
		life = false;
	}
}

void Player::Move( const glm::vec3& mv ) {
    position += mv;
}

bool Player::IsAlive() const {
	return life;
}
