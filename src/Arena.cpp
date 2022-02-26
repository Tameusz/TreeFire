//
// Created by szust on 23.02.2022.
//

#include "../headers/Arena.h"

Arena::Arena(unsigned size)
{
    exist = false;
    this->size = size;
    field_matrix = nullptr;
}

Arena::~Arena()
{
    if(field_matrix)
    {
        for(unsigned i = 0; i<size; ++i)
            if(field_matrix[i])
                delete[] field_matrix[i];
        delete[] field_matrix;
    }
}

Field&  Arena::operator () (unsigned x, unsigned y)
{
    return field_matrix[x][y];
}


bool Arena::fill(Field val)
{
    if (exist)
    {
        for (unsigned i = 0; i < size; ++i)
            for (unsigned j = 0; j < size; ++j)
                field_matrix[i][j] = val;
        return true;
    }
    return false;
}

bool Arena::create(const unsigned size)
{
    Field val = Field::UNTOUCHED;
    field_matrix = new Field * [size];
    for(unsigned i=0; i<size; ++i)
        field_matrix[i]  = new Field [size];
    fill(val);
    return 1;
}
