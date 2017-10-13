#include <cassert>
#include "citizen.h"

// Citizen
Citizen::Citizen(const HealthPoints& healthPoints, const Age& age) : SingleCreature(healthPoints), age(age) {}

Age Citizen::getAge() const { return age; }

void Citizen::getAttackedBy(const monster_ptr& monster) { takeDamage(monster->getAttackPower()); }


// Adult
const AgeIntervalChecker Adult::checker = AgeIntervalChecker(minAge, maxAge);

Adult::Adult(const HealthPoints& healthPoints, const Age& age) : Citizen(healthPoints, age) {
    assert(checker.isInside(age));
}

creature_ptr Adult::clone() const {
    return std::dynamic_pointer_cast<Creature>(std::make_shared<Adult>(getHealth(), getAge()));
}


// Teenager
const AgeIntervalChecker Teenager::checker = AgeIntervalChecker(minAge, maxAge);

Teenager::Teenager(const HealthPoints& healthPoints, const Age& age) : Citizen(healthPoints, age) {
    assert(checker.isInside(age));
}

creature_ptr Teenager::clone() const {
    return std::dynamic_pointer_cast<Creature>(std::make_shared<Teenager>(getHealth(), getAge()));
}

// Sheriff
Sheriff::Sheriff(const HealthPoints& healthPoints, const Age& age, const AttackPower& attackPower)
    : Adult(healthPoints, age), SingleFighter(attackPower) {}

creature_ptr Sheriff::clone() const {
    return std::dynamic_pointer_cast<Creature>(std::make_shared<Sheriff>(getHealth(), getAge(), getAttackPower()));
}

void Sheriff::getAttackedBy(const monster_ptr& monster) {
    if(getHealth()) {
        // Assumes that both attack are at the same time, that is - or both are hit or neither
        Citizen::getAttackedBy(monster);
        monster->takeDamage(getAttackPower());
    }
}

// Creators
adult_ptr createAdult(const HealthPoints& healthPoints, const Age& age) {
    return std::make_shared<Adult>(healthPoints, age);
}
teenager_ptr createTeenager(const HealthPoints& healthPoints, const Age& age) {
    return std::make_shared<Teenager>(healthPoints, age); }

sheriff_ptr createSheriff(const HealthPoints& healthPoints, const Age& age, const AttackPower& attackPower) {
    return std::make_shared<Sheriff>(healthPoints, age, attackPower); }
