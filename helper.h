
#ifndef JNP1_HELPER_H
#define JNP1_HELPER_H
#include <type_traits>
#include <string>
#include <memory>

class Status;
class AgeIntervalChecker;
class Creature;
class Fighter;

using creature_ptr = std::shared_ptr<Creature>;


/**
 * We use const references to these types so that the functions
 * stay effective in case these are redefined.
 */
using HealthPoints = unsigned long;
using AttackPower = unsigned long;
using Age = unsigned long;
using Time = unsigned long;


class Status {
    std::string monsterName;
    HealthPoints monsterHealth;
    unsigned long aliveCitizens;
  public:
    Status(const std::string& monsterName, const HealthPoints& monsterHealth,
           unsigned long aliveCitizens);

    std::string getMonsterName() const;
    HealthPoints getMonsterHealth() const;
    unsigned long getAliveCitizens() const;
};

/**
 * Class responsible for checking if a number is in a given (constant) interval.
 * Used for checking ages of citizens.
 */
class AgeIntervalChecker{
    Age min; Age max;
  public:
    AgeIntervalChecker(Age min, Age max);
    inline bool isInside(Age x) const { return x >= min && x <= max; }
};

class Creature {
  public:
    Creature();

    virtual HealthPoints getHealth() const = 0;
    virtual void takeDamage(const AttackPower& damage) = 0;

    // Virtual copy ctor
    virtual creature_ptr clone() const = 0;

    virtual ~Creature() {};
};

class SingleCreature : public virtual Creature {
    HealthPoints healthPoints;

  public:
    SingleCreature(const HealthPoints& healthPoints);

    virtual HealthPoints getHealth() const override;
    virtual void takeDamage(const AttackPower& damage) override;

    virtual creature_ptr clone() const = 0;
};

class Fighter {
  public:
    Fighter();

    virtual AttackPower getAttackPower() const = 0;

    virtual ~Fighter() {};
};

class SingleFighter : public virtual Fighter {
    AttackPower attackPower;

  public:
    SingleFighter(const AttackPower& attackPower);

    virtual AttackPower getAttackPower() const override;

};

#endif //JNP1_HELPER_H
