/*
 * Parser.cpp
 *
 *  Created on: 25/10/2013
 *      Author: agu
 */

#include "Parser.h"
namespace std{

Parser::Parser() {
	this->mensaje="hola";

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}
string Parser::saludo(){
	return this->mensaje;

}

}
