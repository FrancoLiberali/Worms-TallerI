#ifndef __ROTATING_FINISHED_ERROR_H__
#define __ROTATING_FINISHED_ERROR_H__

class RotatingFinished : public std::exception{
	public:
		// Excepcion de aviso de finalizacion de un proceso de rotacion del gusano
		RotatingFinished() noexcept {}
		
		virtual ~RotatingFinished() noexcept {}
};

#endif
