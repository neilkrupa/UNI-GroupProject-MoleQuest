#ifndef MOLE_SPAWNER_H_
#define MOLE_SPAWNER_H_

class MoleSpawner {
public:
  MoleSpawner();
  ~MoleSpawner();

  void Update(int lag);

private:
  struct MolesPerLevel {
    int normal = 0;
    int ranged = 0;
    int heavy = 0;
    int fast = 0;
  };

  std::vector<MolesPerLevel> levels_;
};

#endif