/*	Práctica 1 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __CUADRADO_H
#define __CUADRADO_H

#include <GL/freeglut.h>
#include <math.h>
#include "punto.h"
#include "color.h"
/**
 Implementación del TAD Cuadrado.

 Las operaciones son:

 - Cuadrado: Punto,Punto,Punto,Punto -> Cuadrado. Generadora.
 
 Getters:
 - getColor: -> Color. Observadora.
 - getNivel: -> int. Observadora.
 - getP1: -> Punto. Observadora.
 - getP2: -> Punto. Observadora.
 - getP3: -> Punto. Observadora.
 - getP4: -> Punto. Observadora.

 Setters:
 - setColor: Color -> void. Modificadora.
 - setNivel: int -> void. Modificadora.

 Metodos:
 - dibujar: Cuadrado -> void. Observadora.

 */
class Cuadrado {
public:

	//Constructora:
	/**
		Constructora de la clase cuadrado. Cuatro puntos (p1,p2,p3,p4) ordenacion:
		p1 -> esquina inferior izquierda.
		p2 -> esquina inferior derecha.
		p3 -> esquina superior derecha.
		p4 -> esquina superior izquierda.
	*/
	Cuadrado(Punto p1,Punto p2,Punto p3,Punto p4){
		_p1=p1;
		_p2=p2;
		_p3=p3;
		_p4=p4;
	}

	Cuadrado(){}

	//Getters:
	/**
		Devuelve el color del cuadrado.
	*/
	Color getColor(){
		return _c;
	}

	/**
		Devuelve el nivel de anidamiento del cuadrado.
	*/
	int getNivel(){
		return _nivel;
	}

	/**
		Devuelve el punto de la esquina inferior izquierda.
	*/
	Punto getP1(){
		return _p1;
	}

	/**
		Devuelve el punto de la esquina inferior derecha.
	*/
	Punto getP2(){
		return _p2;
	}

	/**
		Devuelve el punto de la esquina superior derecha.
	*/
	Punto getP3(){
		return _p3;
	}

	/**
		Devuelve el punto de la esquina superior izquierda.
	*/
	Punto getP4(){
		return _p4;
	}

	//Setters:
	/**
		Establece el color del cuadrado.
	*/
	void setColor(Color c){
		_c = c;
	}

	/**
		Establece nivel de anidamiento del cuadrado.
	*/
	void setNivel(int n){
		_nivel = n;
	}

	//Metodos:
	/**
		Dibuja el cuadrado en el area visible de la escena del color establecido.
	*/
	void dibujar(){
		glBegin ( GL_POLYGON ) ;
			glColor3f(_c.getF1(),_c.getF2(),_c.getF3());
			glVertex2d( _p1.x(), _p1.y());
			glVertex2d( _p2.x(), _p2.y());
			glVertex2d( _p3.x(), _p3.y());
			glVertex2d( _p4.x(), _p4.y());
			glVertex2d( _p1.x(), _p1.y());
		glEnd () ;
	}

private:
	Punto _p1;
	Punto _p2;
	Punto _p3;
	Punto _p4;
	int _nivel;
	Color _c;
};

#endif // __CUADRADO_H