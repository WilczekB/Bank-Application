
#ifndef CREDITCALCULATOR_H
#define CREDITCALCULATOR_H

#include "credit.h"
#include "calculator.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

class Credit;

class CreditCalculator : public Calculator
{
private:
    //Wskaźnik na obiekt klasy Credit
    Credit* credit_;
public:
    //Konstruktor
    CreditCalculator(Credit* credit);
    //Destruktor
    ~CreditCalculator();
    //Funkcja do tworzenia harmonogramu spłaty kredytu
    void calculate() override;
};

#endif // CREDITCALCULATOR_H
