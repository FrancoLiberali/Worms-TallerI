#ifndef __USER_DATA_H__
#define __USER_DATA_H__

struct UserData{
	public:
		int indicator;
		void* pointer;
		
		// Estructura que posee un int que indica de que tipo
		// es el puntero al que apunta su void*
		UserData(int indicator_e, void* pointer_e) : indicator(indicator_e), pointer(pointer_e){} 
};

#endif
