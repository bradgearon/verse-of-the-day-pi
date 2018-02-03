#include "filedownloader.h"
#include <QDate>
#include <QDateTime>
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QQmlApplicationEngine>
#include <QTime>
#include <QTimer>
#include <QWindow>
#include <QtDebug>
#include <chrono>
#include <iostream>
#include <memory>

static qint32 getMsToTomorrowAtEight() {
  auto tomorrow = QDate::currentDate().addDays(1);
  QDateTime eightTomorrow(tomorrow, QTime(8, 0, 0, 0));
  auto now = QDateTime::currentDateTime();
  auto msToEightTomorrow = static_cast<qint32>(now.msecsTo(eightTomorrow));
  return msToEightTomorrow;
}

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  QWindow *obj = static_cast<QWindow *>(engine.rootObjects().first());
  obj->setVisibility(QWindow::FullScreen);

  VerseData verseData;
  obj->setProperty("verseData", QVariant::fromValue(&verseData));

  FileDownloader downloader(&verseData);
  auto url = QUrl(QStringLiteral("https://lightfortheday.com/"));
  downloader.DownloadUrl(url);

  QTimer timer;
  timer.setSingleShot(true);

  QObject::connect(&timer, &QTimer::timeout, [&downloader, &url, &timer]() {
    downloader.DownloadUrl(url);
    auto timerDuration = getMsToTomorrowAtEight();
    timer.start(timerDuration);
    qDebug() << "timer started kick off in " << timerDuration;
  });

  auto timerDuration = getMsToTomorrowAtEight();
  timer.start(timerDuration);

  qDebug() << "timer started kick off in " << timerDuration;

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
