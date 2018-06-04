#include <typeinfo>

#define BUF_LEN 256
#ifndef __SOCKET_ERROR_H__
#define __SOCKET_ERROR_H__

class SocketError : public std::exception{
	private:
		char msg_error[BUF_LEN];
		
	public:
		explicit SocketError(const char* format, ...) noexcept;
		
		virtual const char* what() const noexcept;
		
		virtual ~SocketError() noexcept;
};
#endif
