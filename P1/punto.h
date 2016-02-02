/*	Pr�ctica 1 - Inform�tica Gr�fica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente S�nchez.
*/

#ifndef __PUNTO_H
#define __PUNTO_H

#include <math.h>
#include <GL/freeglut.h>

/**
 Implementaci�n del TAD Punto.

 Las operaciones son:

 - Punto: -> Punto. Generadora.

 Getters:
 - x: -> GLdouble. Observadora.
 - y: -> GLdouble. Observadora.

 Metodos:
 - distancia: Punto -> GLdouble. Observadora.
 */
class Punto {
public:
	//Constructora:
	/**
		Constructora de la clase Punto con parametros.
	*/
	Punto(const GLdouble a,const GLdouble b){
		_A=a;
		_B=b;
	}

	Punto(){}

	//Getters:
	/**
		Devuelve la coordenada x del punto.
	*/
	GLdouble x() const{
		return _A;
	}

	/**
		Devuelve la coordenada y del punto.
	*/
	GLdouble y() const{
		return _B;
	}

	//Metodos:
	/**
		Devuelve la distancia entre dos puntos.
	*/
	GLdouble distancia(Punto p){
		return sqrt(pow(p.x()-_A,2) + pow(p.y()-_B,2));
	}

private:
	GLdouble _A;
	GLdouble _B;
};

#endif // __PUNTO_H