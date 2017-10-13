//
//  horror_example.cc
//  horror-movie-2
//
//  Created by Patrycja Wegrzynowicz on 12/10/16.
//  Copyright (c) 2016 Patrycja Wegrzynowicz. All rights reserved.
//

#include <cassert>
#include <iostream>
#include "citizen.h"
#include "monster.h"
#include "smalltown.h"

int main(int argc, const char * argv[]) {
    auto mum = createMummy(90, 1);
    auto zom = createZombie(20, 1);
    auto vam = createVampire(30, 1);

    std::vector<monster_ptr> mon;
    mon.push_back(mum); mon.push_back(zom); mon.push_back(vam);
    std::cout << mon[0]->getHealthPoints() << std::endl;
    std::cout << mon[1]->getHealthPoints() << std::endl;
    std::cout << mon[2]->getHealthPoints() << std::endl;
    auto group = createGroupOfMonsters(mon);
    std::cout << group->getHealthPoints() << std::endl;
    std::cout << group->getAttackPower() << std::endl;

    std::cout << mum->getHealthPoints() << std::endl;
    auto groupOfMonsters = createGroupOfMonsters({
                                                         createMummy(90, 1),
                                                         createZombie(20, 1),
                                                         createVampire(30, 1)
                                                 });
    auto smallTown = SmallTown::Builder()
            .monster(groupOfMonsters)
            .startTime(3)
            .maxTime(27)
            .citizen(createSheriff(100, 35, 20))
            .citizen(createAdult(100, 21))
            .citizen(createTeenager(50, 14))
            .build();

    smallTown.tick(18);
    smallTown.tick(3);

    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "GroupOfMonsters");
    assert(status.getMonsterHealth() == 80);
    assert(status.getAliveCitizens() == 3);

    return 0;
}
