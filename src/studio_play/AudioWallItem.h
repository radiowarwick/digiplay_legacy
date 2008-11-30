#ifndef CLASS_AUDIOWALLITEM
#define CLASS_AUDIOWALLITEM

#include <qpushbutton.h>

#include "audio/InputRaw.h"
#include "audio/Counter.h"

#include "dps.h"

struct AudioWallItemSpec {
	AudioWallItemSpec() {
		file = "";
		start = 0;
		end = 0;
		text = "";
	}
    QString file;
    unsigned long start;
    unsigned long end;
    QString text;
    QColor fgColour;
    QColor bgColour;
};


class AudioWallItem :   public QPushButton,
                        public Audio::InputRaw,
                        public Audio::Counter {
    Q_OBJECT
    public:
        AudioWallItem(QWidget* parent, const char* name);
        ~AudioWallItem();
        void set(AudioWallItemSpec& pItem);
        void setFont(QFont &F);
        void setBackgroundColour(QColor &C);
        void setForegroundColour(QColor &C);
        void setText(QString T);
        void update() {updateButton();}

    public slots:
        void play();

    private:
        void onSetSample();
        void onSetState();
        void onSetTotalSamples();

        void updateButton(bool force = false);

        QString text;
        QColor bgColour;
        QColor fgColour;
        QFont font;
        
        bool newItemAvailable;
        AudioWallItemSpec newItem;
};

#endif
