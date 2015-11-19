//
//  TablaPalabrasReservadas.cpp
//  ccompiler
//
//  Created by Antonio J. Rueda on 16/11/15.
//
#include "stdafx.h"
#include <fstream>
#include "TablaPalabrasReservadas.h"

void TablaPalabrasReservadas::cargar(const string& archivo) {
    ifstream f(archivo.c_str());
    
    if (!f) {
        throw ErrorFicheroPalabrasReservadas();
    }
    
    string palabra;
    
    while (f >> palabra) {
        palabrasReservadas.push_back(palabra);
    }
}
