#ifndef __SDL_EXCEPTION_H__
#define __SDL_EXCEPTION_H__
#include <string>
#include <exception>

/*
* @Class SdlException
* Excepción lanzada ante cualquier error producido en el manejo de la libreria SDL.
*/
class SdlException : public std::exception {
public:
    SdlException(const char* description, const char* sdlError);
    SdlException(const char* description);

    const char* what() const noexcept;
private:
    std::string description;
};

#endif
