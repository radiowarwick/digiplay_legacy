#include "AudioWallItem.h"

AudioWallItem::AudioWallItem(QWidget* parent, const char* name) :
        QPushButton::QPushButton(parent,name) {
    QObject::connect(this,SIGNAL(pressed()),this,SLOT(play()));
    this->addCounter(this);
}

AudioWallItem::~AudioWallItem() {

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
    switch (_state) {
        case STATE_STOP:
            Audio::InputRaw::play();
            updateButton();
            break;
        case STATE_PLAY:
            Audio::InputRaw::stop();
            updateButton();
            break;
        case STATE_PAUSE:
            break;
    }
}

void AudioWallItem::onSetSample() {
    updateButton();
}

void AudioWallItem::onSetState() {
    updateButton();
}

void AudioWallItem::onSetTotalSamples() {

}

void AudioWallItem::updateButton() {
    unsigned long smpl = Audio::Counter::_currentSample;
    if (text == "") {
        QPushButton::setText("");
        QPushButton::setPaletteForegroundColor(QColor(QRgb(0)));
        QPushButton::setPaletteBackgroundColor(QColor(QRgb(12632256)));
        QPushButton::setEnabled(false);
        return;
    }
    switch (_state) {
        case STATE_STOP:
            QPushButton::setText(text);
            QPushButton::setPaletteForegroundColor(fgColour);
            QPushButton::setPaletteBackgroundColor(bgColour);
            QPushButton::setEnabled(true);
            break;
        case STATE_PLAY:
            QPushButton::setText("PLAYING\n" 
                    + dps_prettyTime(_totalSamples - smpl));
            QPushButton::setPaletteForegroundColor(QColor(QRgb(16776960)));
            QPushButton::setPaletteBackgroundColor(QColor(QRgb(16711680)));
            QPushButton::setEnabled(true);
            break;
        case STATE_PAUSE:
            break;
    }
}
