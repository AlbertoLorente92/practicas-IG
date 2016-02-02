/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __OBJETOCOMPUESTO_H
#define __OBJETOCOMPUESTO_H
#include "Objeto3D.h"

class ObjetoCompuesto : public Objeto3D{
public:
	ObjetoCompuesto(){}

	ObjetoCompuesto(int h){
		_numHijos = h;
		_hijos = new Objeto3D*[_numHijos];
	}

	void pinta(){
		for(int i = 0 ; i < _numHijos; i++){
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glMultMatrixd(_hijos[i]->mt->_m);
			_hijos[i]->pinta();	
			glPopMatrix();
		}
	}

	void borra(){
		for(int i = 0 ; i < _numHijos; i++){
			_hijos[i]->borra();
			_hijos[i]->mt->borra();
			delete _hijos[i];
			_hijos[i] = NULL;
		}
	}

	int _numHijos;
	Objeto3D** _hijos;
};

#endif // __OBJETOCOMPUESTO_H