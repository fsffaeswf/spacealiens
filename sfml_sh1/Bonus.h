#pragma once
#include "game_obj.h"

class Player;

class Bonus : public GameObject {
public:
	enum BonusType { SHIELD, KABOOM, MAX_BONUS_TYPE };
	Bonus(sf::Vector2f meteorPos, size_t bonusType);
	void update();
	void draw(sf::RenderWindow& window);
	void act(Player& player);
	bool isToDel();
	auto getHitBox();
	void setDel();

private:
	BonusType type;
	sf::Clock timer;
	bool del = false;
};

Bonus::Bonus(sf::Vector2f enemyPos, size_t bonusType) {
	type = (BonusType)bonusType;
	switch (type) {
	case KABOOM:
		texture.loadFromFile("images\\Powerup0.png");
		break;
	}
	//texture.loadFromFile();
	sprite.setTexture(texture);
	sprite.setPosition(enemyPos);
	timer.restart();
}

void Bonus::update() {
	sprite.move(0, 6.f);
	if (sprite.getPosition().x + sprite.getGlobalBounds().height > window_height) {
		del = true;
	}
}

void Bonus::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

bool Bonus::isToDel() { return del; }

auto  Bonus::getHitBox() { return sprite.getGlobalBounds(); }

void Bonus::setDel() { del = true; }

void Bonus::act(Player& player) {
	switch (type) {
	case KABOOM:
		break;
	}
}
