#include "filedownloader.h"
#include "verseimageprovider.h"
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QQmlApplicationEngine>
#include <QWindow>
#include <QtDebug>
#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  auto verseImageProvider = new VerseImageProvider();
  VerseData data;
  verseImageProvider->setData(&data);

  engine.addImageProvider(QLatin1String("verse"), verseImageProvider);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  QWindow *obj = static_cast<QWindow *>(engine.rootObjects().first());
  obj->setVisibility(QWindow::FullScreen);

  // obj->setProperty("verseData", QVariant::fromValue(&data));

  FileDownloader fd(QUrl(QStringLiteral("https://lightfortheday.com/")), &data);

  auto backImage = obj->findChild<QObject *>("backImage");
  auto foreImage = obj->findChild<QObject *>("foreImage");

  QObject::connect(
      &fd, &FileDownloader::downloaded, [&data, backImage, foreImage]() {
        qDebug() << "testing" << data.getBackgroundImage().length();
        qDebug() << "this fired" << data.getForegroundImage().length();
        if (data.getBackgroundImage().length() > 0) {
          backImage->setProperty("source", "image://verse/back");
        }
        if (data.getForegroundImage().length() > 0) {
          foreImage->setProperty("source", "image://verse/fore");
        }
      });

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
