#include "smalltown.h"

#include <cassert>
#include <iostream>
#include "smalltown.h"


// Clock
bool Clock::correctTime(const Time& startTime, const Time& endTime) const {
    return endTime >= startTime && endTime > 0;
}

Clock::Clock(const Time& startTime, const Time& endTime) :
    current(startTime), timeOfTheDay(endTime){ assert(correctTime(startTime, endTime)); }

Clock& Clock::operator+=(const Time& timeStep){
    current = (current + timeStep) % (timeOfTheDay + 1);
    return (*this);
}

Time Clock::getCurrent() const { return current; }


// JNPClock
const Time JNPClock::divisorHours[] = {3, 13};
const Time JNPClock::undivisorHours[] = {7};

JNPClock::JNPClock(const Time& startTime, const Time& endTime) : Clock(startTime, endTime) {}

bool JNPClock::isAttackHour() const {
    bool attack = false;
    for(Time divisorHour : divisorHours){ // is time divisable by 3 or 13?
        if(!(getCurrent() % divisorHour)){ attack = true; }
    }

    for(Time undivisorHour : undivisorHours){ // and is not divisable by 7?
        if(!(getCurrent() % undivisorHour)){ attack = false; }
    }
    return attack;
}


// SmallTown
SmallTown::SmallTown(const Time& t0, const Time& t1, const monster_ptr& newMonster,
                     const std::vector<citizen_ptr>& newCitizens) :
    t0(t0), t1(t1), monster(newMonster), timer(std::make_unique<JNPClock>(t0, t1)), citizens{} {
    // Deep copying
    for(auto cit_ptr : newCitizens)
        citizens.push_back(std::dynamic_pointer_cast<Citizen>(cit_ptr->clone()));
    aliveCitizens = static_cast<unsigned long>(citizens.size());
}

Status SmallTown::getStatus() const {
    return Status(monster->getName(), monster->getHealth(), aliveCitizens);
}

bool SmallTown::hasEnded() {
    if(aliveCitizens == 0 && monster->getHealth() == 0){
        result = "DRAW";
        return true;
    }
    if (aliveCitizens == 0){
        result = "MONSTER WON";
        return true;
    }
    if (monster->getHealth() == 0){
        result = "CITIZENS WON";
        return true;
    }
    return false;
}

void SmallTown::printResult() const { std::cout << result << std::endl; }

void SmallTown::tick(const Time& timeStep) {
    if(hasEnded()){
        printResult();
    } else {
        if(timer->isAttackHour()){
            for(auto citizen : citizens){

                if(citizen->getHealth()){
                    // health of citizen is checked mainly so that if he's dead after the
                    // round we can deduct if aliveCitizens counter should be decreased or not

                    citizen->getAttackedBy(monster);

                    // if citizen died then counter should get smaller
                    if(citizen->getHealth() == 0){ --aliveCitizens; }
                }
            }
        }
        *timer += timeStep;
    }
}

// SmallTown::BuilderClass
SmallTown::BuilderClass& SmallTown::BuilderClass::monster(const monster_ptr& newMonster) {
    this->currentMonster = newMonster;
    this->isMonsterSet = true;
    return *this;
}

SmallTown::BuilderClass& SmallTown::BuilderClass::startTime(const Time& t0) {
    this->t0 = t0;
    this->isT0Set = true;
    return *this;
}

SmallTown::BuilderClass& SmallTown::BuilderClass::maxTime(const Time& t1) {
    this->t1 = t1;
    this->isT1Set = true;
    return *this;
}

SmallTown::BuilderClass& SmallTown::BuilderClass::citizen(const citizen_ptr& newCitizen) {
    if(citizenSet.find(newCitizen) == citizenSet.end()) {
        citizenSet.insert(newCitizen);
        citizenVector.push_back(newCitizen);
        this->isAnyCitizen = true;
    }
    return *this;
}


SmallTown SmallTown::BuilderClass::build() {
    assert(checkRequirements());
    return SmallTown(t0, t1, currentMonster, citizenVector);
}

bool SmallTown::BuilderClass::checkRequirements() {
    return isT0Set && isT1Set && isMonsterSet && isAnyCitizen;
}