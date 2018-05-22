#include <fstream> 
#include <istream>
#include <iostream>

#ifndef __FILE_H__
#define __FILE_H__
class File{
	private:
		void seekg(std::streamoff off, std::ios_base::seekdir way);
		std::streampos tellg();
		
	protected:
		std::fstream file;
		const char* filepath;
		
	public:
		//Construye el file de la ruta filepath en el modo mode.
		//o lanza OpenFileError en caso de no ser posible abrirlo.
		File(const char* filepath, std::fstream::openmode mode);
		
		~File() noexcept;
		
		//Escribe en el archivo msj 
		// o lanza FileError en caso de no ser posible.
		void write(const char* msj, size_t len);
		
		//Lee del archivo un largo len y lo guarda en to 
		// o lanza FileError en caso de no ser posible.
		void read(char* to, size_t len);
		
		// Lee del archivo hasta encontrar un caracter delim o el EOF.
		// Post: Lanza FileError si en el largo maximo max_len no se llego a encontrar
		// ninguna de estas dos cosas.
		// Retorna true si el valor encontrado fue EOF y false si encontro delim.
		bool getline(char* buff, std::streamsize max_len, const char delim);
		
		// Retorna true si en la lectura anterior se encontro el caracter EOF 
		// o false en caso contrario.
		bool eof() const noexcept;
		
		// Devuelve el largo del archivo, o lanza FileError
		// en caso de que no se pueda mover la posicion del archivo.
		// Post: la posicion del archivo se encuentra al 
		// principio del mismo si se puede calcular el largo.
		unsigned int len();
};

#endif
