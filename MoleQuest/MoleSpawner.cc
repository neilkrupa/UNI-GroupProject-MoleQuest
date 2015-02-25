#include "stdafx.h"
#include "MoleSpawner.h"

MoleSpawner::MoleSpawner() {
  // Set up how many types of mole per level there should be

  srand(time(NULL));
  MolesPerLevel level;

  // Level 1
  level.normal = 20 + (rand() % 10);
  level.ranged = 1;
  level.heavy = 0;
  level.fast = 0;
  levels_.push_back(level);

  // Level 2
  level.normal = 25 + (rand() % 10);
  level.ranged = 2;
  level.heavy = 1;
  level.fast = 0;
  levels_.push_back(level);

  // Level 3
  level.normal = 35 + (rand() % 10);
  level.heavy = 2 + (rand() % 2);
  level.fast = 1;
  level.ranged = 0;
  levels_.push_back(level);

  // Level 4
  level.normal = 80 + (rand() % 20);
  level.heavy = 5 + (rand() % 1);
  level.fast = 0;
  level.ranged = 0;
  levels_.push_back(level);

  // Level 5
  level.normal = 50 + (rand() % 30);
  level.fast = 10;
  level.ranged = 7;
  level.heavy = 1;
  levels_.push_back(level);

  // Level 6
  level.normal = 100 + (rand() % 25);
  level.heavy = 15;
  level.ranged = 15;
  level.fast = 15;
  levels_.push_back(level);
}

MoleSpawner::~MoleSpawner() {

}

void MoleSpawner::Update(int lag) {

}