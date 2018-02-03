
#include "verseimageprovider.h"

VerseImageProvider::VerseImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap) {}

QPixmap VerseImageProvider::requestPixmap(const QString &id, QSize *size,
                                          const QSize &requestedSize) {
  QByteArray imageData;

  if (id == "back") {
    imageData = data->getBackgroundImage();
  }
  if (id == "fore") {
    imageData = data->getForegroundImage();
  }

  auto qimage = QImage::fromData(imageData);
  auto pixmap = QPixmap::fromImage(qimage);

  return pixmap;
}

VerseData *VerseImageProvider::getData() const { return data; }

void VerseImageProvider::setData(VerseData *value) { data = value; }
