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
  explicit FileDownloader(VerseData *data, QObject *parent = 0);
  virtual ~FileDownloader();
  void DownloadUrl(QUrl url);
signals:
  void downloaded();

private slots:
  void fileDownloaded();

private:
  QNetworkAccessManager manager;
  VerseData *data;
  QNetworkReply *firstReply = nullptr;
};

#endif // FILEDOWNLOADER_H
