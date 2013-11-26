/*
 * TestKMeans.cpp
 *
 *  Created on: 22/11/2013
 *      Author: agu
 */

#include "TestKMeans.h"
using namespace std;

TestKMeans::TestKMeans() {

	//this->generarPuntos();
	//this->generarSemillas();
	double nums1[] = { 1, 2, 3 };
	double nums2[] = { 1, 3, 6 };
	double nums3[] = { 6, 15, 9 };
	double nums4[] = { 6, 16, 12 };
	vector<double> frecPond1(nums1, nums1 + sizeof(nums1) / sizeof(double));
	vector<double> frecPond2(nums2, nums2 + sizeof(nums2) / sizeof(double));
	vector<double> frecPond3(nums3, nums3 + sizeof(nums3) / sizeof(double));
	vector<double> frecPond4(nums4, nums4 + sizeof(nums4) / sizeof(double));
	Punto* punto1=new Punto(frecPond1, 1);
	Punto* punto2=new Punto(frecPond2, 2);
	Punto* punto3=new Punto(frecPond3, 3);
	Punto* punto4=new Punto(frecPond4, 4);
	Punto* semilla1=new Punto(frecPond2, 2);
	Punto* semilla2=new Punto(frecPond3, 3);
	this->puntos.push_back(*punto1);
	this->puntos.push_back(*punto2);
	this->puntos.push_back(*punto3);
	this->puntos.push_back(*punto4);
	this->semillas.push_back(*semilla1);
	this->semillas.push_back(*semilla2);
	delete punto1;
	delete punto2;
	delete punto3;
	delete punto4;
}

TestKMeans::~TestKMeans() {
	delete this->kMeans;
}

void TestKMeans::generarPuntos() {

	Punto* puntoTemp;
	double nums[] = { 1, 2, 3 };
	vector<double> frecPond(nums, nums + sizeof(nums) / sizeof(double));
	for (unsigned int i = 0; i < this->cantPuntos; i++) {
		//generarFrecPond(frecPond, i);
		puntoTemp = new Punto(frecPond, i);
		this->puntos.push_back(*puntoTemp);

		delete puntoTemp;
	}
}
void TestKMeans::generarFrecPond(vector<double> &frecPond, unsigned int i) {

	for (unsigned int j = 0; j < frecPond.size(); ++j) {
		frecPond[j] = frecPond[j] * i;
	}

}

void TestKMeans::generarSemillas() {

	for (unsigned int j = 0; j < this->cantSemillas; ++j) {
			this->semillas[j]=this->puntos[rand()%this->puntos.size()];
		}

}
vector<Cluster*> TestKMeans::getResultadoKMeans(){
	this->kMeans=new KMeans(&this->puntos,3,&this->semillas,true);
	this->kMeans->calcularClusters();
	return this->kMeans->getClusters();

}

unsigned int TestKMeans::getCantSemillas(){
	return this->cantSemillas;
}

unsigned int TestKMeans::getCantPuntos(){
	return this->cantPuntos;
}

vector<Punto> TestKMeans::getPuntos(){
	return this->puntos;
}
vector<Punto> TestKMeans::getSemillas(){
	return this->semillas;
}
