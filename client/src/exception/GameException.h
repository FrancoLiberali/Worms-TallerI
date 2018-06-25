#ifndef __GAME_EXCEPTION__
#define __GAME_EXCEPTION__
#include <string>

/*
* @Class GameException
* Excepción lanzada ante cualquier error en el juego, principalemente al cargar los recursos.
*/

class GameException : public std::exception {
private:
    std::string description;

public:
    GameException(char const* description);
    const char* what() const noexcept;

};

#endif 
