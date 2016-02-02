/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __DISCOPARCIAL_H
#define __DISCOPARCIAL_H
#include "ObjetoCuadrico.h"

class DiscoParcial : public ObjetoCuadrico{
public:
		
	//Metodos:	
	DiscoParcial(GLdouble i,GLdouble o,GLint s,GLint r,GLdouble ang1,GLdouble ang2,Color c){
		_discoParcial = gluNewQuadric();
		_innerRadius = i;
		_outerRadius = o;
		_slices = s;
		_rings = r;
		_startAngle = ang1;
		_sweepAngle = ang2;
		_c = c;
		gluQuadricDrawStyle(_discoParcial,GLU_FILL);
	}

	void pinta(){
		glColor3f(_c.getF1(),_c.getF2(),_c.getF3()); 
		gluPartialDisk(_discoParcial, _innerRadius, _outerRadius, _slices, _rings, _startAngle, _sweepAngle);
	}

	void borra(){
		gluDeleteQuadric(_discoParcial);
		_discoParcial = NULL;
	}

private:
	GLUquadric* _discoParcial;
	GLdouble _innerRadius,_outerRadius,_startAngle,_sweepAngle;
	GLint _slices, _rings;
	Color _c;

};

#endif // __DISCOPARCIAL_H