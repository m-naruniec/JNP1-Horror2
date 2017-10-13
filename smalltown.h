
#ifndef JNP1_SMALLTOWN_H
#define JNP1_SMALLTOWN_H

#include <vector>
#include <unordered_set>
#include "helper.h"
#include "citizen.h"
#include "monster.h"

class Clock;
class JNPClock;
class SmallTown;


/**
 * Class representing a general clock so that time counting strategies are derivatives of this class.
 */
class Clock {
    Time current;
    Time timeOfTheDay;

    /**
     * Check if the Timer parameters are consistent
     * @return verdict of verification
     */
    bool correctTime(const Time& startTime, const Time& endTime) const;
  public:

    Clock(const Time& startTime, const Time& endTime);

    /**
     * Checks (depending on given strategy) if current hour is an attack hour
     */
    virtual bool isAttackHour() const = 0;

    /**
     * Adds time interval to the current time
     */
    Clock& operator+=(const Time& timeStep);
    Time getCurrent() const;
};

/**
 * Clock with specific strategy for attack hours
 */
class JNPClock : public Clock {
    const static Time divisorHours[];
    const static Time undivisorHours[];
  public:
    JNPClock(const Time& startTime, const Time& endTime);

    virtual bool isAttackHour() const override;
};


class SmallTown {
    Time t0;
    Time t1;
    unsigned long aliveCitizens;

    monster_ptr monster;
    std::unique_ptr<Clock> timer;
    std::vector<citizen_ptr> citizens;
    std::string result;

    /**
     * Checks if the game has ended, if it has, saves the result in result variable
     * @return
     * true - the game has ended
     * false - the game is still going on
     */
    bool hasEnded();

    /**
     * Prints the result of the game if the game has ended
     * called when game has not ended prints something undefined
     */
    void printResult() const;
    SmallTown(const Time& t0, const Time& t1,
              const monster_ptr& monster, const std::vector<citizen_ptr>& citizens);
  public:
    class BuilderClass {
        bool isT0Set{false}, isT1Set{false}, isMonsterSet{false}, isAnyCitizen{false};
        bool checkRequirements();

        Time t0;
        Time t1;
        monster_ptr currentMonster{nullptr};

        std::unique_ptr<Clock> timer;

        // optimisation structure used only to check if a citizen is already in a vector.
        std::unordered_set<citizen_ptr> citizenSet;

        std::vector<citizen_ptr> citizenVector;

      public:
        BuilderClass() {}

        BuilderClass& monster(const monster_ptr& newMonster);
        BuilderClass& startTime(const Time& t0);
        BuilderClass& maxTime(const Time& t1);
        BuilderClass& citizen(const citizen_ptr& newCitizen);

        SmallTown build();
    };

    static BuilderClass Builder() {
        return BuilderClass{};
    }

    /**
     * Plays one round in SmallTown
     * if now is a time of attack, then monsters attack citizens
     * then timeStep is added to the clock
     * @param timeStep amount of time that should be added to the clock
     */
    void tick(const Time& timeStep);

    /**
     * gets a structure with current status of smalltown
     * @return structure with:
     * name of the monster (name of a class)
     * counter of alive citizens
     * summary health of the monsters
     */
    Status getStatus() const;
};


#endif //JNP1_SMALLTOWN_H
