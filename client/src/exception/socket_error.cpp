#include "socket_error.h"
#include <cerrno>
#include <cstring>
#include <clocale>
#include <cstdio>
#include <cstdarg>

SocketError::SocketError(const char* format, ...) noexcept{
	int _errno = errno;
	
	va_list args;
	va_start(args, format);
	int s = vsnprintf(msg_error, BUF_LEN, format, args);
	va_end(args);
	
	strncpy(msg_error + s, std::strerror(_errno), BUF_LEN - s);
	msg_error[BUF_LEN - 1] = 0;
}

SocketError::~SocketError() noexcept{
}

const char* SocketError::what() const noexcept{
	return msg_error;
}
