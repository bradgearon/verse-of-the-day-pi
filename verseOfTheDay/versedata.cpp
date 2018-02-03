#include "versedata.h"

QString VerseData::getForegroundImage() const { return foregroundImage; }

void VerseData::setForegroundImage(const QString &value) {
  foregroundImage = value;
  emit foregroundImageUpdated();
}

void VerseData::loadData(const QString &value) {
  images = std::vector<ImageSet>();
  QRegExp findImageSrc("src=\"(([^\"]+)(\\.jpg|\\.png))\"");
  int pos = 0;
  int i = 1;

  ImageSet set;
  while ((pos = findImageSrc.indexIn(value, pos)) != -1) {
    auto cap = findImageSrc.cap(1);
    pos += findImageSrc.matchedLength();

    if (i % 2 != 0) {
      set.BackgroundImage = cap.toStdString();
    } else {
      set.ForegroundImage = cap.toStdString();
      images.push_back(set);
      set = ImageSet();
    }
    i++;
  }

  setSelectedDay(0);
}

bool VerseData::getCanGoBack() const { return canGoBack; }

void VerseData::setCanGoBack(bool value) {
  canGoBack = value;
  emit canGoBackUpdated();
}

bool VerseData::getCanGoForward() const { return canGoForward; }

void VerseData::setCanGoForward(bool value) {
  canGoForward = value;
  emit canGoForwardUpdated();
}

qint32 VerseData::getSelectedDay() const { return selectedDay; }

void VerseData::setSelectedDay(const qint32 &value) {
  selectedDay = value;
  emit selectedDayUpdated();

  auto selected = static_cast<size_t>(selectedDay);
  auto image = images[selected];

  setBackgroundImage(QString::fromStdString(image.BackgroundImage));
  setForegroundImage(QString::fromStdString(image.ForegroundImage));

  auto last = static_cast<qint32>(images.size() - 1);
  setCanGoBack(selectedDay < last);
  setCanGoForward(selectedDay > 0);
}

QString VerseData::getBackgroundImage() const { return backgroundImage; }

void VerseData::setBackgroundImage(const QString &value) {
  backgroundImage = value;
  emit backgroundImageUpdated();
}
