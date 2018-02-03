#ifndef VERSEIMAGEPROVIDER_H
#define VERSEIMAGEPROVIDER_H

#include "versedata.h"
#include <QPixmap>
#include <QQuickImageProvider>

class VerseImageProvider : public QQuickImageProvider {
public:
  VerseImageProvider();
  QPixmap requestPixmap(const QString &id, QSize *size,
                        const QSize &requestedSize);

  VerseData *getData() const;
  void setData(VerseData *value);

private:
  VerseData *data;
};
#endif // VERSEIMAGEPROVIDER_H
