//
//  TablaSimbolos.hpp
//  ccompiler
//
//  Created by Antonio J. Rueda on 16/11/15.
//

#ifndef TablaSimbolos_hpp
#define TablaSimbolos_hpp

#include <exception>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class ErrorGuardadoTablaSimbolos : public exception {};

class TablaSimbolos {
    vector<string> tablaSimbolos;
    
public:
    TablaSimbolos() : tablaSimbolos() {}
    
    bool existe(const string& palabra) {
        return find(tablaSimbolos.begin(), tablaSimbolos.end(), palabra) != tablaSimbolos.end();
    }
    
    void nuevo(const string& palabra) {
        tablaSimbolos.push_back(palabra);
    }
    
    void guardar(const string& archivo);
    
    size_t numSimbolos() { return tablaSimbolos.size(); }
};

#endif /* TablaSimbolos_hpp */
