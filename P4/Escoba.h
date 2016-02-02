/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __ESCOBA_H
#define __ESCOBA_H

#include "ObjetoCompuesto.h"
#include "Cilindro.h"

class Escoba : public ObjetoCompuesto{
public:
	
	//Metodos:	
	Escoba(){
		escoba = new ObjetoCompuesto(2);
		int nHijos = 0;

		escoba->_hijos[0] = new Cilindro(1.0,1.0,20.0,10,10,Brown);
		escoba->_hijos[1] = new Cilindro(1.0,1.0,8.0,10,10,Brown);

		TAfin* t = new TAfin();
		/////////////////////////////Palo alargado
		escoba->_hijos[nHijos]->mt = t->clona();	
		nHijos++;
		/////////////////////////////Palo corto (traves)
		t->traslada(new PuntoVector3D(-4.0,0.0,20.0,1.0));		
		t->rotaY(90);
		escoba->_hijos[nHijos]->mt = t->clona();	

		nHijos = 0;
		cerdas = new ObjetoCompuesto(5);

		cerdas->_hijos[0] = new Cilindro(0.5,0.5,4.0,10,10,Black);
		cerdas->_hijos[1] = new Cilindro(0.5,0.5,4.0,10,10,Black);
		cerdas->_hijos[2] = new Cilindro(0.5,0.5,4.0,10,10,Black);
		cerdas->_hijos[3] = new Cilindro(0.5,0.5,4.0,10,10,Black);
		cerdas->_hijos[4] = new Cilindro(0.5,0.5,4.0,10,10,Black);

		/////////////////////////////Cerda 1
		t = new TAfin();
		t->traslada(new PuntoVector3D(-4.0,0.0,20.5,1.0));	
		cerdas->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		/////////////////////////////Cerda 2
		t = new TAfin();
		t->traslada(new PuntoVector3D(-2.0,0.0,20.5,1.0));	
		cerdas->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		/////////////////////////////Cerda 3
		t = new TAfin();
		t->traslada(new PuntoVector3D(0.0,0.0,20.5,1.0));	
		cerdas->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		/////////////////////////////Cerda 4
		t = new TAfin();
		t->traslada(new PuntoVector3D(2.0,0.0,20.5,1.0));	
		cerdas->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		/////////////////////////////Cerda 5
		t = new TAfin();
		t->traslada(new PuntoVector3D(4.0,0.0,20.5,1.0));	
		cerdas->_hijos[nHijos]->mt = t->clona();	

		delete t;
		t = NULL;
	}

	void pinta(){
		escoba->pinta();
		cerdas->pinta();
	}

	void borra(){
		escoba->borra();
		cerdas->borra();
	}

private:
	ObjetoCompuesto* escoba;
	ObjetoCompuesto* cerdas;
};

#endif // __ESCOBA_H