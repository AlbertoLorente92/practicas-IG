/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __CILINDRO_H
#define __CILINDRO_H
#include "ObjetoCuadrico.h"

class Cilindro : public ObjetoCuadrico{
public:
		
	//Metodos:	
	Cilindro(GLdouble b,GLdouble t,GLdouble h,GLint sl,GLint st,Color c){
		_cilindro = gluNewQuadric();
		_baseRadius = b;
		_topRadius = t;
		_height = h;
		_slices = sl;
		_stacks = st;
		_c = c;
		gluQuadricDrawStyle(_cilindro,GLU_FILL);
	}

	void pinta(){
		glColor3f(_c.getF1(),_c.getF2(),_c.getF3()); 
		gluCylinder(_cilindro, _baseRadius, _topRadius, _height, _slices, _stacks);
	}

	void borra(){
		gluDeleteQuadric(_cilindro);
		_cilindro = NULL;
	}

private:
	GLUquadric* _cilindro;
	GLdouble _baseRadius,_topRadius,_height;
	GLint _slices, _stacks;
	Color _c;

};

#endif // __CILINDRO_H