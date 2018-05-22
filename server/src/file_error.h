#include <typeinfo>

#define BUF_LEN 256
#ifndef __FILE_ERROR_H__
#define __FILE_ERROR_H__

class FileError : public std::exception{
	private:
		char msg_error[BUF_LEN];
		
	public:
		explicit FileError(const char* format, ...) noexcept;
		
		//Devuelve el mensaje de error de la excepcion.
		virtual const char* what() const noexcept;
		
		virtual ~FileError() noexcept;
};
#endif
