#ifndef MOLE_SPAWNER_H_
#define MOLE_SPAWNER_H_

class MoleSpawner {
public:
  MoleSpawner();
  ~MoleSpawner();

  void Update(int lag);

private:
  struct MolesPerLevel {
    int normal;
    int ranged;
    int heavy;
    int fast;
  };

  std::vector<MolesPerLevel> levels_;
};

#endif