//
//  TablaSimbolos.cpp
//  ccompiler
//
//  Created by Antonio J. Rueda on 16/11/15.
//
#include "stdafx.h"
#include <fstream>
#include "TablaSimbolos.h"

void TablaSimbolos::guardar(const string& archivo) {
    ofstream f(archivo);
    
    if (!f) {
        throw ErrorGuardadoTablaSimbolos();
    }
    
    for (string& simbolo : tablaSimbolos) {
        f << simbolo << endl;
    }
}
