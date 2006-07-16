#ifndef CLASS_AUDIO_WALL_MANAGER
#define CLASS_AUDIO_WALL_MANAGER

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class AudioWallManager {
	public:
		AudioWallManager( Connection *C );
		~AudioWallManager();
		void setUser( string username );

	private:
		string _username;
};

#endif
