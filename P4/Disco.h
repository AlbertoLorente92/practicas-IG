/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __DISCO_H
#define __DISCO_H
#include "ObjetoCuadrico.h"

class Disco : public ObjetoCuadrico{
public:
		
	//Metodos:	
	Disco(GLdouble i,GLdouble o,GLint s,GLint r,Color c){
		_disco = gluNewQuadric();
		_innerRadius = i;
		_outerRadius = o;
		_slices = s;
		_rings = r;
		_c = c;
		gluQuadricDrawStyle(_disco,GLU_FILL);
	}

	void pinta(){
		glColor3f(_c.getF1(),_c.getF2(),_c.getF3()); 
		gluDisk(_disco, _innerRadius, _outerRadius, _slices, _rings);
	}

	void borra(){
		gluDeleteQuadric(_disco);
		_disco = NULL;
	}

private:
	GLUquadric* _disco;
	GLdouble _innerRadius,_outerRadius;
	GLint _slices, _rings;
	Color _c;

};

#endif // __DISCO_H