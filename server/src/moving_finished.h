#ifndef __MOVING_FINISHED_ERROR_H__
#define __MOVING_FINISHED_ERROR_H__

class MovingFinished : public std::exception{
	public:
		MovingFinished() noexcept {}
		
		virtual ~MovingFinished() noexcept {}
};

#endif
