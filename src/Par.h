/*
 * Par.h
 *
 *  Created on: 28/11/2013
 *      Author: fabri
 *      #include <cstdbool>
 */

#ifndef Par_H_
#define Par_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

using namespace std;


class Par {

private:
	float pesoTotal;
	string palabra;

public:
	Par();
	Par(float pesoTotal, string palabra);
	float getPesoTotal();
	string getPalabra();
	bool operator==(const Par& otroPar) const;
	bool operator!=(const Par& otroPar) const;
	bool operator< (const Par& otroPar) const;
	bool operator> (const Par& otroPar) const;
	bool operator<=(const Par& otroPar) const;
	bool operator>=(const Par& otroPar) const;
};
#endif /* Par_H_ */
