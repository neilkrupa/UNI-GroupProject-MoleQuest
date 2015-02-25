#include "stdafx.h"
#include "MoleSpawner.h"
#include "NormalMole.h"
#include "FastMole.h"
#include "HeavyMole.h"
#include "RangeMole.h"
#include "GameObjectManager.h"

MoleSpawner::MoleSpawner(Player* player) {
  player_ = player;

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

void MoleSpawner::Update(int lag, int level) {
  time_passed += lag / 1000.f;

  // -1 to take in to account for vectors being 0 based but levels start at 1
  level--;

  int amount = 0;

  // Work out amount of moles to spawn this update
  if (time_passed > 10) {
    amount = 3 * (level+1);
    time_passed = 0;
  }

  // Spawn moles
  if (amount > 0) {
    SpawnNormal(amount, level);
    SpawnHeavy(amount, level);
    SpawnFast(amount, level);
    SpawnRanged(amount, level);
  }
}

void MoleSpawner::SpawnFast(int amount, int level) {
  // Check amount is a valid number of moles this level has left to spawn
  amount = amount > levels_[level].fast ? levels_[level].fast : amount;

  for (int i = 0; i < amount; i++) {
    FastMole* mole = new FastMole(player_);
    mole->SetObjectType(GameObject::kMole);
    GameObjectManager::Add(mole);
  }

  levels_[level].fast -= amount;
}

void MoleSpawner::SpawnNormal(int amount, int level) {
  amount = amount > levels_[level].normal ? levels_[level].normal : amount;

  for (int i = 0; i < amount; i++) {
    NormalMole* mole = new NormalMole(player_);
    mole->SetObjectType(GameObject::kMole);
    GameObjectManager::Add(mole);
  }

  levels_[level].normal -= amount;
}

void MoleSpawner::SpawnHeavy(int amount, int level) {
  amount = amount > levels_[level].heavy ? levels_[level].heavy : amount;

  for (int i = 0; i < amount; i++) {
    HeavyMole* mole = new HeavyMole(player_);
    mole->SetObjectType(GameObject::kMole);
    GameObjectManager::Add(mole);
  }

  levels_[level].heavy -= amount;
}

void MoleSpawner::SpawnRanged(int amount, int level) {
  amount = amount > levels_[level].ranged ? levels_[level].ranged : amount;

  for (int i = 0; i < amount; i++) {
    RangeMole* mole = new RangeMole(player_);
    mole->SetObjectType(GameObject::kMole);
    GameObjectManager::Add(mole);
  }

  levels_[level].ranged -= amount;
}