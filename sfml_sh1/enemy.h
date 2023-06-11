#pragma once
#include "settings.h"
class Enemy
{
public:
	Enemy(sf::Vector2f pos);
	void update(sf::Vector2f pos);
	sf::FloatRect getHitbox() { return sprite.getGlobalBounds(); }
	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
		for (auto laser : lasers) {
			laser->draw(window);
		}
	}
	void hit() { m_hit = true; }
	bool get_hit() { return m_hit; }
	bool isToDel();
	void setDel();
	void fire(sf::Vector2f pos) {
		/*int currTime = timer.getElapsedTime().asMilliseconds();
		if (currTime - prevFireTime > FIRE_COOLDOWN) {
			int now = timer.getElapsedTime().asMilliseconds();

			auto laser = new Laser(pos.x, pos.y, enemyLaser_file_name);
			lasers.push_back(laser);


		}*/
	}

	void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
private:
	sf::Sprite sprite;
	sf::Texture texture;
	bool m_hit = false;
	bool del = false;
	std::list<Laser*> lasers;
	sf::Clock timer;
	
	int  prevFireTime;
};

Enemy::Enemy(sf::Vector2f pos)
{
	texture.loadFromFile(enemy_file_name);
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	sprite.setScale(3, 3);
	timer.restart();
	prevFireTime = timer.getElapsedTime().asMilliseconds();
}
void Enemy::update(sf::Vector2f pos){
	fire(pos);
	/*for (auto laser : lasers) {
		laser->update(Laser_speed);
	}*/
	sprite.move(0, 0.1);
}



bool Enemy::isToDel() { return del; }


void Enemy::setDel() { del = true; }