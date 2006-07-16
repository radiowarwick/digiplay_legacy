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

#define AUDIOWALL_INDEX_OUT_OF_BOUNDS 12000

struct AudioWallItem {
	QString text;
	QFont font;
	QColor color;
};

class AudioWallManager : public QObject {
	Q_OBJECT
	public:
		AudioWallManager( Connection *C );
		~AudioWallManager();
		AudioWallItem& operator[] (unsigned int index);
		AudioWallItem& at(unsigned int index);
		void setUser( QString username );
		void changeWall( unsigned int index );

	private:
		QString _username;
		vector<AudioWallItem> _items;
};

#endif
