#pragma once
#include "settings.h"
#include <iostream>
class Laser {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedy;
	bool m_hit = false;
public:
	Laser(float x, float y, std::string name) {
		sprite.setScale(0.7f, 0.7f);
		texture.loadFromFile(name);
		sprite.setTexture(texture);
		sprite.setPosition(x,y);
		sprite.setScale(3, 3);
	}
	void update(float speed) {
		sprite.move(0, speed);
	}

	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	void hit() { m_hit = true; }
	bool get_hit() { return m_hit; }

	auto getPosition() { return sprite.getPosition(); }

	bool offScreen() {
		auto bulletPos = getPosition();
		auto bulletBounds = getHitbox();
		if (bulletPos.x < -bulletBounds.width ||
			bulletPos.x > window_width + bulletBounds.width ||
			bulletPos.y > window_height + bulletBounds.height ||
			bulletPos.y < -bulletBounds.height)
		{
			return true;
		}
		return false;
	}
	sf::Sprite& getSprite() { return sprite; }
	sf::FloatRect getHitbox() { return sprite.getGlobalBounds(); }
	void draw(sf::RenderWindow& window) {window.draw(sprite);}
};
