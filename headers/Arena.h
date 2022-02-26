//
// Created by szust on 23.02.2022.
//

#ifndef TREEFIRE_ARENA_H
#define TREEFIRE_ARENA_H

#include "Field.h"

class Arena
{
public:
    Arena(unsigned size);
    ~Arena();
    bool create(const unsigned size); ///tworzy i wypełnia tablicę(z pomoca "fill")
    bool fill(Field val);/// wypelnia tablice

    Field& operator () (unsigned,unsigned);
    Field ** field_matrix;


private:

    unsigned size;
    bool exist;
};

#endif //TREEFIRE_ARENA_H
