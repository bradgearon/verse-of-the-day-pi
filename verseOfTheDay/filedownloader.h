#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include "versedata.h"
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <memory>

class FileDownloader : public QObject {
  Q_OBJECT
public:
  explicit FileDownloader(QUrl imageUrl, VerseData *data, QObject *parent = 0);
  virtual ~FileDownloader();

signals:
  void downloaded();

private slots:
  void fileDownloaded();
  void backgroundDownloaded();
  void foregroundDownloaded();

private:
  QNetworkAccessManager manager;
  VerseData *data;
  QNetworkReply *firstReply = nullptr;
  QNetworkReply *backgroundReply = nullptr;
  QNetworkReply *foregroundReply = nullptr;
};

#endif // FILEDOWNLOADER_H
