#ifndef __ROTATION_FINISHED_ERROR_H__
#define __ROTATION_FINISHED_ERROR_H__

class RotationFinished : public std::exception{
	public:
		RotationFinished() noexcept {}
		
		virtual ~RotationFinished() noexcept {}
};

#endif
