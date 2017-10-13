#include "monster.h"
#include <iostream>
// Monster
Monster::Monster() : Creature(), Fighter() {}


// SingleMonster
SingleMonster::SingleMonster(const HealthPoints& healthPoints, const AttackPower& attackPower)
    : SingleCreature(healthPoints), SingleFighter(attackPower) {}


// Zombie
const std::string Zombie::name = "Zombie";
Zombie::Zombie(const HealthPoints& healthPoints, const AttackPower& attackPower)
    : SingleMonster(healthPoints, attackPower) {}

creature_ptr Zombie::clone() const {
    return std::dynamic_pointer_cast<Creature>(std::make_shared<Zombie>(getHealth(), getAttackPower()));
}

std::string Zombie::getName() const { return name; }


// Vampire
const std::string Vampire::name = "Vampire";
Vampire::Vampire(const HealthPoints& healthPoints, const AttackPower& attackPower)
    : SingleMonster(healthPoints, attackPower) {}

creature_ptr Vampire::clone() const {
    return std::dynamic_pointer_cast<Creature>(std::make_shared<Vampire>(getHealth(), getAttackPower()));
}

std::string Vampire::getName() const { return name; }


// Mummy
const std::string Mummy::name = "Mummy";
Mummy::Mummy(const HealthPoints& healthPoints, const AttackPower& attackPower)
    : SingleMonster(healthPoints, attackPower) {}

creature_ptr Mummy::clone() const {
    return std::dynamic_pointer_cast<Creature>(std::make_shared<Mummy>(getHealth(), getAttackPower()));
}

std::string Mummy::getName() const { return name; }


// GroupOfMonsters
const std::string GroupOfMonsters::name = "GroupOfMonsters";
//TODO wywalic copy/paste code

GroupOfMonsters::GroupOfMonsters(const std::vector<monster_ptr>& newMonsters) : Monster() {
    for(auto mon_ptr : newMonsters)
        this->monsters.push_back(std::dynamic_pointer_cast<Monster> (mon_ptr->clone()));
    healthPoints = calcHealth();
    attackPower = calcAttPower();
}

GroupOfMonsters::GroupOfMonsters(const std::initializer_list<monster_ptr>& newMonsters) : Monster() {
    for(auto mon_ptr : newMonsters)
        this->monsters.push_back(std::dynamic_pointer_cast<Monster>(mon_ptr->clone()));
    healthPoints = calcHealth();
    attackPower = calcAttPower();
}

HealthPoints GroupOfMonsters::getHealth() const { return healthPoints; }
AttackPower GroupOfMonsters::getAttackPower() const { return attackPower; }

void GroupOfMonsters::takeDamage(const AttackPower& damage) {
    for(auto monster: monsters){
        HealthPoints prevHealth = monster->getHealth();
        if(prevHealth > 0) {
            // take damage
            monster->takeDamage(damage);
            HealthPoints newHealth = monster->getHealth();
            healthPoints -= prevHealth - newHealth;

            // Disable his attackPower if he died
            if(newHealth == 0){ attackPower -= monster->getAttackPower();}
        }
    }
}

AttackPower GroupOfMonsters::calcAttPower() const {
    AttackPower cur = 0;
    for(auto monsterPtr : monsters ){ cur += monsterPtr->getAttackPower();}
    return cur;
}
HealthPoints GroupOfMonsters::calcHealth() const {
    HealthPoints cur = 0;
    for(auto monsterPtr : monsters ){ cur += monsterPtr->getHealth();}
    return cur;
}


creature_ptr GroupOfMonsters::clone() const {
    return std::dynamic_pointer_cast<Creature>(std::make_shared<GroupOfMonsters>(monsters));
}

std::string GroupOfMonsters::getName() const { return name; }

zombie_ptr createZombie(const HealthPoints& healthPoints, const AttackPower& attackPower) {
    return std::make_shared<Zombie>(healthPoints, attackPower);
}
vampire_ptr createVampire(const HealthPoints& healthPoints, const AttackPower& attackPower) {
    return std::make_shared<Vampire>(healthPoints, attackPower); }

mummy_ptr createMummy(const HealthPoints& healthPoints, const AttackPower& attackPower) {
    return std::make_shared<Mummy>(healthPoints, attackPower); }

group_ptr createGroupOfMonsters(const std::initializer_list<monster_ptr>& newMonsters) {
    std::vector<monster_ptr> newVector(newMonsters);
    return createGroupOfMonsters(newVector);
}

group_ptr createGroupOfMonsters(const std::vector<monster_ptr>& newMonsters) {
    return std::make_shared<GroupOfMonsters>(newMonsters);
}
