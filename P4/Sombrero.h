/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __SOMBRERO_H
#define __SOMBRERO_H
#include "ObjetoCompuesto.h"
#include "Cilindro.h"
#include "Disco.h"
#include "Esfera.h"

class Sombrero : public ObjetoCuadrico{
public:
		
	//Metodos:	
	Sombrero(){
		s = new ObjetoCompuesto(3);
		Disco* d;
		Cilindro* c;	
		Esfera* e;

		d = new Disco(5.0,10.0,10,10,Black);
		c = new Cilindro(5.0,5.0,5.0,10,10,Gray);
		e = new Esfera(5.0,10,10,Gray);

		s->_hijos[0] = e;
		s->_hijos[1] = c;	
		s->_hijos[2] = d;

		TAfin* t = new TAfin();
		s->_hijos[0]->mt = t->clona();
		s->_hijos[1]->mt = t->clona();

		t->traslada(new PuntoVector3D(0.0,0.0,5.0,0));
		s->_hijos[2]->mt = t->clona();

		delete t;
		t = NULL;
	}

	void pinta(){
		s->pinta();
	}

	void borra(){
		s->borra();
	}

private:
	ObjetoCompuesto* s;
};

#endif // __SOMBRERO_H