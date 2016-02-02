/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __CAMARA_H
#define __CAMARA_H

#include "PuntoVector3D.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
using namespace std;
#include <GL/freeglut.h>
class Camara{
private:
	PuntoVector3D *u, *v,*n;
	PuntoVector3D *eye, *look, *up;
	GLdouble m [16];
	PuntoVector3D* p1, *p2, *p3; //<-Para las rotaciones pitch yaw y roll

public:
	Camara(PuntoVector3D* ojo, PuntoVector3D* mira, PuntoVector3D* arriba){
		eye = ojo->clona();
		look = mira->clona();
		up = arriba->clona();
		setModelViewMatrix(); //Calcula en función de eye, look, up los atributos u, v, n
	}

	void recorridoEje(GLdouble x,GLdouble y,GLdouble z){
		eye->setX(eye->getX() + x * 10);
		eye->setY(eye->getY() + y * 10);
		eye->setZ(eye->getZ() + z * 10);
		setModelViewMatrix();
	}

	void rotacionRoll(GLdouble ang){
		GLdouble cs = cos(ang / 180.0 * M_PI);
		GLdouble sn = sin(ang / 180.0 * M_PI);
		u->setX(cs*p2->getX() - sn*p3->getX());
		u->setY(cs*p2->getY() - sn*p3->getY());
		u->setZ(cs*p2->getZ() - sn*p3->getZ());
		u->normaliza();
		//Calculamos el nuevo vector v
		v->setX(sn*p2->getX() + cs*p3->getX());
		v->setY(sn*p2->getY() + cs*p3->getY());
		v->setZ(sn*p2->getZ() + cs*p3->getZ());
		//Calculamos el nuevo vector u

		//Aplicamos Matriz
		aplicaMatriz();
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(m);
	}

	void rotacionPitch(GLdouble ang){
		GLdouble cs = cos(ang / 180.0 * M_PI);
		GLdouble sn = sin(ang / 180.0 * M_PI);

		//Calculamos el nuevo vector n
		n->setX(cs*p1->getX() - sn*p3->getX());
		n->setY(cs*p1->getY() - sn*p3->getY());
		n->setZ(cs*p1->getZ() - sn*p3->getZ());
		n->normaliza();
		//Calculamos el nuevo vector v
		v->setX(sn*p1->getX() + cs*p3->getX());
		v->setY(sn*p1->getY() + cs*p3->getY());
		v->setZ(sn*p1->getZ() + cs*p3->getZ());
		v->normaliza();

		//Aplicamos Matriz
		aplicaMatriz();
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(m);
	}

	void rotacionYaw(GLdouble ang){
		GLdouble cs = cos(ang / 180.0 * M_PI);
		GLdouble sn = sin(ang / 180.0 * M_PI);

		//Calculamos el nuevo vector u
		u->setX(cs*p2->getX() - sn*p1->getX());
		u->setY(cs*p2->getY() - sn*p1->getY());
		u->setZ(cs*p2->getZ() - sn*p1->getZ());
		u->normaliza();
		//Calculamos el nuevo vector n
		n->setX(sn*p2->getX() + cs*p1->getX());
		n->setY(sn*p2->getY() + cs*p1->getY());
		n->setZ(sn*p2->getZ() + cs*p1->getZ());
		n->normaliza();

		//Aplicamos Matriz
		aplicaMatriz();
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(m);
	}

	void giraX(){								//OK
		//calculamos el radio
		GLdouble radio = sqrt( (eye->getY() * eye->getY()) + (eye->getZ() * eye->getZ()) );

		//sacamos el angulo
		GLdouble angulo = atan2(eye->getY() , eye->getZ());
		
		//restamos 0.05 radianes
		angulo -= 0.05;

		//calculamos el nuevo Z
		eye->setZ(cos(angulo) * radio);

		//calculamos el nuevo Y
		eye->setY( sin(angulo) * radio);
		
		//actualizamos la matriz de vista
		setModelViewMatrix();	
	}

	void giraY(){								//OK
		//calculamos el radio
		GLdouble radio = sqrt( (eye->getX() * eye->getX()) + (eye->getZ() * eye->getZ()) );

		//sacamos el angulo
		GLdouble angulo = atan2( eye->getX(), eye->getZ());
		
		//restamos 0.05 radianes
		angulo -= 0.05;

		//calculamos el nuevo Z
		eye->setZ( cos(angulo) * radio);

		//calculamos el nuevo X
		eye->setX( sin(angulo) * radio);

		//actualizamos la matriz de vista
		setModelViewMatrix();
	}

	void giraZ(){								//OK
		//calculamos el radio
		GLdouble radio = sqrt( (eye->getY() * eye->getY()) + (eye->getX() * eye->getX()) );

		//sacamos el angulo
		GLdouble angulo = atan2( eye->getY(), eye->getX());
		
		//sumamos 0.05 radianes
		angulo += 0.05;

		//calculamos el nuevo Z
		eye->setX( cos(angulo) * radio);

		//calculamos el nuevo X
		eye->setY( sin(angulo) * radio);

		//actualizamos la matriz de vista
		setModelViewMatrix();
	}

	void lateral(){					//4			OK
		up->setX(0);
		up->setY(1);

		eye->setX(100);
		eye->setY(0);
		eye->setZ(0);
		setModelViewMatrix();
	}

	void frontal(){					//5			OK
		up->setX(0);
		up->setY(1);

		eye->setX(0);
		eye->setY(0);
		eye->setZ(100);
		setModelViewMatrix();
	}

	void cenital(){					//6			OK
		up->setX(1);
		up->setY(0);

		eye->setX(0);
		eye->setY(100);
		eye->setZ(0);
		setModelViewMatrix();
	}

	void esquina(){					//7			OK
		up->setX(0);
		up->setY(1);

		eye->setX(100);
		eye->setY(100);
		eye->setZ(100);
		setModelViewMatrix();
	}

	void aplicaPerspectiva(bool perpectiva){
		//Si queremos proyeccion ortogonal
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(perpectiva){
			glOrtho(-40.0, 40.0, -40.0, 40.0, 1, 1000);
		}else{
			gluPerspective(27.5, 1.0, 1, 1000);
		}
	}
private:

	//Calcula en función de eye, look, up los atributos u,v,n
	void setModelViewMatrix(){
		//Calculamos n
		n = eye->clona();
		n->resta(look);
		n->normaliza();
		//Calculamos u
		u = up->productoVectorial(n);
		u->normaliza();
		//Calculamos v
		v = n->productoVectorial(u);

		p1 = n->clona();
		p2 = u->clona();
		p3 = v->clona();

		//Obtenemos matriz de vista
		// Camera set up
		glMatrixMode(GL_MODELVIEW);
		aplicaMatriz();
		glLoadMatrixd(m);

	}
	void aplicaMatriz(){
		m[0] = u->getX();
		m[1] = v->getX();
		m[2] = n->getX();
		m[3] = 0;
		m[4] = u->getY();
		m[5] = v->getY();
		m[6] = n->getY();
		m[7] = 0;
		m[8] = u->getZ();
		m[9] = v->getZ();
		m[10] = n->getZ();
		m[11] = 0;
		m[12] = -1*eye->productoEscalar(u);
		m[13] = -1*eye->productoEscalar(v);
		m[14] = -1*eye->productoEscalar(n);
		m[15] = 1;		
	}
};

#endif //__CAMARA_H