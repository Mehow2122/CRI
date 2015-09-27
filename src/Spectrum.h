//
// Created by mehow on 12.09.15.
//
#include <vector>
#include "defines.h"
#ifndef CPP1_SPECTRUM_H
#define CPP1_SPECTRUM_H


#endif //CPP1_SPECTRUM_H
class Spectrum{
private:
    std::vector <double> data;
public:
    void setData(double tab[SIZE]);
    void setData(std::vector <double> tab[SIZE]);
    void printData();
    std::vector <double> getData();
};