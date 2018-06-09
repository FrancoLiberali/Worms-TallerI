#ifndef __ROTATING_FINISHED_ERROR_H__
#define __ROTATING_FINISHED_ERROR_H__

class RotatingFinished : public std::exception{
	public:
		RotatingFinished() noexcept {}
		
		virtual ~RotatingFinished() noexcept {}
};

#endif
