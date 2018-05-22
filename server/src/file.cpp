#include "file.h"
#include "file_error.h"

File::File(const char* filepath_entry, std::fstream::openmode mode) : 
	file(std::fstream(filepath_entry, mode)), filepath(filepath_entry){
	if (file.fail()){
		throw FileError("Error al abrir el archivo");
	}
}

File::~File() noexcept{
	file.close();
}

void File::write(const char* msj, size_t len){
	file.write(msj, len);
	if (file.fail()){
		throw FileError("Al archivo %s no se le pudo escribir el mensaje %s.", 
		this->filepath, msj);
	}
}

void File::read(char* to, size_t len){
	file.read(to, len);
	if (file.fail() && !file.eof()){
		throw FileError("Al archivo %s no se le pudo leer un largo %i.", 
		this->filepath, (int)len);
	}
}

bool File::getline(char* buff, std::streamsize max_len,const char delim){
	file.getline(buff, max_len, delim);
	if (file.fail()){
		throw FileError(
		"Leer linea de %s con el delim '%c' leyo %i caracts sin encontrarlo.",
		this->filepath, delim, (int)max_len);
	}
	return (!file.eof());
}

bool File::eof() const noexcept{
	return file.eof();
}

void File::seekg(std::streamoff off, std::ios_base::seekdir way){
	file.seekg(off, way);
	if (file.fail()){
		throw FileError(
		"Al archivo %s no se le pudo asignar una nueva posicion.",
		this->filepath);
	}
}

std::streampos File::tellg(){
	std::streampos pos = file.tellg();
	if (file.fail()){
		throw FileError(
		"Al archivo %s no se le pudo ver la posicion en la que se encuentra.",
		this->filepath);
	}
	return pos;
}

unsigned int File::len(){
	this->seekg(0, this->file.end);
    unsigned int length = this->tellg();
    this->seekg(0, this->file.beg);
	return length;
}


