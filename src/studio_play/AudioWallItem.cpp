#include <QtGui/QApplication>

#include "AudioWallItem.h"

AudioWallItem::AudioWallItem(QWidget* parent) :
        QPushButton::QPushButton(parent) {
    mInputModule = 0;
    QObject::connect(this,SIGNAL(pressed()),this,SLOT(play()));
    mNewItemAvailable = false;
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
            if (pItem.mFile != "") {
                mStylesheet = pItem.mStyle;
                mButtonText = pItem.mText;
                if (!mInputModule) {
                    mInputModule = new Audio::InputFile();
                    mInputModule->patch(OUT0, this, IN0);
                    mInputModule->addCounter(this);
                }
                mInputModule->load(pItem.mFile.toStdString(),
                                   pItem.mStart, pItem.mEnd);
            }
            else {
                mButtonText = "";
            }
            updateButton(true);
            break;
        }
        case STATE_PLAY:
        case STATE_PAUSE: {
            mNewItemAvailable = true;
            mNewItem = pItem;
            break;
        }
    }
}

void AudioWallItem::setText(QString T) {
    mButtonText = T;
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
            if (mNewItemAvailable) {
                mNewItemAvailable = false;
                set(mNewItem);
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
    if (_state == STATE_STOP && mNewItemAvailable) {
        mNewItemAvailable = false;
        set(mNewItem);
    }
    updateButton();
}

void AudioWallItem::onSetTotalSamples() {
    updateButton();
}

void AudioWallItem::updateButton(bool force) {
    unsigned long smpl = Audio::Counter::_currentSample;

    if (mButtonText == "") {
        QPushButton::setText("");
        QString style = "QPushButton { background-color : rgb(0,0,0); "
                        "              color : rgb(192,192,192); }";
        QPushButton::setStyleSheet(style);
        QPushButton::setEnabled(false);
        return;
    }

    QString text;
    QString style;
    switch (_state) {
        case STATE_STOP: {
            text = text + "\n" + dps_prettyTime(_totalSamples).c_str();
            style = mStylesheet;
            break;
        }
        case STATE_PLAY: {
            text = QString("PLAYING\n")
                            + dps_prettyTime(_totalSamples - smpl).c_str();
            style = "QPushButton { background-color : rgb(255,255,0); "
                            "              color : rgb(255,0,0); }";
            break;
        }
        case STATE_PAUSE: {
            break;
        }

    }
    QPushButton::setText(text);
    QPushButton::setStyleSheet(style);
    QPushButton::setEnabled(true);
}
