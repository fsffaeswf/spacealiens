#pragma once
#include <SFML/Graphics.hpp>
const float window_height = 720;
const float window_width = 1280;

std::string PlayerFileName{ "images\\Player.png" };
std::string playerLaser_file_name{ "images\\PlayerBullet.png" };
std::string enemy_file_name{ "images\\Enemy.png" }; 
std::string enemyLaser_file_name{ "images\\enemylaser.png" };

const int FIRE_COOLDOWN = 800;

const float Player_speed = 6.f;
const float Laser_speed = 10.f;