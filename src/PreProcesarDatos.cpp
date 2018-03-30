
/*
 * PreProcesarDatos.cpp
 *
 *  Created on: 03/11/2013
 *      Author: agu, fabri
 */

#include "PreProcesarDatos.h"
typedef map<string,int> hash;
typedef map<string,float> hash2;


/**********************************************************************/
/**********************************************************************/


// Devuelve en dir el directorio indicado en la ruta

void PreProcesarDatos::relative_dir_base_split(const string& path, string& dir, string& nombre) {
  std::string::size_type slash_pos = path.rfind("/"); //Find the last slash
  if (slash_pos != std::string::npos) {  // If there is a slash
    slash_pos++;
    dir = path.substr(0, slash_pos); // Directory is before slash
    nombre = path.substr(slash_pos); // And obviously, the file is after
  } else { // Otherwise, there is no directory present
    dir.clear();
    nombre = path;
  }
}

/**********************************************************************/
/**********************************************************************/


//Primer Constructor de la Clase PreProcesarDatos
PreProcesarDatos::PreProcesarDatos(const char* ruta) {
	this->invalidos= "¡!#$%&'(	 )*+,‘’”“-.:;<=>¿?@[]^_`{|}~/\\\"\n´~ÑÞ`1234567890\r \t \\ \r\n";
	LectorDirectorios * lecDirectorio= new LectorDirectorios();
	// Levanta archivos del directorio:
	this->vector_archivos = lecDirectorio->leerDir (ruta);
	this->verifStopWord= new VerificadorStopWords(DIR_STOP_WORDS);
	this->archivoHashSecundario.open(DIR_FILE_HASH_2, ios_base::out | ios_base::app); // modo append
	this->verifDocDiferentes=0;
		// Si no se puede abrir:
	if (!this->archivoHashSecundario.is_open()){
		throw std::ios_base::failure("El archivo no se abre");
	}
	string a;
	this->relative_dir_base_split(ruta,this->directorio,a);
	delete lecDirectorio;
}

/**********************************************************************/
/**********************************************************************/

//Segundo Constructor de la Clase PreProcesarDatos
PreProcesarDatos::PreProcesarDatos(hash hashPorParametro) {
	cout<<"entro a preprocesar datos"<<endl;
	this->invalidos= "¡!#$%&'(	 )*+,‘’”“-.:;<=>¿?@[]^_`{|}~/\\\"\n´~ÑÞ`1234567890\r \t \\ \r\n";
	this->verifStopWord= new VerificadorStopWords(DIR_STOP_WORDS);
	this->verifDocDiferentes=0;
	this->hashPrincipal = hashPorParametro;
}

/**********************************************************************/
/**********************************************************************/


// Tercer Constructor
PreProcesarDatos::PreProcesarDatos(){
	
}

/**********************************************************************/
/**********************************************************************/


// Destructor de la clase PreProcesarDatos
PreProcesarDatos::~PreProcesarDatos() {
	delete this->verifStopWord;
	archivoHashSecundario.close();
}

/**********************************************************************/
/**********************************************************************/

// Pasa a minusculas los caracteres del string str
void PreProcesarDatos::pasarAminusculas(string& str) {
  transform(str.begin(), str.end(), str.begin(), ::tolower);
}

/**********************************************************************/
/**********************************************************************/


// Recibe un hash con valores del tipo int.
// Si la clave no esta en el hash, la agrega asociada a un valor 0.
// Si la clave esta en el hash, aumenta en 1 el valor asociado.
void PreProcesarDatos::agregarElementoAHash(hash& hash, string clave){
	if (hash.count(clave) > 0){
		 hash[clave]=hash[clave]+ 1;
		 return;
	}
	hash[clave] = 1;
}

/**********************************************************************/
/**********************************************************************/


// Recibe un hash con valores del tipo float
// Si la clave no esta en el hash, la agrega asociada a un valor 0.
// Si la clave esta en el hash, aumenta en 1 el valor asociado.
void PreProcesarDatos::agregarElementoAHash(hash2& hash, string clave){
	if (hash.count(clave) > 0){
		 hash[clave]=hash[clave]+ 1;
		 return;
	}
	hash[clave] = 1;
}

/**********************************************************************/
/**********************************************************************/

// Recibe un hash con valores del tipo float
// Si la clave no esta en el hash, la agrega asociada a un valor 0.
// Si la clave esta en el hash, aumenta en 1 el valor asociado.
void PreProcesarDatos::contarEnHash(hash2& hash, string clave){
	if (hash.count(clave) > 0){
		 hash[clave]=hash[clave]+ 1;
		 return;
	}
}

/**********************************************************************/
/**********************************************************************/


// Agrega una palabra como clave al hash. Si la palabra estaba entre el conjunto
// de claves, entonces aumenta su correspondiente valor en 1. Sino, agrega la clave
// al conjunto de claves y setea en 1 su valor correspondiente
void PreProcesarDatos::agregarElementoAHashPrincipal(hash& hash,string clave, bool cambio_doc){
	if (hash.count(clave) == 0) hash[clave] = 1;
	if (cambio_doc){
		hash[clave]=hash[clave]+ 1;	// Aumento cant de docs
		return;
	}
}

/**********************************************************************/
/**********************************************************************/


// Conviente un int a string
string PreProcesarDatos::numberToString(int number){
	stringstream ss;
	ss << number;
	string str = ss.str();
	return str;
}

/**********************************************************************/
/**********************************************************************/


// Convierte un float a string
string PreProcesarDatos::numberToString(float number){
	stringstream ss;
	ss << number;
	string str = ss.str();
	return str;
}

/**********************************************************************/
/**********************************************************************/


// Escribe el archivo secuencial intermedio que contiene los pares palabra,frecuencia
// de todas las palabras en un documento, a partir de un hash en memoria
void PreProcesarDatos::escribirArchivoDeHash(hash hash){
	string aux;
	for (hash::iterator it= hash.begin(); it != hash.end(); it++){
		aux.operator =(it->first);
		aux.append(",");
		aux.append(this->numberToString(it->second));
		aux.append(" ");
		this->archivoHashSecundario << aux;
	}
	this->archivoHashSecundario << ",/";
}

/**********************************************************************/
/**********************************************************************/


// Escribe el archivo que debe contener los vectores de frecuencias ponderadas
// de palabras de cada documento a partir de un hash en memoria
void PreProcesarDatos::escribirArchivoIndice(hash2 hash, ofstream& archivoIndice){
	string aux;
	archivoIndice.setf( ios::fixed, ios::floatfield );
	archivoIndice.precision(5);
	for (hash2::iterator it= hash.begin(); it != hash.end(); it++){
		archivoIndice << it->second <<",";
	}
	archivoIndice << endl;
}

/**********************************************************************/
/**********************************************************************/


// Genera, a partir de un conjunto de documentos el archivo final que
// contiene los vectores de frecuencias ponderadas correspondientes a cada
// documento
void PreProcesarDatos::preProcesarDatos(){
	string auxLinea;
	string palabra;
	unsigned int i;
	unsigned int ant_i = -1;
	cout<<"Iniciando proceso de parseo..."<<endl;
	for (i = 0; i < this->vector_archivos.size(); i++){
		if (this->vector_archivos[i].compare(".svn") == 0) continue;
		this->manejador = new ManejadorArchivos() ;
		this->manejador->abrirLectura(this->directorio+this->vector_archivos[i]);

		while (this->manejador->leerUnaLinea(auxLinea)){
			char *linea = new char[1024000];
			strcpy(linea, auxLinea.c_str());
			// auxPalabra va a ir conteniendo cada palabra sacando los tokens
			tokenizar(linea);
			char* auxPalabra = strtok(linea,this->invalidos);

			while ( auxPalabra != NULL ) {
					palabra = auxPalabra;
					pasarAminusculas(palabra);
					// Veo si es un stopword y sino lo agrego a hashes:
					if(!this->verifStopWord->verificarPalabra(palabra)){
						palabra = stem_palabra(palabra);
						if (palabra.length() > 1){
							agregarElementoAHashPrincipal(this->hashPrincipal, palabra, i != ant_i);
							agregarElementoAHash(this->hashSecundario, palabra);
							agregarElementoAHash(this->hashTF, palabra);
						}
					}
					auxPalabra = strtok (NULL, this->invalidos);
					ant_i = i;
			}
			delete []linea;
			delete auxPalabra;
		} // Termina de trabajar con ese archivo
		delete this->manejador;		
		escribirArchivoDeHash(this->hashSecundario);
		// Referencio la variable hash_secundario a un nuevo hash de un nuevo archivo
		hash nuevoHash;
		this->hashSecundario = nuevoHash;
	}
	this->archivoHashSecundario.close();
	reducirDimensionalidad();
	generarIndiceDocumentos();
	//CERRAR ARCHIVO DE HASH SECUNDARIO
}

/**********************************************************************/
/**********************************************************************/


//Reemplaza todos los caracteres de la linea que no sean letras por un espacio
void PreProcesarDatos::tokenizar(char* linea){

	int i = 0;
	int valor = linea[i];
	int largo = strlen(linea);

	while (i<largo){
		if (!( ((valor > 64) && (valor < 91)) || ((valor > 96) && (valor < 123)) ))
			linea[i] = ' ';
		i++;
		valor = (int) linea[i];
	}
}

/**********************************************************************/
/**********************************************************************/


//Devuelve la cadena de caracteres invalidos
const char* PreProcesarDatos::getInvalidos(){
	return this->invalidos;
}

/**********************************************************************/
/**********************************************************************/


//Lee los pares palabra,frecuencia del archivo file_hash2, los procesa y
//genera como salida el archivo indiceDocumentos que contiene los vectores
//de frecuencias poderadas de cada documento
void PreProcesarDatos::generarIndiceDocumentos(){
	string auxLinea;
	float frecPond;
	this->manejador = new ManejadorArchivos(); //posible perdida de memoria.
	this->manejador->abrirLectura(DIR_FILE_HASH_2);
	ofstream indiceDocumentos;
	indiceDocumentos.open(DIR_FILE_INDICE_FINAL, ios_base::out | ios_base::app);
	hash2 hashDocsEnMemoria = generarHashMemoria();//posible perdida de memoria
	string clave;
	char* aux;
	float frecuencia = 0;
	int i=0;

	while (this->manejador->leerUnaLineaIndice(auxLinea)) {
		char *linea = new char[1024000];
		strcpy(linea, auxLinea.c_str());
		aux = strtok(linea, ", ");
		i++;
		while (aux != NULL) {
			clave = aux;
			frecuencia = atof(strtok(NULL, ", "));
			if (hashPrincipal.count(clave) > 0){
				frecPond = calcular_TF_IDF(clave, frecuencia, 0);
				hashDocsEnMemoria[clave] = frecPond;
			}
			aux = strtok(NULL, ", ");
		}
		escribirArchivoIndice(hashDocsEnMemoria, indiceDocumentos);
		hash2 nuevoHash = generarHashMemoria();
		hashDocsEnMemoria = nuevoHash;
		delete []linea;
	}
	indiceDocumentos.close();
}

/**********************************************************************/
/**********************************************************************/


// Genera un nuevo hash en memoria con el vocabulario de palabras completo
hash2 PreProcesarDatos::generarHashMemoria() {
	hash2 hashDocsEnMemoria;
	for (hash::iterator it= this->hashPrincipal.begin(); it != this->hashPrincipal.end(); it++){
		if (it->second != 0) 
			hashDocsEnMemoria[it->first] = 0;//Linea dudosa
	}
	return hashDocsEnMemoria;
}

/**********************************************************************/
/**********************************************************************/


// Calcula el peso total mediante TFxIDF
float PreProcesarDatos::calcular_TF_IDF(string clave, float frecuencia, int tamVectorArchivos){
	if (vector_archivos.size() > 0 ){
		return (frecuencia * log10f(( (vector_archivos.size())) / (this->hashPrincipal[clave])));
	}
	return (frecuencia * log10f(( (tamVectorArchivos)) / (this->hashPrincipal[clave])));
}

/**********************************************************************/
/**********************************************************************/


// Aplica Stemming a palabras mediante el Algoritmo de Porter
string PreProcesarDatos::stem_palabra(string palabra){
	char *palabra_c = new char[palabra.length() + 1];
	strcpy(palabra_c, palabra.c_str());
	int final = stem(palabra_c, 0, strlen(palabra_c)-1);
	delete [] palabra_c;
	return palabra.substr(0,final);
}

/**********************************************************************/
/**********************************************************************/


// A partir de la ruta donde se encuentra el documento genera su vector de
// frecuencias ponderadas.
Punto PreProcesarDatos::procesarNuevoDocumento(string ruta, int tamVectorArchivos){
	string auxLinea;
	string palabra;
	hash2 hashNuevoDoc = generarHashMemoria();
	this->manejador = new ManejadorArchivos();
	this->manejador->abrirLectura(ruta);
	
	// Recupero nombre del archivo:
	string nombre, directorio;
	relative_dir_base_split(ruta,directorio,nombre);
	
	while (this->manejador->leerUnaLinea(auxLinea)){
		char *linea = new char[1024000];
		strcpy(linea, auxLinea.c_str());
		// auxPalabra va a ir conteniendo cada palabra sacando los tokens
		tokenizar(linea);
		char* auxPalabra = strtok(linea,this->invalidos);

		while ( auxPalabra != NULL ) {
			palabra = auxPalabra;
			pasarAminusculas(palabra);
			// Veo si es un stopword y sino lo agrego a hashes:
			if(!this->verifStopWord->verificarPalabra(palabra)){
				palabra = stem_palabra(palabra);
				if (palabra.length() > 1) contarEnHash(hashNuevoDoc, palabra);
			}
			auxPalabra = strtok (NULL, this->invalidos);
		}
		delete []linea;
		delete auxPalabra;
	}
	delete this->manejador;
	int i = 0;
	vector<float> vectorDoc;

	for (hash2::iterator it= hashNuevoDoc.begin(); it != hashNuevoDoc.end(); it++){
		vectorDoc.push_back(calcular_TF_IDF(it->first, it->second, tamVectorArchivos));
		i++;
	}
	
	Punto puntoNuevoDoc = Punto(vectorDoc, 10000000, nombre);
	// Falta ver como setear el numero del doc en la instancia de Punto
	return puntoNuevoDoc;
}

/**********************************************************************/
/**********************************************************************/

//Devuelve el hashPrincipal
map<string, int> PreProcesarDatos::obtenerHashVocabulario (){
	return hashPrincipal;
}

/*********************************************************************/
/**********************************************************************/


vector<string> PreProcesarDatos::getVectorArchivos(){
	return this->vector_archivos;	
}	

/**********************************************************************/
/**********************************************************************/

// Persistencia del Hash principal
void PreProcesarDatos::escribirArchivoDeHashPrincipal(hash hash){
	string aux;
	ofstream archivoHashPrincipal;
	archivoHashPrincipal.open(DIR_FILE_HASH_1, ios_base::out | ios_base::app);
	for (hash::iterator it= hash.begin(); it != hash.end(); it++){
		aux.operator = (it->first);
		aux.append(",");
		aux.append(this->numberToString(it->second));
		aux.append(",");
		archivoHashPrincipal << aux;
	}
	archivoHashPrincipal << ",/";
	archivoHashPrincipal.close();
	cout<<"cerrar archivo\n";
}

/**********************************************************************/
/**********************************************************************/


void PreProcesarDatos::reducirDimensionalidad(){
	priority_queue<Par> heap;
	int cantComponentes;
	float peso;
	Par datos;
	string clave;
	hash aux;
	
	// Se empieza a truncar recien a partir de los 1000 docs
	if (hashTF.size() < 10000) return;
	cantComponentes = 10000;

	// Pongo en un heap las claves con su valor total en el cuerpo de docs
	for (hash::iterator it= hashTF.begin(); it != hashTF.end(); it++){
		peso = calcular_TF_IDF(it->first, (float)it->second,0);
		//cout<< peso<< "\n";
		heap.push(Par(peso, it->first));
	}
	
	// Genero un hash solo con las palabras de mas peso
	for (int j = 0; j <= cantComponentes; j++) {
		datos = heap.top();
    clave = datos.getPalabra();
    aux[clave] = this->hashPrincipal[clave];
		heap.pop();
	}

	// Pongo como hashPrincipal el hash truncado aux
	hash aux2 = hashPrincipal;
	this->hashPrincipal = aux;
}
