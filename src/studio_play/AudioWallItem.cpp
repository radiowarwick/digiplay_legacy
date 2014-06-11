#include <qapplication.h>

#include "AudioWallItem.h"

AudioWallItem::AudioWallItem(QWidget* parent, const char* name) :
        QPushButton::QPushButton(parent,name) {
    mInputModule = 0;
    QObject::connect(this,SIGNAL(pressed()),this,SLOT(play()));
    newItemAvailable = false;
}

AudioWallItem::~AudioWallItem() {
    // Stop audiowall item playing if it's still playing to allow it to be
    // cleanly destroyed. This isn't ideal as accidental logout could affect
    // what is going out on air.
    if (mInputModule) {
        if (_state != STATE_STOP) {
            mInputModule->stop();
        }
        mInputModule->unpatch(OUT0);
        delete mInputModule;
    }
}

void AudioWallItem::set(AudioWallItemSpec& pItem) {
	switch (_state) {
		case STATE_STOP: {
			if (pItem.file != "") {
				bgColour = pItem.bgColour;
				fgColour = pItem.fgColour;
				text = pItem.text;
                
                if (!mInputModule) {
                    mInputModule = new Audio::InputFile();
                    mInputModule->patch(OUT0, this, IN0);
                    mInputModule->addCounter(this);
                }
				mInputModule->load(pItem.file.ascii(), pItem.start, pItem.end);
			}
			else {
				text = "";
			}
			updateButton(true);
			break;
		}
		case STATE_PLAY: 
		case STATE_PAUSE: {
			newItemAvailable = true;
			newItem = pItem;
			break;
		}
	}
}

void AudioWallItem::setFont(QFont &F) {
    font = F;
    updateButton();
}

void AudioWallItem::setBackgroundColour(QColor &C) {
    bgColour = C;
    updateButton();
}

void AudioWallItem::setForegroundColour(QColor &C) {
    fgColour = C;
    updateButton();
}

void AudioWallItem::setText(QString T) {
    text = T;
    updateButton();
}

void AudioWallItem::play() {
    ProcessMixer* P = dynamic_cast<ProcessMixer*>(
                                Audio::ProcessLink::connectedDevice(OUT0));
    if (!P) {
        cout << "ProcessMixer is not valid!!" << endl;
    }
    switch (_state) {
        case STATE_STOP:
            if (P && P->activeChannels() < 3) {
                mInputModule->play();
                updateButton();
            }
            break;
        case STATE_PLAY:
            mInputModule->stop();
            if (newItemAvailable) {
            	newItemAvailable = false;
            	set(newItem);
            }
            else {
            	updateButton();
            }
            break;
        case STATE_PAUSE:
            break;
    }
}

void AudioWallItem::onSetSample() {
    updateButton();
}

void AudioWallItem::onSetState() {
    if (_state == STATE_STOP && newItemAvailable) {
    	newItemAvailable = false;
    	set(newItem);
    }
    updateButton();
}

void AudioWallItem::onSetTotalSamples() {
    updateButton();
}

void AudioWallItem::updateButton(bool force) {
    unsigned long smpl = Audio::Counter::_currentSample;
    // Force an update
    if (force) {
    	qApp->tryLock();
    }
    else {
    	// Just try and update
    	if (! qApp->tryLock()) return;
    }
    
    if (text == "") {
        QPushButton::setText("");
        QPushButton::setPaletteForegroundColor(QColor(QRgb(0)));
        QPushButton::setPaletteBackgroundColor(QColor(QRgb(12632256)));
        QPushButton::setEnabled(false);
        qApp->unlock();
        return;
    }
    switch (_state) {
        case STATE_STOP:
            QPushButton::setText(text + "\n" + dps_prettyTime(_totalSamples));
            QPushButton::setPaletteForegroundColor(fgColour);
            QPushButton::setPaletteBackgroundColor(bgColour);
            QPushButton::setEnabled(true);
            break;
        case STATE_PLAY:
            if (!(smpl - _lastSample < 1764)) {
                QPushButton::setText("PLAYING\n" 
                    + dps_prettyTime(_totalSamples - smpl));
                QPushButton::setPaletteForegroundColor(QColor(QRgb(16776960)));
                QPushButton::setPaletteBackgroundColor(QColor(QRgb(16711680)));
                QPushButton::setEnabled(true);

                _lastSample = smpl;
            }
            break;
        case STATE_PAUSE:
            break;
    }
    qApp->unlock();
}
