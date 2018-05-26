#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

#include <queue>
#include <string>

class EventHandler {
private:
	std::queue<std::string> eventQueue;
public:
	void add(std::string event);
  	bool empty();
  	std::string get();
};

#endif