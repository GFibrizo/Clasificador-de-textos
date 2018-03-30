/*
 * Par.cpp
 *
 *  Created on: 28/11/2013
 *      Author: fabri
 */

#include "Par.h"

Par::Par(){
}

Par::Par(float pesoTotal, string palabra){
	this->pesoTotal = pesoTotal;
	this->palabra = palabra;
}

/**********************************************************************/
/**********************************************************************/

float Par::getPesoTotal(){
	return this->pesoTotal;
}

/**********************************************************************/
/**********************************************************************/

string Par::getPalabra(){
	return this->palabra;
}

/**********************************************************************/
/**********************************************************************/


bool Par::operator==(const Par& otroPar) const {
	if (this->pesoTotal == otroPar.pesoTotal) return true;
	return false;
}

/**********************************************************************/
/**********************************************************************/


bool Par::operator!=(const Par& otroPar) const {
	return (this->pesoTotal != otroPar.pesoTotal);
}

/**********************************************************************/
/**********************************************************************/


bool Par::operator< (const Par& otroPar) const {
	return (this->pesoTotal < otroPar.pesoTotal); 
}

/**********************************************************************/
/**********************************************************************/


bool Par::operator> (const Par& otroPar) const {
	return (this->pesoTotal > otroPar.pesoTotal);
}

/**********************************************************************/
/**********************************************************************/


bool Par::operator<=(const Par& otroPar) const {
	return (this->pesoTotal <= otroPar.pesoTotal);
}

/**********************************************************************/
/**********************************************************************/


bool Par::operator>=(const Par& otroPar) const {
	return (this->pesoTotal >= otroPar.pesoTotal);
}
