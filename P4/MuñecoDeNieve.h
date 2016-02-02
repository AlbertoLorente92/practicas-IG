/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __MUÑECODENIEVE_H
#define __MUÑECODENIEVE_H

#include "ObjetoCompuesto.h"
#include "Sombrero.h"
#include "Cilindro.h"
#include "Esfera.h"
#include "Malla.h"
#include "Disco.h"
#include "Ojo.h"
#include "Escoba.h"

class MuñecoDeNieve : public Objeto3D{
public:
	
	//Metodos:	
	MuñecoDeNieve(){
		cuerpo = new ObjetoCompuesto(13);

		int nHijos = 0;

		Esfera* e1 = new Esfera(10.0,10,10,White);
		Esfera* e2 = new Esfera(5.0,10,10,White);

		Cilindro* nariz = new Cilindro(2.0,0.0,8.0,10,10,Orange);

		Cilindro* boton1 = new Cilindro(2.0,2.0,4.0,10,10,Black);
		Cilindro* boton2 = new Cilindro(2.0,2.0,4.0,10,10,Black);
		Cilindro* boton3 = new Cilindro(2.0,2.0,4.0,10,10,Black);

		Disco* tapaBoton1 = new Disco(0.0,2.0,10,10,Black);
		Disco* tapaBoton2 = new Disco(0.0,2.0,10,10,Black);
		Disco* tapaBoton3 = new Disco(0.0,2.0,10,10,Black);

		Sombrero* s = new Sombrero();

		Ojo* izquierdo = new Ojo(GL_LIGHT1);
		Ojo* derecho = new Ojo(GL_LIGHT2);

		Escoba* escoba = new Escoba();

		cuerpo->_hijos[0] = e1;
		cuerpo->_hijos[1] = e2;

		cuerpo->_hijos[2] = nariz;

		cuerpo->_hijos[3] = boton1;
		cuerpo->_hijos[4] = boton2;
		cuerpo->_hijos[5] = boton3;

		cuerpo->_hijos[6] = tapaBoton1;
		cuerpo->_hijos[7] = tapaBoton2;
		cuerpo->_hijos[8] = tapaBoton3;

		cuerpo->_hijos[9] = s;

		cuerpo->_hijos[10] = izquierdo;
		cuerpo->_hijos[11] = derecho;

		cuerpo->_hijos[12] = escoba;

		TAfin* t = new TAfin();
		/////////////////////////////Esferas cuerpo
		t->traslada(new PuntoVector3D(0.0,10.0,0.0,1.0));		//Esfera inferior (cuerpo)
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		t = new TAfin();
		t->traslada(new PuntoVector3D(0.0,23.0,0.0,1.0));		//Esfera superior (cabeza)
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		/////////////////////////////Cilidro nariz
		t = new TAfin();
		t->traslada(new PuntoVector3D(3.0,23.0,3.0,1.0));
		t->rotaY(45);
		cuerpo->_hijos[nHijos]->mt = t->clona();			
		nHijos++;

		/////////////////////////////Cilidro botones
		t = new TAfin();
		t->traslada(new PuntoVector3D(4.0,15.0,4.0,1.0));		//Boton superior
		t->rotaY(45);
		cuerpo->_hijos[nHijos]->mt = t->clona();		
		nHijos++;

		t = new TAfin();
		t->traslada(new PuntoVector3D(4.8,10.0,4.8,1.0));		//Boton central
		t->rotaY(45);
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		t = new TAfin();
		t->traslada(new PuntoVector3D(4.0,5.0,4.0,1.0));		//Boton inferior
		t->rotaY(45);
		cuerpo->_hijos[nHijos]->mt = t->clona();		
		nHijos++;

		/////////////////////////////Discos botones
		t = new TAfin();
		t->traslada(new PuntoVector3D(6.8,15.0,6.8,1.0));		//Boton superior Tapadera
		t->rotaY(45);
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		t = new TAfin();
		t->traslada(new PuntoVector3D(7.0,10.0,7.0,1.0));		//Boton central Tapadera
		t->rotaY(45);
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		t = new TAfin();
		t->traslada(new PuntoVector3D(6.8,5.0,6.8,1.0));		//Boton inferior Tapadera
		t->rotaY(45);
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		t = new TAfin();
		t->traslada(new PuntoVector3D(0.0,30.5,0.0,1.0));		//Sombrero
		t->rotaX(90);
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		t = new TAfin();
		t->traslada(new PuntoVector3D(2.0,24.5,4.5,1.0));		//ojo Izquierdo
		t->rotaY(45);
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		t = new TAfin();
		t->traslada(new PuntoVector3D(4.5,24.5,2.0,1.0));		//ojo Derecho
		t->rotaY(45);
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		t = new TAfin();
		t->traslada(new PuntoVector3D(9.0,0.0,-9.0,1.0));		//Escoba
		t->rotaX(-90);
		cuerpo->_hijos[nHijos]->mt = t->clona();	
		nHijos++;

		delete t;
		t = NULL;

		/////////////////////////////Construir suelo
		construirSuelo();
	}

	void construirSuelo(){
		const int NV = 4;
		int indVert[NV];
		int nCaras = 0, nVertices = 0;

		m = new Malla();

		m->_numVertices = 8;
		m->_numNormales = 8;
		m->_numCaras = 6;

		m->_vertices = new PuntoVector3D*[m->_numVertices];
		m->_normales = new PuntoVector3D*[m->_numNormales];
		m->_caras = new Cara*[m->_numCaras];

		/////////////////////////////////////////////////////////////Lateral superior derecha
		m->_vertices[nVertices] = new PuntoVector3D(-10.0,0.0,-10.0,1);		//0
		nVertices++;
		m->_vertices[nVertices] = new PuntoVector3D(-10.0,-2.0,-10.0,1);	//1
		nVertices++;
		m->_vertices[nVertices] = new PuntoVector3D(10.0,-2.0,-10.0,1);		//2
		nVertices++;
		m->_vertices[nVertices] = new PuntoVector3D(10.0,0.0,-10.0,1);		//3
		nVertices++;

		indVert[0] = 0;	indVert[1] = 1;	indVert[2] = 2; indVert[3] = 3;
		m->_caras[nCaras] = new Cara(indVert,NV,nCaras);
		nCaras++;

		/////////////////////////////////////////////////////////////Lateral inferior derecha
		m->_vertices[nVertices] = new PuntoVector3D(10.0,0.0,10.0,1);		//4
		nVertices++;
		m->_vertices[nVertices] = new PuntoVector3D(10.0,-2.0,10.0,1);		//5
		nVertices++;

		indVert[0] = 3;	indVert[1] = 2;	indVert[2] = 5; indVert[3] = 4;
		m->_caras[nCaras] = new Cara(indVert,NV,nCaras);
		nCaras++;

		/////////////////////////////////////////////////////////////Lateral inferior izquierda
		m->_vertices[nVertices] = new PuntoVector3D(-10.0,0.0,10.0,1);		//6
		nVertices++;
		m->_vertices[nVertices] = new PuntoVector3D(-10.0,-2.0,10.0,1);		//7

		indVert[0] = 4;	indVert[1] = 5;	indVert[2] = 7; indVert[3] = 6;
		m->_caras[nCaras] = new Cara(indVert,NV,nCaras);
		nCaras++;

		/////////////////////////////////////////////////////////////Lateral superior izquierda
		indVert[0] = 6;	indVert[1] = 7;	indVert[2] = 1; indVert[3] = 0;
		m->_caras[nCaras] = new Cara(indVert,NV,nCaras);
		nCaras++;		

		/////////////////////////////////////////////////////////////Tablero inferior
		indVert[0] = 1;	indVert[1] = 2;	indVert[2] = 5; indVert[3] = 7;
		m->_caras[nCaras] = new Cara(indVert,NV,nCaras);
		nCaras++;

		/////////////////////////////////////////////////////////////Tablero superior
		indVert[0] = 0;	indVert[1] = 3;	indVert[2] = 4; indVert[3] = 6;
		m->_caras[nCaras] = new Cara(indVert,NV,nCaras);
		

		calculaNormales();
	}

	void calculaNormales(){
		for(int k = 0; k < m->_numCaras; k++){
			m->_normales[k] = m->calculoVectorNormalPorNewell(m->_caras[k]);
		}
	}

	void pinta(){
		cuerpo->pinta();

		glColor3f(Red.getF1(),Red.getF2(),Red.getF3()); 
		m->pinta();
	}

	void borra(){
		cuerpo->borra();
		m->borra();
	}
	
private:	
	ObjetoCompuesto* cuerpo;
	Malla* m;
};

#endif // __MUÑECODENIEVE_H