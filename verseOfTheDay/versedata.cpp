#include "versedata.h"

QByteArray VerseData::getForegroundImage() const { return foregroundImage; }

void VerseData::setForegroundImage(const QByteArray &value) {
  foregroundImage = value;
}

QByteArray VerseData::getBackgroundImage() const { return backgroundImage; }

void VerseData::setBackgroundImage(const QByteArray &value) {
  backgroundImage = value;
}
