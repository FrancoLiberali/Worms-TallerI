#include "protected_queue.h"

#ifndef __MOK_PROXY_H__
#define __MOK_PROXY_H__

class MokProxy{
	public:
		MokProxy();
		
		~MokProxy() noexcept;
		
		void close_communication();
		
		void receive_event(ProtectedQueue& queue);
		
		void send_state_change(int gusano_number, char new_state);
		
		void send_position(int gusano_number, int x, int y, int direction, int angle);
		
};

#endif
