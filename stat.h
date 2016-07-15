#ifndef STAT_H
#define STAT_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "squadra.h"
#include "linestat.h"

class Stat : public QWidget
{
    Q_OBJECT
private:
    enum { maxPersone = 16};

    void createHeader();

    Squadra* squadra;
    QLabel* squadraLabel;
    QLabel* percSquadra;

    QLabel* numero;
    QLabel* cognome;
    QLabel* nome;
    QLabel* ammo;
    QLabel* dueMin;
    QLabel* escl;
    QLabel* reti;
    QLabel* parate;
    QLabel* perc;
    QLabel* parateperc;

    QHBoxLayout* headerLayout;

    LineStat* persona[maxPersone];

public:
    explicit Stat(Squadra* s, QWidget *parent = 0);

signals:

public slots:
    void updateDati();

};

#endif // STAT_H
