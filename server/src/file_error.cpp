#include "file_error.h"
#include <cerrno>
#include <cstring>
#include <clocale>
#include <cstdio>
#include <cstdarg>

FileError::FileError(const char* format, ...) noexcept{
	int _errno = errno;
	
	va_list args;
	va_start(args, format);
	int s = vsnprintf(msg_error, BUF_LEN, format, args);
	va_end(args);
	
	strncpy(msg_error + s, std::strerror(_errno), BUF_LEN - s);
	msg_error[BUF_LEN - 1] = 0;
}

FileError::~FileError() noexcept{
}

const char* FileError::what() const noexcept{
	return msg_error;
}
