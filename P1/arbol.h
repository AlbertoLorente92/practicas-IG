/*	Práctica 1 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __ARBOL_H
#define __ARBOL_H

#include <GL/freeglut.h>
#include "lista.h"
#include "cuadrado.h"
/**
 Implementación del TAD Arbol.

 Las operaciones son:

 - Arbol: -> Arbol. Generadora.

 Getters:
 - getArchivados: -> Lista<Cuadrados>. Observadora.
 - getFrontera: -> Lista<Cuadrados>. Observadora.

 Setters:
 - setArchivados: Lista<Cuadrados> -> void. Modificadora.
 - setFrontera: Lista<Cuadrados> -> void. Modificadora.

 Metodos:
 - pinta: void -> Escena. Modificadora.
 */
class Arbol {
public:

	//Constructora
	/**
		Constructora de la clase arbol.
	*/
	Arbol(){	
		Lista<Cuadrado> l;
		_Archivados = l;
	}

	//Getters:
	/**
		Devuelve la lista de los cuadrados archivados.
	*/
	Lista<Cuadrado> getArchivados(){
		return _Archivados;
	}

	/**
		Devuelve la lista de los cuadrados frontera.
	*/
	Lista<Cuadrado> getFrontera(){
		return _Frontera;
	}

	//Setters:
	/**
		Establece una nueva lista de cuadrados archivados.
	*/
	void setArchivados(Lista<Cuadrado> l){
		_Archivados = l;
	}

	/**
		Establece una nueva lista de cuadrados frontera.
	*/
	void setFrontera(Lista<Cuadrado> l){
		_Frontera = l;
	}

	//Metodos:
	/**
		Pinta los cuadrados de las listas.
	*/
	void pinta(){
		Cuadrado aux;
		Lista<Cuadrado>::Iterador it = _Frontera.principio();
		Lista<Cuadrado>::Iterador it2 = _Archivados.principio();

		while(it != _Frontera.final()){
			aux = it.elem();
			aux.dibujar();
			it.avanza();
		}

		while(it2 != _Archivados.final()){
			aux = it2.elem();
			aux.dibujar();
			it2.avanza();
		}

	}

private:
	Lista<Cuadrado> _Archivados;
	Lista<Cuadrado> _Frontera;
};

#endif // __ARBOL_H