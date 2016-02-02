/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __OJO_H
#define __OJO_H

#include "ObjetoCompuesto.h"
#include "Disco.h"

class Ojo : public ObjetoCuadrico{
public:
	
	//Metodos:	
	Ojo(GLenum l){

		ligth =l;
		o = new ObjetoCompuesto(1);

		o->_hijos[0] = new Disco(0.2,1.0,10,10,Black);


		TAfin* t = new TAfin();
		o->_hijos[0]->mt = t->clona();	

		delete t;
		t = NULL;
	}

	void pinta(){

		
		
		GLfloat p1[]={0.0f,0.0f,0.0f,1.0f};	 
		glLightfv(ligth,GL_POSITION,p1);
		GLfloat di1[]={0.0f,0.0f,1.0f};			
		glLightfv(ligth,GL_SPOT_DIRECTION,di1);
		glLightf(ligth,GL_SPOT_CUTOFF,45.0f);
		glLightf(ligth,GL_SPOT_EXPONENT,0.0f);
		GLfloat d[]={1.0,1.0,1.0,0.0};
		glLightfv(ligth, GL_DIFFUSE, d);
		GLfloat a[]={0.3f,0.3f,0.3f,1.0};
		glLightfv(ligth, GL_AMBIENT, a);

		o->pinta();
	}

	void borra(){
		o->borra();
	}

private:
	GLenum ligth;
	ObjetoCompuesto* o;
};

#endif // __OJOS_H