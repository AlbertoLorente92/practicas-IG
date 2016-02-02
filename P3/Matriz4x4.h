/*	Práctica 3 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __MATRIZ4X4_H
#define __MATRIZ4X4_H

#include "PuntoVector3D.h"

class Matriz4x4 {
public:
	//Constructora:
	/**
		Constructora de la clase PuntoVector3D con parametros.
	*/
	Matriz4x4(const PuntoVector3D a,const PuntoVector3D b,const PuntoVector3D c,const PuntoVector3D d){
		_c1[0] = a.getX();
		_c1[1] = a.getY();
		_c1[2] = a.getZ();
		_c1[3] = a.getPuntoVector();
		/////////////////
		_c2[0] = b.getX();
		_c2[1] = b.getY();
		_c2[2] = b.getZ();
		_c2[3] = b.getPuntoVector();
		/////////////////
		_c3[0] = c.getX();
		_c3[1] = c.getY();
		_c3[2] = c.getZ();
		_c3[3] = c.getPuntoVector();
		/////////////////
		_c4[0] = d.getX();
		_c4[1] = d.getY();
		_c4[2] = d.getZ();
		_c4[3] = d.getPuntoVector();
	}

	Matriz4x4(const GLdouble t){
		PuntoVector3D C( (GLfloat)cos(t) + ((GLfloat)t*((GLfloat)sin(t))), 0, ((GLfloat)sin(t)) - ((GLfloat)t*((GLfloat)cos(t))),	1);
		PuntoVector3D Cp(((GLfloat)t * ((GLfloat)cos(t))),	0,(	( (GLfloat)t * ((GLfloat)sin(t)))),	0);
		PuntoVector3D Cpp((((GLfloat)cos(t)) - ( (GLfloat)t * ((GLfloat)sin(t)))),	0,(((GLfloat)sin(t)) + ((GLfloat)t * ((GLfloat)cos(t)))),	0);

		PuntoVector3D* T = Cp.clona();
		T->normaliza();

		PuntoVector3D* B = Cpp.clona();
		B = B->productoVectorial(&Cp);
		B->normaliza();

		PuntoVector3D N = B->productoVectorial(T);

		_c1[0] = N.getX();
		_c1[1] = N.getY();
		_c1[2] = N.getZ();
		_c1[3] = 0;//N.getPuntoVector();
		/////////////////
		_c2[0] = B->getX();
		_c2[1] = B->getY();
		_c2[2] = B->getZ();
		_c2[3] = 0;//B->getPuntoVector();
		/////////////////
		_c3[0] = T->getX();
		_c3[1] = T->getY();
		_c3[2] = T->getZ();
		_c3[3] = 0;//T->getPuntoVector();
		/////////////////
		_c4[0] = C.getX();
		_c4[1] = C.getY();
		_c4[2] = C.getZ();
		_c4[3] = 1;//C.getPuntoVector();

		delete B;
		B = NULL;
		delete T;
		T = NULL;
	}

	Matriz4x4(){}

	~Matriz4x4(){};


	PuntoVector3D* multiplicaPuntoXMatriz(PuntoVector3D p){
		PuntoVector3D* p3 = new PuntoVector3D(	_c1[0]*p.getX()+_c2[0]*p.getY()+_c3[0]*p.getZ()+_c4[0],
												_c1[1]*p.getX()+_c2[1]*p.getY()+_c3[1]*p.getZ()+_c4[1],
												_c1[2]*p.getX()+_c2[2]*p.getY()+_c3[2]*p.getZ()+_c4[2],
												_c1[3]*p.getX()+_c2[3]*p.getY()+_c3[3]*p.getZ()+_c4[3]);
		return p3;
	}

private:
	GLfloat _c1[4];
	GLfloat _c2[4];
	GLfloat _c3[4];
	GLfloat _c4[4];	

};

#endif // __MATRIZ4X4_H