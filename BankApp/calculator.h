
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <QDate>

class Calculator
{
public:
    //Konstruktor
    Calculator();
    //Wirtualny destruktor
    virtual ~Calculator();
    //Wirtualna funkcja służaca do obliczania rat, bądź odsetek
    virtual void calculate() = 0;
};

#endif // CALCULATOR_H
