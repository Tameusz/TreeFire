//
// Created by szust on 23.02.2022.
//

#include "../headers/Field.h"

Field::Field(int initialState)
{
    currentState = initialState;
    nextState = initialState;
}


Field::~Field()
= default;

void Field::setCurrState(int state)
{
    currentState = state;
}
void Field::setNextState(int state)
{
    nextState = state;
}

int Field::getCurrState() const
{
    return currentState;
}

int Field::getNextState() const
{
    return nextState;
}

void Field::forwardState()
{
    currentState = nextState;
}

int Field::getwind_direction() const
{
    return wind_direction;
}

int Field::getwind_power() const
{
    return wind_power;
}

void Field::set_wind_direction(int direction)
{
    wind_direction = direction;
}

void Field::set_wind_power(int power)
{
    wind_power = power;
}

////////////////////////////////////////////////////////////////////////
#include <iostream>
int calculateNextStateRandom(Field** matrix, const int size, int i, int j)
{
    if (matrix[i][j].getCurrState() == Field::states::BURNING)
        return Field::BURNING2;


    if (matrix[i][j].getCurrState() == Field::states::BURNING2)
        return Field::BURNT;

    if (matrix[i][j].getCurrState() == Field::states::BURNT)
        return Field::BURNT;

    if (matrix[i][j].getCurrState() == Field::ROCK)
        return Field::states::ROCK;

    if(i == 0)
    {

        if (j == 0 &&(         ///gdy jest w lweym gornym rogu
                matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                )
            return rand()%2;

        if(j == size - 1 &&(    /// gdy jest w lewym dolnym rogu
                matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
                matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                )
            return rand()%2;

        if(                     /// gdy jest przy lewej scianie
                matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                matrix[i + 1][j].getCurrState() == Field::states::BURNING ||
                matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                matrix[i][j + 1].getCurrState() == Field::states::BURNING
                )
            return rand()%2;

        return Field::UNTOUCHED;
    }

    if(i == size - 1)
    {

        if(j == 0 &&( ///gdy jest w prawym gornym rogu
                matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
                matrix[i][j + 1].getCurrState() == Field::states::BURNING)
                )
            return rand()%2;

        if(j == size - 1 &&( ///gdy jest w prawy dolnym rogu
                matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                matrix[i][j - 1].getCurrState() == Field::states::BURNING)
                )
            return rand()%2;

        if(             /// gdy jest przy prawej scianie
                matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                matrix[i - 1][j].getCurrState() == Field::states::BURNING ||
                matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                matrix[i][j + 1].getCurrState() == Field::states::BURNING
                )
            return rand()%2;

        return Field::UNTOUCHED;
    }

    if(j == 0 && (          /// gdy jest przy gornej krawedzi
            matrix[i-1][j].getCurrState() == Field::states::BURNING ||
            matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
            matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j].getCurrState() == Field::states::BURNING)
            )
        return rand()%2;

    if(j == size - 1 && (    /// gdy jest przy dolnej krawedzi
            matrix[i-1][j].getCurrState() == Field::states::BURNING ||
            matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
            matrix[i][j - 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j].getCurrState() == Field::states::BURNING)
            )
        return rand()%2;


    if (                    /// gdy jest gdzies w srodku
            matrix[i + 1][j].getCurrState() == Field::states::BURNING	||
            matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
            matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING	||
            matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
            matrix[i][j + 1].getCurrState() == Field::states::BURNING 	||
            matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
            matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
            matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING
            )
        return rand()%2;

    return Field::states::UNTOUCHED;

}


////////////////////////////////////////////////////////////////////////


int calculateNextStateStar(Field** matrix, const int size, int i, int j)
{
    if (matrix[i][j].getCurrState() == Field::states::BURNING)
        return Field::BURNING2;


    if (matrix[i][j].getCurrState() == Field::states::BURNING2)
        return Field::BURNT;

    if (matrix[i][j].getCurrState() == Field::states::BURNT)
        return Field::BURNT;

    if (matrix[i][j].getCurrState() == Field::ROCK)
        return Field::states::ROCK;

    if(i == 0)
    {

        if (j == 0 &&(         ///gdy jest w lweym gornym rogu
                matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                )
            return Field::states::BURNING;

        if(j == size - 1 &&(    /// gdy jest w lewym dolnym rogu
                matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                )
            return Field::states::BURNING;

        if(                     /// gdy jest przy lewej scianie
                matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                matrix[i + 1][j].getCurrState() == Field::states::BURNING   ||
                matrix[i][j + 1].getCurrState() == Field::states::BURNING
                )
            return Field::states::BURNING;

        return Field::UNTOUCHED;
    }

    if(i == size - 1)
    {

        if(j == 0 &&( ///gdy jest w prawym gornym rogu
                matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                matrix[i][j + 1].getCurrState() == Field::states::BURNING)
                )
            return Field::states::BURNING;

        if(j == size - 1 &&( ///gdy jest w prawy dolnym rogu
                matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                matrix[i][j - 1].getCurrState() == Field::states::BURNING)
                )
            return Field::states::BURNING;

        if(             /// gdy jest przy prawej scianie
                matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                matrix[i - 1][j].getCurrState() == Field::states::BURNING ||
                matrix[i][j + 1].getCurrState() == Field::states::BURNING
                )
            return Field::states::BURNING;

        return Field::UNTOUCHED;
    }

    if(j == 0 && (          /// gdy jest przy gornej krawedzi
            matrix[i-1][j].getCurrState() == Field::states::BURNING ||
            matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j].getCurrState() == Field::states::BURNING)
            )
        return Field::states::BURNING;

    if(j == size - 1 && (    /// gdy jest przy dolnej krawedzi
            matrix[i-1][j].getCurrState() == Field::states::BURNING ||
            matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
            matrix[i][j - 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j].getCurrState() == Field::states::BURNING)
            )
        return Field::states::BURNING;


    if (                    /// gdy jest gdzies w srodku
            matrix[i + 1][j].getCurrState() == Field::states::BURNING	||
            matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
            matrix[i][j + 1].getCurrState() == Field::states::BURNING 	||
            matrix[i][j - 1].getCurrState() == Field::states::BURNING
            )
        return Field::states::BURNING;

    return Field::states::UNTOUCHED;
}

////////////////////////////////////////////////////////////////////////

int calculateNextState(Field** matrix, const int size, int i, int j)
{
    if (matrix[i][j].getCurrState() == Field::states::BURNING)
        return Field::BURNING2;


    if (matrix[i][j].getCurrState() == Field::states::BURNING2)
        return Field::BURNT;

    if (matrix[i][j].getCurrState() == Field::states::BURNT)
        return Field::BURNT;

    if (matrix[i][j].getCurrState() == Field::ROCK)
        return Field::states::ROCK;


    if(i == 0)
    {

        if (j == 0 &&(         ///gdy jest w lweym gornym rogu
                matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                )
            return Field::states::BURNING;

        if(j == size - 1 &&(    /// gdy jest w lewym dolnym rogu
                matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
                matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                )
            return Field::states::BURNING;

        if(                     /// gdy jest przy lewej scianie
                matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                matrix[i + 1][j].getCurrState() == Field::states::BURNING ||
                matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                matrix[i][j + 1].getCurrState() == Field::states::BURNING
                )
            return Field::states::BURNING;

        return Field::UNTOUCHED;
    }

    if(i == size - 1)
    {

        if(j == 0 &&( ///gdy jest w prawym gornym rogu
                matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
                matrix[i][j + 1].getCurrState() == Field::states::BURNING)
                )
            return Field::states::BURNING;

        if(j == size - 1 &&( ///gdy jest w prawy dolnym rogu
                matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                matrix[i][j - 1].getCurrState() == Field::states::BURNING)
                )
            return Field::states::BURNING;

        if(             /// gdy jest przy prawej scianie
                matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                matrix[i - 1][j].getCurrState() == Field::states::BURNING ||
                matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                matrix[i][j + 1].getCurrState() == Field::states::BURNING
                )
            return Field::states::BURNING;

        return Field::UNTOUCHED;
    }

    if(j == 0 && (          /// gdy jest przy gornej krawedzi
            matrix[i-1][j].getCurrState() == Field::states::BURNING ||
            matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
            matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j].getCurrState() == Field::states::BURNING)
            )
        return Field::states::BURNING;

    if(j == size - 1 && (    /// gdy jest przy dolnej krawedzi
            matrix[i-1][j].getCurrState() == Field::states::BURNING ||
            matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
            matrix[i][j - 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
            matrix[i + 1][j].getCurrState() == Field::states::BURNING)
            )
        return Field::states::BURNING;


    if (                    /// gdy jest gdzies w srodku
            matrix[i + 1][j].getCurrState() == Field::states::BURNING	||
            matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
            matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING	||
            matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
            matrix[i][j + 1].getCurrState() == Field::states::BURNING 	||
            matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
            matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
            matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING
            )
        return Field::states::BURNING;

    return Field::states::UNTOUCHED;
}

////////////////////////////////////////////////////////////////////////

int percent_counter_plus(int wind_power)
{

    int x = rand()%100 + wind_power/2;
    if(x > 40)
        return 1;
    else
        return 0;
}

int percent_counter_minus(int wind_power)
{
    int x = rand()%100 - wind_power/2;
    if(x > 40)
        return 1;
    else
        return 0;

}
////////////////////////////////////////////////////////////////////////
int calculateNextStatesRANDOMandWIND(Field** matrix, const int size, int i, int j,int wind_direction, int wind_power)
{
    if (matrix[i][j].getCurrState() == Field::states::BURNING)
        return Field::BURNING2;

    if (matrix[i][j].getCurrState() == Field::states::BURNING2)
        return Field::BURNT;

    if (matrix[i][j].getCurrState() == Field::states::BURNT)
        return Field::BURNT;

    if (matrix[i][j].getCurrState() == Field::ROCK)
        return Field::states::ROCK;

    if (wind_direction > 0)
    {



        if(wind_direction == 1) // z góry
        {


            if(i == 0)
            {

                if (j == 0 &&(         ///gdy jest w lweym gornym rogu
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(j == size - 1 &&(    /// gdy jest w lewym dolnym rogu
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(                     /// gdy jest przy lewej scianie
                        matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING
                        )
                    return rand()%2;

                return Field::UNTOUCHED;
            }

            if(i == size - 1)
            {

                if(j == 0 &&( ///gdy jest w prawym gornym rogu
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(j == size - 1 &&( ///gdy jest w prawy dolnym rogu
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(             /// gdy jest przy prawej scianie
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING ||
                        matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING
                        )
                    return rand()%2;

                return Field::UNTOUCHED;
            }

            if(j == 0 && (          /// gdy jest przy gornej krawedzi
                    matrix[i-1][j].getCurrState() == Field::states::BURNING ||
                    matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                    )
                return rand()%2;

            if(j == size - 1 && (    /// gdy jest przy dolnej krawedzi
                    matrix[i-1][j].getCurrState() == Field::states::BURNING ||
                    matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                    )
                return rand()%2;


            if (                            /// gdy jest gdzies w srodku
                    matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
                    matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                    matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING
                    )
                return percent_counter_plus(wind_power);

            if (
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING	||
                    matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                    matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING	||
                    matrix[i][j + 1].getCurrState() == Field::states::BURNING 	||
                    matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING

                    )
                return percent_counter_minus(wind_power);


            return Field::states::UNTOUCHED;

        }
        if(wind_direction == 2) // z prawej
        {

            if(i == 0)
            {

                if (j == 0 &&(         ///gdy jest w lweym gornym rogu
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(j == size - 1 &&(    /// gdy jest w lewym dolnym rogu
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(                     /// gdy jest przy lewej scianie
                        matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING
                        )
                    return rand()%2;

                return Field::UNTOUCHED;
            }

            if(i == size - 1)
            {

                if(j == 0 &&( ///gdy jest w prawym gornym rogu
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(j == size - 1 &&( ///gdy jest w prawy dolnym rogu
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(             /// gdy jest przy prawej scianie
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING ||
                        matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING
                        )
                    return rand()%2;

                return Field::UNTOUCHED;
            }

            if(j == 0 && (          /// gdy jest przy gornej krawedzi
                    matrix[i-1][j].getCurrState() == Field::states::BURNING ||
                    matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                    )
                return rand()%2;

            if(j == size - 1 && (    /// gdy jest przy dolnej krawedzi
                    matrix[i-1][j].getCurrState() == Field::states::BURNING ||
                    matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                    )
                return rand()%2;


            if (                    /// gdy jest gdzies w srodku
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING	||
                    matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING	||
                    matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING
                    )
                return percent_counter_plus(wind_power);

            if(
                    matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                    matrix[i][j + 1].getCurrState() == Field::states::BURNING 	||
                    matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                    matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
                    matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING
                    )
                return percent_counter_minus(wind_power);

            return Field::states::UNTOUCHED;

        }
        if(wind_direction == 3) // z dolu
        {

            if(i == 0)
            {

                if (j == 0 &&(         ///gdy jest w lweym gornym rogu
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(j == size - 1 &&(    /// gdy jest w lewym dolnym rogu
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(                     /// gdy jest przy lewej scianie
                        matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING
                        )
                    return rand()%2;

                return Field::UNTOUCHED;
            }

            if(i == size - 1)
            {

                if(j == 0 &&( ///gdy jest w prawym gornym rogu
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(j == size - 1 &&( ///gdy jest w prawy dolnym rogu
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(             /// gdy jest przy prawej scianie
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING ||
                        matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING
                        )
                    return rand()%2;

                return Field::UNTOUCHED;
            }

            if(j == 0 && (          /// gdy jest przy gornej krawedzi
                    matrix[i-1][j].getCurrState() == Field::states::BURNING ||
                    matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                    )
                return rand()%2;

            if(j == size - 1 && (    /// gdy jest przy dolnej krawedzi
                    matrix[i-1][j].getCurrState() == Field::states::BURNING ||
                    matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                    )
                return rand()%2;


            if (                    /// gdy jest gdzies w srodku
                    matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING	||
                    matrix[i][j + 1].getCurrState() == Field::states::BURNING 	||
                    matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING
                    )
                return percent_counter_plus(wind_power);

            if(
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING	||
                    matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                    matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
                    matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                    matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING
                    )
                return percent_counter_minus(wind_power);

            return Field::states::UNTOUCHED;

        }
        if(wind_direction == 4) // z lewej
        {

            if(i == 0)
            {

                if (j == 0 &&(         ///gdy jest w lweym gornym rogu
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(j == size - 1 &&(    /// gdy jest w lewym dolnym rogu
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(                     /// gdy jest przy lewej scianie
                        matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i + 1][j].getCurrState() == Field::states::BURNING ||
                        matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING
                        )
                    return rand()%2;

                return Field::UNTOUCHED;
            }

            if(i == size - 1)
            {

                if(j == 0 &&( ///gdy jest w prawym gornym rogu
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(j == size - 1 &&( ///gdy jest w prawy dolnym rogu
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING)
                        )
                    return rand()%2;

                if(             /// gdy jest przy prawej scianie
                        matrix[i][j - 1].getCurrState() == Field::states::BURNING 	||
                        matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                        matrix[i - 1][j].getCurrState() == Field::states::BURNING ||
                        matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                        matrix[i][j + 1].getCurrState() == Field::states::BURNING
                        )
                    return rand()%2;

                return Field::UNTOUCHED;
            }

            if(j == 0 && (          /// gdy jest przy gornej krawedzi
                    matrix[i-1][j].getCurrState() == Field::states::BURNING ||
                    matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                    )
                return rand()%2;

            if(j == size - 1 && (    /// gdy jest przy dolnej krawedzi
                    matrix[i-1][j].getCurrState() == Field::states::BURNING ||
                    matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING ||
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING)
                    )
                return rand()%2;


            if (                    /// gdy jest gdzies w srodku
                    matrix[i - 1][j].getCurrState() == Field::states::BURNING 	||
                    matrix[i - 1][j + 1].getCurrState() == Field::states::BURNING	||
                    matrix[i - 1][j - 1].getCurrState() == Field::states::BURNING
                    )
                return percent_counter_plus(wind_power);

            if(
                    matrix[i + 1][j].getCurrState() == Field::states::BURNING	||
                    matrix[i + 1][j + 1].getCurrState() == Field::states::BURNING	||
                    matrix[i + 1][j - 1].getCurrState() == Field::states::BURNING	||
                    matrix[i][j + 1].getCurrState() == Field::states::BURNING 	||
                    matrix[i][j - 1].getCurrState() == Field::states::BURNING
                    )
                return percent_counter_minus(wind_power);


            return Field::states::UNTOUCHED;

        }
    }
    return calculateNextStateRandom(matrix,size,i,j);
}
////////////////////////////////////////////////////////////////////////
bool calculateAndSetNextStatesForFieldMatrixRANDOMandWIND(Field** matrix, const int size)
{
    if (size < 1 || matrix == nullptr)
        return false;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j )
        {
            matrix[i][j].setNextState(calculateNextStatesRANDOMandWIND(matrix,size,i,j,matrix[i][j].getwind_direction(),matrix[i][j].getwind_power()));
        }
    }
    return true;
}
////////////////////////////////////////////////////////////////////////

bool calculateAndSetNextStatesForFieldMatrix(Field** matrix, const int size)
{
    if (size < 1 || matrix == nullptr)
        return false;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j )
        {
            matrix[i][j].setNextState(calculateNextState(matrix,size,i,j));
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////

bool calculateAndSetNextStatesForFieldMatrixSTAR(Field** matrix, const int size)
{
    if (size < 1 || matrix == nullptr)
        return false;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j )
        {
            matrix[i][j].setNextState(calculateNextStateStar(matrix,size,i,j));
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////

bool calculateAndSetNextStatesForFieldMatrixRANDOM(Field** matrix, const int size)
{
    if (size < 1 || matrix == nullptr)
        return false;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j )
        {
            matrix[i][j].setNextState(calculateNextStateRandom(matrix,size,i,j));
        }
    }
    return true;
}
