#include <cassert>
#include "helper.h"

// Status
Status::Status(const std::string& monsterName, const HealthPoints& monsterHealth, unsigned long aliveCitizens) :
    monsterName(monsterName), monsterHealth(monsterHealth), aliveCitizens(aliveCitizens) {};

std::string Status::getMonsterName() const { return monsterName;}
HealthPoints Status::getMonsterHealth() const { return monsterHealth;}
unsigned long Status::getAliveCitizens() const { return aliveCitizens;}

// AgeIntervalChecker
AgeIntervalChecker::AgeIntervalChecker(Age min, Age max) : min(min), max(max){};

// Creature
Creature::Creature() {}

// SingleCreature
SingleCreature::SingleCreature(const HealthPoints& healthPoints) : Creature(), healthPoints(healthPoints) {
    assert(healthPoints > 0);
};

HealthPoints SingleCreature::getHealth() const { return healthPoints; }
void SingleCreature::takeDamage(const AttackPower& damage) {
    healthPoints = (healthPoints > damage) ? healthPoints - damage : 0;
}

// Fighter
Fighter::Fighter() {};

// SingleFighter
SingleFighter::SingleFighter(const AttackPower& attackPower) : Fighter(), attackPower(attackPower) {}
AttackPower SingleFighter::getAttackPower() const { return attackPower; }
