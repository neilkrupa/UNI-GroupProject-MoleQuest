#ifndef MOLE_SPAWNER_H_
#define MOLE_SPAWNER_H_

#include "Player.h"

class MoleSpawner {
public:
  MoleSpawner(Player*);
  ~MoleSpawner();

  void Update(int lag, int level);

private:
  struct MolesPerLevel {
    int normal;
    int ranged;
    int heavy;
    int fast;
  };

  std::vector<MolesPerLevel> levels_;

  void SpawnNormal(int amount, int level);
  void SpawnHeavy(int, int level);
  void SpawnFast(int, int);
  void SpawnRanged(int, int);

  float time_passed = 3.0f;
  float spawn_time = 6;

  Player* player_;
};

#endif