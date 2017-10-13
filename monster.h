
#ifndef JNP1_MONSTER_H
#define JNP1_MONSTER_H

#include <vector>
#include <memory>
#include "helper.h"

class Monster;
class SingleMonster;
class Zombie;
class Vampire;
class Mummy;
class GroupOfMonsters;

using monster_ptr = std::shared_ptr<Monster>;
using single_monster_ptr = std::shared_ptr<SingleMonster>;
using zombie_ptr = std::shared_ptr<Zombie>;
using vampire_ptr = std::shared_ptr<Vampire>;
using mummy_ptr = std::shared_ptr<Mummy>;
using group_ptr = std::shared_ptr<GroupOfMonsters>;

/**
 * Abstract class used to realize interface - 'Component' of composite design pattern
 */
class Monster : public virtual Creature, public virtual Fighter {

  public:
    Monster();

    using Creature::getHealth;
    using Creature::takeDamage;
    using Fighter::getAttackPower;

    /**
     * Get monster name
     * @return string with name of the class of the monster
     */
    virtual std::string getName() const = 0;

    virtual creature_ptr clone() const = 0;
};


/**
 * Class representing a single monster
 * 'Leaf' of composite design pattern
 */
class SingleMonster : public Monster, public SingleCreature, public SingleFighter {
  public:
    SingleMonster(const HealthPoints& healthPoints, const AttackPower& attackPower);

    using SingleCreature::getHealth;
    using SingleCreature::takeDamage;
    using SingleFighter::getAttackPower;
    virtual creature_ptr clone() const = 0;
};


/**
 * Classes representing specific types of a single monster
 */
class Zombie : public SingleMonster {
    static const std::string name;
  public:
    Zombie(const HealthPoints& healthPoints, const AttackPower& attackPower);

    virtual creature_ptr clone() const override;

    std::string getName() const;
};
class Vampire : public SingleMonster{
    static const std::string name;
  public:
    Vampire(const HealthPoints& healthPoints, const AttackPower& attackPower);

    virtual creature_ptr clone() const override;

    std::string getName() const;
};
class Mummy: public SingleMonster{
    static const std::string name;
  public:
    Mummy(const HealthPoints& healthPoints, const AttackPower& attackPower);

    virtual creature_ptr clone() const override;

    std::string getName() const;
};


/**
 * Class representing collection of monsters
 * 'Composite' of composite design pattern
 */
class GroupOfMonsters : public Monster {
    HealthPoints healthPoints;
    AttackPower attackPower;
    static const std::string name;
    std::vector<monster_ptr> monsters;

    /**
     * Calculates health of the GroupOfMonsters
     * @return sum of healths of monsters in group
     */
    HealthPoints calcHealth() const;

    /**
     * Calculates attackPower of the GroupOfMonsters
     * @return sum of attackPowers of monsters in group
     */
    AttackPower calcAttPower() const;
  public:
    GroupOfMonsters(const std::vector<monster_ptr>& monsters);
    GroupOfMonsters(const std::initializer_list<monster_ptr>& monsters);

    /**
     * Gets sum of health of all the monster in group
     */
    HealthPoints getHealth() const;

    /**
     * Gets sum of attackPower of all the monster in group
     */
    AttackPower getAttackPower() const;

    /**
     * Take 'damage' health from every monster in group
     */
    void takeDamage(const AttackPower& damage);

    std::string getName() const;
    virtual creature_ptr clone() const override;
};

zombie_ptr createZombie(const HealthPoints& healthPoints, const AttackPower& attackPower);
vampire_ptr createVampire(const HealthPoints& healthPoints, const AttackPower& attackPower);
mummy_ptr createMummy(const HealthPoints& healthPoints, const AttackPower& attackPower);

group_ptr createGroupOfMonsters(const std::initializer_list<monster_ptr>& newMonsters);
group_ptr createGroupOfMonsters(const std::vector<monster_ptr>& newMonsters);

#endif //JNP1_MONSTER_H
