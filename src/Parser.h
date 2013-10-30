/*
 * Parser.h
 *
 *  Created on: 25/10/2013
 *      Author: agu
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <string>

namespace std{

class Parser {
private:
	string mensaje;
public:
	Parser();
	virtual ~Parser();
	string saludo();

};
}


#endif /* PARSER_H_ */
