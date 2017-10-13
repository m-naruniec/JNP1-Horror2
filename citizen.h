
#ifndef JNP1_CITIZEN_H
#define JNP1_CITIZEN_H

#include <type_traits>
#include <memory>
#include "helper.h"
#include "monster.h"


class Citizen;
class Adult;
class Teenager;
class Sheriff;

using citizen_ptr = std::shared_ptr<Citizen>;
using adult_ptr = std::shared_ptr<Adult>;
using teenager_ptr = std::shared_ptr<Teenager>;
using sheriff_ptr = std::shared_ptr<Sheriff>;

class Citizen : public SingleCreature {
    Age age;
  public:
    Citizen(const HealthPoints& healthPoints, const Age& age);

    using Creature::getHealth;
    using Creature::takeDamage;
    Age getAge() const;
    virtual void getAttackedBy(const monster_ptr& monster);

    virtual creature_ptr clone() const = 0;
};

class Adult : public Citizen {
    static const Age minAge = 18; static const Age maxAge = 100;
    static const AgeIntervalChecker checker;
  public:
    Adult(const HealthPoints& healthPoints, const Age& age);

    virtual creature_ptr clone() const override;
};

class Teenager : public Citizen {
    static const Age minAge = 11; static const Age maxAge = 17;
    static const AgeIntervalChecker checker;
  public:
    Teenager(const HealthPoints& healthPoints, const Age& age);

    virtual creature_ptr clone() const override;
};

class Sheriff : public Adult, public SingleFighter {
  public:
    Sheriff(const HealthPoints& healthPoints, const Age& age, const AttackPower& attackPower);

    using SingleFighter::getAttackPower;
    void getAttackedBy(const monster_ptr& monster) override;

    virtual creature_ptr clone() const override;
};

adult_ptr createAdult(const HealthPoints& healthPoints, const Age& age);
teenager_ptr createTeenager(const HealthPoints& healthPoints, const Age& age);
sheriff_ptr createSheriff(const HealthPoints& healthPoints, const Age& age, const AttackPower& attackPower);


#endif //JNP1_CITIZEN_H
