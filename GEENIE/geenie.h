#ifndef GEENIE_H
#define GEENIE_H

#include <QObject>
#include "common.h"

class GEENIE : public QObject
{
    Q_OBJECT
public:
    explicit GEENIE(QObject *parent = 0);

signals:

public slots:
};

#endif // GEENIE_H
