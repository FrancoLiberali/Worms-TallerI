#ifndef __MOVING_FINISHED_ERROR_H__
#define __MOVING_FINISHED_ERROR_H__

class MovingFinished : public std::exception{
	public:
		// Excepcion de aviso de finalizacion de un proceso de movimiento del gusano
		MovingFinished() noexcept {}
		
		virtual ~MovingFinished() noexcept {}
};

#endif
