//
// Created by szust on 23.02.2022.
//

#ifndef TREEFIRE_FIELD_H
#define TREEFIRE_FIELD_H

class Field
{
public:
    enum states { UNTOUCHED, BURNING, ROCK, BURNING2, BURNT}; /// 0 = untouched, 1 = burning, 2 = rock, 3 = burning1, 4 = burnt

    Field(int = states::UNTOUCHED);
    virtual ~Field();

    int getCurrState() const; /// podaje aktualny stan
    int getNextState() const; /// podaje nastepny stan
    int getwind_direction() const;
    int getwind_power() const;
    void setCurrState(int); /// ustawia aktualny stan
    void setNextState(int);     ///ustawia nastepny stan
    void forwardState();    /// zamienia stan aktualny na nastepny
    void set_wind_direction(int);
    void set_wind_power(int);

protected:
    int currentState;
    int nextState;
    int wind_direction{};
    int wind_power{};
};


int percent_counter_plus(int wind_power);
int percent_counter_minus(int wind_power);
int calculateNextState(Field** matrix, const int size, int i, int j); /// sprawdza nastepny stan
bool calculateAndSetNextStatesForFieldMatrix(Field** matrix, const int size); ///zamienia stany la calej tablicy
bool calculateAndSetNextStatesForFieldMatrixRANDOM(Field** matrix, const int size);
bool calculateAndSetNextStatesForFieldMatrixSTAR(Field** matrix, const int size);
bool calculateAndSetNextStatesForFieldMatrixRANDOMandWIND(Field** matrix, const int size);
int calculateNextStateStar(Field** matrix, const int size, int i, int j);
int calculateNextStateRandom(Field** matrix, const int size, int i, int j);
int calculateNextStatesRANDOMandWIND(Field** matrix, const int size, int i, int j,int wind_direction, int wind_power);


#endif //TREEFIRE_FIELD_H
