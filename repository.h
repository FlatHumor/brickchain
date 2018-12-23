//
// Created by mark on 12/23/18.
//

#ifndef BRICKCHAIN_REPOSITORY_H
#define BRICKCHAIN_REPOSITORY_H

#include <vector>
#include "brick.h"

class repository
{
public:
    virtual void load_brick(brick *, int32_t &) { }
    virtual void save_brick(brick &, int32_t &) { }
    virtual std::vector<int32_t> get_identificators() { return { }; }
};

#endif //BRICKCHAIN_REPOSITORY_H
