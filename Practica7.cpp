//
//  main.cpp
//  ccompiler
//
//  Created by Antonio J. Rueda on 16/11/15.
//
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include "TablaSimbolos.h"
#include "TablaPalabrasReservadas.h"

using namespace std;

using namespace std::chrono;

/*
* Saltar una línea concreta
*/
void saltarLinea(ifstream& f) {
	int c;
	while ((c = f.get()) != EOF && c != '\n');
}

/*
* Saltar los dos tipos de comentarios existentes
*/
void saltarComentario(ifstream& f) {
	int c = f.peek();

	// Comprobar si se trata de un comentario inline
	if (c == '/') {
		saltarLinea(f);
	}
	else if (c == '*') {
		// ¿Se trata de un comentario tradicional tipo /* comentario */?
		f.get();

		char prev = 0;
		while ((c = f.get()) != EOF && ((c != '/') || prev != '*')) {
			prev = c;
		}
	}
}

/*
* Saltar constante de cadena
*/
void saltarCadena(ifstream& f) {
	int c;
	while ((c = f.get()) != EOF && c != '"');
}

/*
* Saltar constante de cadena
*/
void saltarCaracter(ifstream& f) {
	f.get();
	f.get();
}

/*
* Extracción de los símbolos de un programa C
*/
int main(int argc, const char * argv[]) {

	// Comprobar parámetros de entrada
	if (argc != 2) {
		cerr << "Numero de parametros incorrecto (introducir nombre de archivo)" << endl;
		return 1;
	}

	// Abrir fichero de entrada
	ifstream f(argv[1]);

	if (!f) {
		cerr << "Imposible abrir archivo" << endl;
		return 2;
	}

	// Crear y cargar tabla de palabras reservadas y de símbolos
	TablaPalabrasReservadas tablaPalabrasReservadas;
	tablaPalabrasReservadas.cargar("ckeywords.txt");

	TablaSimbolos tablaSimbolos;

	auto tiempoInicial = steady_clock::now();

	// Bucle principal para procesar fichero de entrada
	string token;
	int c;
	while ((c = f.get()) != EOF) {
		// Mientras se encuentren caracteres alfabéticos, añadir a la palabra actual
		if (isalpha(c)) {
			token.push_back(c);
		}
		else {
			// Fin de palabra. Si la palabra actual no está vacía, añadir a la tabla de símbolos
			if (!token.empty()) {
				if (!tablaPalabrasReservadas.existe(token)) {
					if (!tablaSimbolos.existe(token)) {
						tablaSimbolos.nuevo(token);
					}
				}

				token.clear();
			}

			switch (c) {
				// Saltar lineas con directivas de compilación
			case '#': saltarLinea(f); break;
				// Saltar comentarios
			case '/': saltarComentario(f); break;
				// Saltar cadenas
			case '"': saltarCadena(f); break;
				// Saltar caracteres
			case '\'': saltarCaracter(f); break;
			}
		}
	}

	auto tiempoFinal = steady_clock::now();

	// Mostrar tiempo y número de símbolos encontrados
	auto duracion = duration_cast<milliseconds>(tiempoFinal - tiempoInicial);
	cout << "Tiempo de procesamiento: " << duracion.count() << " ms." << endl;

	cout << "N� simbolos encontrados: " << tablaSimbolos.numSimbolos() << endl;

	// Guardar tabla de símbolos
	tablaSimbolos.guardar("simbolos.txt");

	return 0;
}

