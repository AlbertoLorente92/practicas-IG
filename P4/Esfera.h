/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __ESFERA_H
#define __ESFERA_H
#include "ObjetoCuadrico.h"

class Esfera : public ObjetoCuadrico{
public:
		
	//Metodos:	
	Esfera(GLdouble r,GLint p,GLint m,Color c){
		_esfera = gluNewQuadric();
		_radioEsfera = r;
		_paralelos = p;
		_meridianos = m;
		_c = c;
		gluQuadricDrawStyle(_esfera,GLU_FILL);
	}

	void pinta(){
		glColor3f(_c.getF1(),_c.getF2(),_c.getF3()); 
		gluSphere(_esfera,_radioEsfera,_meridianos,_paralelos);	
	}

	void borra(){
		gluDeleteQuadric(_esfera);
		_esfera = NULL;
	}

private:
	GLUquadric* _esfera;
	GLdouble _radioEsfera;
	GLint _paralelos, _meridianos;
	Color _c;
};

#endif // __ESFERA_H