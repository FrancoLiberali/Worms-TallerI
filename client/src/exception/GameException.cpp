#include "GameException.h"

GameException::GameException(char const* description)
    : std::exception(), description(description) {
}

const char* GameException::what() const noexcept{
    return this->description.c_str();
}