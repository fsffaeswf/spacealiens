#pragma once
#include "game_obj.h"
#include "settings.h"
#include "cmath"
#include "bullet.h"
#include "list"
class Player:GameObject
{
public:
	Player();
	void update();
	void fire();
	void draw(sf::RenderWindow& window);
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	std::list<Laser*>* getLasers() { return &lasers; }
private:
	std::list<Laser*> lasers;
	sf::Clock timer;
	int  prevFireTime;
};

Player::Player()
{
	texture.loadFromFile(PlayerFileName);
	sprite.setTexture(texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setScale(4, 4);
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);
	sprite.setPosition(window_width / 2, window_height - bounds.height*3);
	timer.restart();
	prevFireTime = timer.getElapsedTime().asMilliseconds();

}
void Player::update(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sprite.move(-Player_speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sprite.move(Player_speed, 0);
	}
	fire();
	for (auto laser : lasers) {
		laser->update(-Laser_speed);
	}

}
void Player::fire() {
	int currTime = timer.getElapsedTime().asMilliseconds();
	if (currTime - prevFireTime > FIRE_COOLDOWN) {
		if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			auto laser = new Laser(sprite.getPosition().x - 24.f, sprite.getPosition().y - 63.f,playerLaser_file_name);
			lasers.push_back(laser);
			prevFireTime = currTime;
		}
	}
}
void Player::draw(sf::RenderWindow& window) { 
	window.draw(sprite);
for (auto laser : lasers) {
	laser->draw(window);
}
};