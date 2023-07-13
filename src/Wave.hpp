#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.hpp"

class Wave {
	private:
		std::vector<Enemy> enemies;
		bool waveOver = false;
		int id;
	public:
		Wave (int number = 0) {
			id = number;
		}
		
		bool isWaveOver () {
			return enemies.empty ();
		}
		

};