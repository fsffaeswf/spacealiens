#pragma once
#include "settings.h"


class GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	
public:
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	void setPosition(sf::Vector2f pos) { return sprite.setPosition(pos); }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	void draw(sf::RenderWindow& window) { window.draw(sprite); };
};
