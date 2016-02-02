/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __PUNTOVECTOR3D_H
#define __PUNTOVECTOR3D_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
using namespace std;

#include <gl/GL.h>
#include <gl/GLU.h>


class PuntoVector3D {
public:
	//Constructora:
	/**
		Constructora de la clase PuntoVector3D con parametros.
	*/
	PuntoVector3D(const GLdouble a,const GLdouble b,const GLdouble c,const GLdouble d){
		_x=a;
		_y=b;
		_z=c;
		_PuntoOVector=d;
	}

	PuntoVector3D(PuntoVector3D* p){
		_x = p->getX();
		_y = p->getY();
		_z = p->getZ();
		_PuntoOVector= p->getPuntoVector();
	}

	PuntoVector3D(){}

	~PuntoVector3D(){};

	//Getters:
	/**
		Devuelve la coordenada x del PuntoVector3D.
	*/
	GLdouble getX() const{
		return _x;
	}

	/**
		Devuelve la coordenada y del PuntoVector3D.
	*/
	GLdouble getY() const{
		return _y;
	}

	/**
		Devuelve la coordenada z del PuntoVector3D.
	*/
	GLdouble getZ() const{
		return _z;
	}

	GLdouble getPuntoVector() const{
		return _PuntoOVector;
	}

	//Setters:

	void setX(GLdouble x){
		_x = x;
	}

	void setY(GLdouble y){
		_y = y;
	}

	void setZ(GLdouble z){
		_z = z;
	}

	void setPuntoVector(GLdouble p){
		_PuntoOVector = p;
	}

	//Metodos:
	/**
		Producto vectorial entre 2 vectores
	*/
	PuntoVector3D* productoVectorial(PuntoVector3D* p){
		GLdouble nuevaX = _y*p->getZ() - p->getY()*_z;
		GLdouble nuevaY = _z*p->getX() - p->getZ()*_x;
		GLdouble nuevaZ = _x*p->getY() - p->getX()*_y;
		return new PuntoVector3D(nuevaX,nuevaY,nuevaZ,0);
	}

	void normaliza(){
		//hallamos la raiz cuadrada de la suma de los cuadrados
		GLdouble raiz = sqrt( (_x * _x) + ( _y * _y) + (_z * _z));

		if(raiz!=0){
			//hallamos y guardamos la primera coordenada
			_x = _x / raiz;

			//hallamos y guardamos la segunda coordenada
			_y = _y / raiz;

			//hallamos y guardamos la tercera coordenada
			_z = _z / raiz;
		}
	}

	GLdouble productoEscalar(PuntoVector3D* v2){
		return  _x*v2->getX() + _y*v2->getY() + _z*v2->getZ();
	}

	GLdouble productoFrenet(PuntoVector3D* v2){
		return  _x*v2->getX() + _y*v2->getY() + _z*v2->getZ() + _PuntoOVector*v2->getPuntoVector();
	}

	PuntoVector3D* clona(){
		return new PuntoVector3D(_x,_y,_z,_PuntoOVector);
	}

	void resta(PuntoVector3D* v){
		_x -= v->getX();
		_y -= v->getY();
		_z -= v->getZ();
	}

	void suma(PuntoVector3D* p){
		_x +=p->getX();
		_y +=p->getY();
		_z +=p->getZ();
	}

private:
	GLdouble _x;
	GLdouble _y;
	GLdouble _z;
	GLdouble _PuntoOVector;		//1 indica punto 0 vector
};

#endif // __PUNTOVECTOR3D_H