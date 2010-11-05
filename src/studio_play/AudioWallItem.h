#ifndef CLASS_AUDIOWALLITEM
#define CLASS_AUDIOWALLITEM

#include <QtGui/QPushButton>

#include "audiolib/ProcessLink.h"
#include "audiolib/ProcessMixer.h"
#include "audiolib/Input.h"
#include "audiolib/InputFile.h"
#include "audiolib/Counter.h"

#include "dps.h"

enum ItemFileType {
    ITEM_FILETYPE_RAW,
    ITEM_FILETYPE_FLAC
};

struct AudioWallItemSpec {
	AudioWallItemSpec() {
		mFile = "";
        mType = ITEM_FILETYPE_RAW;
		mStart = 0;
		mEnd = 0;
		mText = "";
	}
    QString mFile;
    enum ItemFileType mType;
    unsigned long mStart;
    unsigned long mEnd;
    QString mText;
    QString mStyle;
};

class AudioWallItem :   public QPushButton,
                        public Audio::ProcessLink,
                        public Audio::Counter {
    Q_OBJECT
    public:
        AudioWallItem(QWidget* parent);
        ~AudioWallItem();
        void set(AudioWallItemSpec& pItem);
        void setText(QString T);
        void update() {updateButton();}

    public slots:
        void play();

    private:
        void onSetSample();
        void onSetState();
        void onSetTotalSamples();

        void updateButton(bool force = false);

        QString mButtonText;
        QString mStylesheet;

        bool mNewItemAvailable;
        AudioWallItemSpec mNewItem;
        Audio::Input * mInputModule;
};

#endif
