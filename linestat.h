#ifndef LINESTAT_H
#define LINESTAT_H

#include <QWidget>
#include "tesserato.h"
#include "giocatore.h"
#include "allenatore.h"
#include "portiere.h"
#include <QLabel>
#include <QHBoxLayout>

class LineStat : public QWidget
{
    Q_OBJECT
private:
    Tesserato* tess;

    void createLabels();

    QLabel* nome;
    QLabel* cognome;
    QLabel* numero;
    QLabel* ammo;
    QLabel* dueMin;
    QLabel* escl;
    QLabel* reti;
    QLabel* parate;
    QLabel* perc;
    QLabel* paratePerc;
public:
    explicit LineStat(Tesserato* t, QWidget *parent = 0);

signals:

public slots:
    void updateDati(Tesserato* t);

};

#endif // LINESTAT_H
