#ifndef STATSAMESCREEN_H
#define STATSAMESCREEN_H

#include <QWidget>
#include "stat.h"

class StatSameScreen : public QWidget
{
    Q_OBJECT
public:
    explicit StatSameScreen(QWidget *parent = 0);
    StatSameScreen(Stat* s1, Stat* s2);

signals:

public slots:
};

#endif // STATSAMESCREEN_H
