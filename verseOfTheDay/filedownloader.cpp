#include "filedownloader.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

FileDownloader::FileDownloader(QUrl url, VerseData *data, QObject *parent)
    : QObject(parent) {
  this->data = data;

  QNetworkRequest request(url);

  this->firstReply = manager.get(request);
  connect(this->firstReply, &QNetworkReply::finished, this,
          &FileDownloader::fileDownloaded);
}

FileDownloader::~FileDownloader() {}

void FileDownloader::backgroundDownloaded() {
  this->data->setBackgroundImage(this->backgroundReply->readAll());
  this->backgroundReply->deleteLater();
  emit downloaded();
}

void FileDownloader::foregroundDownloaded() {
  this->data->setForegroundImage(this->foregroundReply->readAll());
  this->foregroundReply->deleteLater();
  emit downloaded();
}

void FileDownloader::fileDownloaded() {
  auto bytes = this->firstReply->readAll();
  auto pageContent =
      QString::fromUtf8(bytes.data(), bytes.size()).toStdString();

  std::regex findImageSrc("src=\"(([^\"]+)(\\.jpg|\\.png))\"");
  auto words_begin = std::sregex_iterator(pageContent.begin(),
                                          pageContent.end(), findImageSrc);
  auto words_end = std::sregex_iterator();
  std::sregex_token_iterator it(pageContent.begin(), pageContent.end(),
                                findImageSrc, 1);
  std::sregex_token_iterator reg_end;
  std::string images[2];
  for (auto i = 0; it != reg_end && i < 2; ++it, i++) {
    auto st = it->str();
    images[i] = st;
    std::cout << st << std::endl;
  }

  auto first = images[0];
  auto second = images[1];

  QNetworkRequest backgroundRequest(QUrl(QString::fromStdString(first)));
  this->backgroundReply = manager.get(backgroundRequest);
  connect(this->backgroundReply, &QNetworkReply::finished, this,
          &FileDownloader::backgroundDownloaded);

  QNetworkRequest foregroundRequest(QUrl(QString::fromStdString(second)));
  this->foregroundReply = manager.get(foregroundRequest);
  connect(this->foregroundReply, &QNetworkReply::finished, this,
          &FileDownloader::foregroundDownloaded);

  this->firstReply->deleteLater();
}
