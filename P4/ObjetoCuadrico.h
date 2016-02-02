/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __OBJETOCUADRICO_H
#define __OBJETOCUADRICO_H
#include "Objeto3D.h"

class ObjetoCuadrico : public Objeto3D{
public:
		
	//Metodos:	
	ObjetoCuadrico(){}

	virtual void pinta() = 0;

	virtual void borra() = 0;

};

#endif // __OBJETOCUADRICO_H