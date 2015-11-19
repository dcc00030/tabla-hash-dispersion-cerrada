//
//  TablaPalabrasReservadas.hpp
//  ccompiler
//
//  Created by Antonio J. Rueda on 16/11/15.
//

#ifndef TablaPalabrasReservadas_hpp
#define TablaPalabrasReservadas_hpp

#include <exception>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class ErrorFicheroPalabrasReservadas : public exception {};

class TablaPalabrasReservadas {
    vector<string> palabrasReservadas;

public:
    TablaPalabrasReservadas() : palabrasReservadas() {
        
    }
    
    void cargar(const string& archivo);
    
    bool existe(const string& palabra) {
        return find(palabrasReservadas.begin(), palabrasReservadas.end(), palabra) != palabrasReservadas.end();
    }
};

#endif /* TablaPalabrasReservadas_hpp */
