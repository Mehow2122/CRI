//
// Created by mehow on 12.09.15.
//

#include "Spectrum.h"
#include <cstdio>
#include <iostream>
using namespace std;

void Spectrum::setData(double tab[SIZE]){

    for(int i=0;i<SIZE;i++) {
        data.push_back(tab[i]);
    }
}
void Spectrum::setData(vector <double> tab[SIZE]){

data = *tab;
}
void Spectrum::printData(){
    for(int i=0;i<data.size();i++){
        cout/*<<360+i*5<<" "*/<<data[i]<<endl;
    }
}

vector <double> Spectrum::getData(){

    return data;
}
