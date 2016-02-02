/*	Pr�ctica 4 - Inform�tica Gr�fica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente S�nchez.
*/

#include "TAfin.h"
#include "color.h"
#ifndef __OBJETO3D_H
#define __OBJETO3D_H

class Objeto3D {
public:

	virtual void pinta() = 0;

	virtual void borra() = 0;

	TAfin* mt;

};

#endif // __OBJETO3D_H