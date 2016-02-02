/*	Práctica 3 - Informática Gráfica (IG)
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
	PuntoVector3D(const GLfloat a,const GLfloat b,const GLfloat c,const GLfloat d){
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
	GLfloat getX() const{
		return _x;
	}

	/**
		Devuelve la coordenada y del PuntoVector3D.
	*/
	GLfloat getY() const{
		return _y;
	}

	/**
		Devuelve la coordenada z del PuntoVector3D.
	*/
	GLfloat getZ() const{
		return _z;
	}

	GLfloat getPuntoVector() const{
		return _PuntoOVector;
	}

	//Setters:

	void setX(GLfloat x){
		_x = x;
	}

	void setY(GLfloat y){
		_y = y;
	}

	void setZ(GLfloat z){
		_z = z;
	}

	void setPuntoVector(GLfloat p){
		_PuntoOVector = p;
	}

	//Metodos:
	/**
		Producto vectorial entre 2 vectores
	*/
	PuntoVector3D* productoVectorial(PuntoVector3D* p){
		GLfloat nuevaX = _y*p->getZ() - _z*p->getY();
		GLfloat nuevaY = _z*p->getX() - p->getZ()*_x;
		GLfloat nuevaZ = _x*p->getY() - p->getX()*_y;
		return new PuntoVector3D(nuevaX,nuevaY,nuevaZ,0);
	}

	void normaliza(){
		//hallamos la raiz cuadrada de la suma de los cuadrados
		GLfloat raiz = sqrt( (_x * _x) + ( _y * _y) + (_z * _z));

		if(raiz!=0){
			//hallamos y guardamos la primera coordenada
			_x = _x / raiz;

			//hallamos y guardamos la segunda coordenada
			_y = _y / raiz;

			//hallamos y guardamos la tercera coordenada
			_z = _z / raiz;
		}
	}

	PuntoVector3D* productoCruzado(PuntoVector3D* p){
		GLfloat x = (_y*p->getZ()) - (p->getY()*_z);
		GLfloat y = -1* ((_x*p->getZ()) - (p->getX()*_z));
		GLfloat z = (_x*p->getY()) - (p->getX()*_y);
		return new PuntoVector3D(x,y,z,0);
	}

	GLdouble productoEscalar(PuntoVector3D* v2)
	{
		return  _x*v2->getX() + _y*v2->getY() + _z*v2->getZ();
	}
	GLdouble productoFrenet(PuntoVector3D* v2)
	{
		return  _x*v2->getX() + _y*v2->getY() + _z*v2->getZ() + _PuntoOVector*v2->getPuntoVector();
	}

	PuntoVector3D* clona(){
		return new PuntoVector3D(_x,_y,_z,_PuntoOVector);
	}

private:
	GLfloat _x;
	GLfloat _y;
	GLfloat _z;
	GLfloat _PuntoOVector;		//1 indica punto 0 vector
};

#endif // __PUNTOVECTOR3D_H