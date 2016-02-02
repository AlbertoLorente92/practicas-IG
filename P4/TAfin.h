/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#include "PuntoVector3D.h"

#ifndef __TAFIN_H
#define __TAFIN_H

class TAfin {
public:
	static const int TAM = 16;	

	//Metodos:	
	TAfin(PuntoVector3D* c11,PuntoVector3D* c22,PuntoVector3D* c33,PuntoVector3D* c44){
		c1 = c11->clona();
		c2 = c22->clona();
		c3 = c33->clona();
		c4 = c44->clona();
		_m = new double[TAM];
		aplicaMatriz();
	}

	TAfin(){
		_m = new double[TAM];
		reset();
	}

	
	
	void traslada(PuntoVector3D* v){
		c4 = v->clona();
		aplicaMatriz();
	}

	void reset(){
		c1 = new PuntoVector3D(1.0,0.0,0.0,0.0);
		c2 = new PuntoVector3D(0.0,1.0,0.0,0.0);
		c3 = new PuntoVector3D(0.0,0.0,1.0,0.0);
		c4 = new PuntoVector3D(0.0,0.0,0.0,1.0);
		aplicaMatriz();
	}

	void rotaX(GLdouble ang){
		c1 = new PuntoVector3D(1.0,0.0,0.0,0.0);
		c2 = new PuntoVector3D(0.0,cos((ang*M_PI)/180.0),sin((ang*M_PI)/180.0),0.0);
		c3 = new PuntoVector3D(0.0,-sin((ang*M_PI)/180.0),cos((ang*M_PI)/180.0),0.0);
		aplicaMatriz();
	}

	void rotaY(GLdouble ang){
		c1 = new PuntoVector3D(cos((ang*M_PI)/180.0),0.0,-sin((ang*M_PI)/180.0),0.0);
		c2 = new PuntoVector3D(0.0,1.0,0.0,0.0);
		c3 = new PuntoVector3D(sin((ang*M_PI)/180.0),0.0,cos((ang*M_PI)/180.0),0.0);
		aplicaMatriz();
	}

	void rotaZ(GLdouble ang){
		c1 = new PuntoVector3D(cos((ang*M_PI)/180.0),sin((ang*M_PI)/180.0),0.0,0.0);
		c2 = new PuntoVector3D(-sin((ang*M_PI)/180.0),cos((ang*M_PI)/180.0),0.0,0.0);
		c3 = new PuntoVector3D(0.0,0.0,1.0,0.0);
		aplicaMatriz();
	}

	void aplicaMatriz(){
		_m[0] = c1->getX();
		_m[1] = c1->getY();
		_m[2] = c1->getZ();
		_m[3] = 0.0;
		_m[4] = c2->getX();
		_m[5] = c2->getY();
		_m[6] = c2->getZ();
		_m[7] = 0.0;
		_m[8] = c3->getX();
		_m[9] = c3->getY();
		_m[10] = c3->getZ();
		_m[11] = 0.0;
		_m[12] = c4->getX();
		_m[13] = c4->getY();
		_m[14] = c4->getZ();
		_m[15] = 1;		
	}

	void escalar(GLdouble e){
		GLdouble x = c1->getX()*e;
		GLdouble y = c2->getY()*e;
		GLdouble z = c3->getZ()*e;
		c1->setX(x);
		c2->setY(y);
		c3->setZ(z);
		aplicaMatriz();
	}

	void borra(){
		delete c1;
		c1 = NULL;
		delete c2;
		c2 = NULL;
		delete c3;
		c3 = NULL;
		delete c4;
		c4 = NULL;
		delete _m;
		_m = NULL;

	}

	TAfin* clona(){
		return new TAfin(c1,c2,c3,c4);
	}

	PuntoVector3D* c1;
	PuntoVector3D* c2;
	PuntoVector3D* c3;
	PuntoVector3D* c4;
	double* _m;
};

#endif // __TAFIN_H