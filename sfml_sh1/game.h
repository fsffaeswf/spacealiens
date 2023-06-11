#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include <vector>
#include "player.h"
#include "enemy.h"
#include "Bonus.h"

class Game {
private:
	sf::RenderWindow window;
	Player player;
	std::list<Enemy*> enemies;
	std::list<Bonus*> bonuses;

public:
	void spawEnemies(size_t n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 4; j++) {
				Enemy* m = new Enemy(sf::Vector2f{ 2 * (i + 1) * 64.f,64 + j * 64.f });
				enemies.push_back(m);
			}
		}
	}
	Game() {
		window.create(sf::VideoMode{ (size_t)window_width,(size_t)window_height }, "f");
		window.setFramerateLimit(60);
		spawEnemies(12);
	}

	void chek_events() {
		sf::Event event;
		while (window.pollEvent(event))
		{
			// ???????????? ????? ?? «???????» ? ????? ??????? ?????
			if (event.type == sf::Event::Closed)
				// ????? ????????? ???
				window.close();
		}
	}

	void update() {
		player.update();
		for (auto& bonus : bonuses) {
			bonus->update();
		}
		for (auto& enemy : enemies) {
			int choice = rand() % 10000;
			if (choice > 5000) {
				enemy->update(enemy->getPosition());
			}
		}
	}

	void chek_collisons() {
		auto laserSprites = player.getLasers();
		sf::FloatRect playerBounds = player.getHitBox();
		for (auto& enemy : enemies) {
			sf::FloatRect enemyBounds = enemy->getHitbox();
			auto laserSprites = player.getLasers();
			for (auto laser : (*laserSprites)) {
				sf::FloatRect laserBounds = laser->getHitBox();
				if (enemyBounds.intersects(laserBounds)) {

					////с каким-то шансом появляется бонус из сбитого метеора
					//size_t chance = rand() % 30000;
					//size_t bonusType = rand() % Bonus::BonusType::MAX_BONUS_TYPE;
					//if (chance < 15000) {
					//	Bonus* bonus = new Bonus(
					//		enemy->getPosition(), bonusType
					//	);
					//	bonuses.push_back(bonus);

					laser->hit();
					enemy->setDel();
				}
			}
			if (enemyBounds.intersects(playerBounds)|| enemy->getPosition().y+enemyBounds.height>window_height) { window.close(); }
		}
		/*for (auto& bonus : bonuses) {
			sf::FloatRect bonusBounds = bonus->getHitBox();
			if (bonusBounds.intersects(playerBounds)) {
				bonus->act(player);
				bonus->setDel();
			}
		}*/
		(*laserSprites).remove_if([](Laser* laser) { return laser->get_hit(); });
		(*laserSprites).remove_if([](Laser* laser) { return laser->offScreen(); });
		enemies.remove_if([](Enemy* enemy) { return enemy->isToDel(); });
		bonuses.remove_if([](Bonus* bonus) { return bonus->isToDel(); });
	}

	void draw() {

		
			window.clear();
			player.draw(window);
			for (auto& enemy : enemies) {
				enemy->draw(window);
			}
			for (auto& bonus : bonuses) {
				bonus->draw(window);
			}
			window.display();
		
	}

	void play() {
		while (window.isOpen())
		{
			chek_events();
			update();
			chek_collisons();
			draw();
		}
	}
};