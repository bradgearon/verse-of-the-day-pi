#ifndef VERSEDATA_H
#define VERSEDATA_H

#include "imageset.h"
#include <QObject>
#include <memory>
#include <regex>
#include <vector>

class VerseData : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString backgroundImage READ getBackgroundImage NOTIFY
                 backgroundImageUpdated)
  Q_PROPERTY(QString foregroundImage READ getForegroundImage NOTIFY
                 foregroundImageUpdated)
  Q_PROPERTY(qint32 selectedDay READ getSelectedDay WRITE setSelectedDay NOTIFY
                 selectedDayUpdated)

  Q_PROPERTY(bool canGoBack READ getCanGoBack NOTIFY canGoBackUpdated)
  Q_PROPERTY(bool canGoForward READ getCanGoForward NOTIFY canGoForwardUpdated)
signals:
  void backgroundImageUpdated();
  void foregroundImageUpdated();
  void selectedDayUpdated();
  void canGoBackUpdated();
  void canGoForwardUpdated();

public:
  QString getBackgroundImage() const;
  void setBackgroundImage(const QString &value);
  QString getForegroundImage() const;
  void setForegroundImage(const QString &value);
  qint32 getSelectedDay() const;
  void setSelectedDay(const qint32 &value);
  void loadData(const QString &value);

  bool getCanGoBack() const;
  void setCanGoBack(bool value);

  bool getCanGoForward() const;
  void setCanGoForward(bool value);

private:
  QString backgroundImage;
  QString foregroundImage;
  qint32 selectedDay = 0;
  bool canGoBack = true;
  bool canGoForward = false;
  std::vector<ImageSet> images;
};

#endif // VERSEDATA_H
