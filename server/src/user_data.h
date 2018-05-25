#ifndef __USER_DATA_H__
#define __USER_DATA_H__

struct UserData{
	public:
		int indicator;
		void* pointer;
		
		UserData(int indicator_e, void* pointer_e) : indicator(indicator_e), pointer(pointer_e){} 
};

#endif
