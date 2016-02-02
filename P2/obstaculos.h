/*	Práctica 2 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __OBSTACULOS_H
#define __OBSTACULOS_H

#include "pelota.h"
#include <GL/freeglut.h>

/**
 Implementación de la interfaz Obstaculos.
*/
class Obstaculos {
public:
	
	//Metodos:	
	virtual bool intersecionConRecta(Pelota p,double& tIn, Punto& normalIn) = 0;

	virtual void pinta() = 0;

};

#endif // __OBSTACULOS_H