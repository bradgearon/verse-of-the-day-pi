#ifndef VERSEDATA_H
#define VERSEDATA_H

#include <QObject>

class VerseData : public QObject {
  Q_OBJECT

  Q_PROPERTY(QByteArray backgroundImage READ getBackgroundImage)
  Q_PROPERTY(QByteArray foregroundImage READ getForegroundImage)

public:
  QByteArray getBackgroundImage() const;
  void setBackgroundImage(const QByteArray &value);
  QByteArray getForegroundImage() const;
  void setForegroundImage(const QByteArray &value);

private:
  QByteArray backgroundImage;
  QByteArray foregroundImage;
};

#endif // VERSEDATA_H
