#ifndef CLASS_AUDIO_WALL_MANAGER
#define CLASS_AUDIO_WALL_MANAGER

#include <vector>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include <qobject.h>
#include <qstring.h>
#include <qfont.h>
#include <qcolor.h>

#include "AudioWall.h"

class AudioWallManager : public QObject {
	Q_OBJECT
	public:
		AudioWallManager( AudioWall *A, Connection *C );
		~AudioWallManager();
		void load(unsigned int cartset);

	private:
		AudioWall *_A;
		Connection *_C;
		QString _username;
		vector<AudioWallPage*> _pages;
};

#endif
