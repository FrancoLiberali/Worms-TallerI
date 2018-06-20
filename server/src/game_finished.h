#ifndef __GAME_FINISHED_ERROR_H__
#define __GAME_FINISHED_ERROR_H__

class GameFinished : public std::exception{
	public:
		GameFinished() noexcept {}
		
		virtual ~GameFinished() noexcept {}
};

#endif
