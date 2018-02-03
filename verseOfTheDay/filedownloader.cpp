#include "filedownloader.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

FileDownloader::FileDownloader(VerseData *data, QObject *parent)
    : QObject(parent) {
  this->data = data;
}

FileDownloader::~FileDownloader() {}

void FileDownloader::DownloadUrl(QUrl url) {
  QNetworkRequest request(url);

  this->firstReply = manager.get(request);
  connect(this->firstReply, &QNetworkReply::finished, this,
          &FileDownloader::fileDownloaded);
}

void FileDownloader::fileDownloaded() {
  auto bytes = this->firstReply->readAll();
  auto pageContent = QString::fromUtf8(bytes.data(), bytes.size());

  data->loadData(pageContent);
  this->firstReply->deleteLater();
  emit downloaded();
}
