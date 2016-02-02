/*	Práctica 3 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __LAPIZ_H
#define __LAPIZ_H

#include "PuntoVector3D.h"

/**
 Implementación del TAD Lapiz.

 Las operaciones son:

 - Lapiz:  -> Lapiz. Generadora.
 - Lapiz: Punto, GLdouble -> Lapiz. Generadora.

 Getters:
 - getPos: -> Punto. Observadora.
 - getDir: -> GLdouble. Observadora.

 Metodos:
 - moveTo: Punto, bool -> void. Modificadora.
 - turnTo: GLdouble -> void. Modificadora.
 - turn: GLdouble -> void. Modificadora.
 - forward: GLdouble, bool -> void. Modificadora.

 */
class Lapiz{
private:
	PuntoVector3D* _pto;
	GLdouble _dir;
public:
	//Constructora:
	/**
		Constructora de la clase lapiz vacia.
	*/
	Lapiz(){
		_pto = new PuntoVector3D(0,0,0,1);
		_dir = 0;
	}

	/**
		Constructora de la clase lapiz con el punto y la direccion hacia la que dibujar.
	*/
	Lapiz(PuntoVector3D* p, GLdouble d)
	{
		_pto = new PuntoVector3D(p->getX(),p->getY(),p->getZ(),p->getPuntoVector());
		_dir = d;
	}

	//Getters:
	/**
		Devuelve el punto de la clase lapiz.
	*/
	PuntoVector3D* getPos() const{
		return _pto;
	}

	/**
		Devuelve el angulo de la clase lapiz.
	*/
	GLdouble getDir() const{
		return _dir;
	}

	//Metodos:
	/**
		Establece un nuevo punto.
	*/
	void moveTo(PuntoVector3D* p, bool draw){
		if(draw)
			_pto = p;
	}

	/**
		Establece una nueva direccion (angulo).
	*/
	void turnTo(GLdouble a){
		_dir = a;
	}

	/**
		Establece una nueva direccion (angulo) al sumarle otro angulo (todo en grados).
	*/
	void turn(GLdouble a){
		if( a > 360)
			a = int(a)%360;
		_dir += a;
	}

	/**
		Avanza el punto de la clase lapiz una distacia 'dist' hacia la direccion de la clase.
	*/
	void forward(GLdouble dist, bool draw,bool modo){
		if(modo){
			if(draw)
				_pto = new PuntoVector3D ((_pto->getX() + (GLfloat)dist*((GLfloat)cos(_dir*M_PI/180.0))),(_pto->getY() + (GLfloat)dist*((GLfloat)sin(_dir*M_PI/180.0))),_pto->getZ(),1);
		}else{
			if(draw)
				_pto = new PuntoVector3D ((_pto->getX() + (GLfloat)dist*((GLfloat)cos(_dir*M_PI/180.0))),_pto->getY(),(_pto->getZ() + (GLfloat)dist*((GLfloat)sin(_dir*M_PI/180.0))),1);
		}
	}

};
#endif // __LAPIZ_H