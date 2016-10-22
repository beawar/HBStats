#ifndef LINESTAT_H
#define LINESTAT_H

#include <QWidget>
#include "tesserato.h"
#include "giocatore.h"
#include "allenatore.h"
#include "portiere.h"
#include "label.h"
#include <QHBoxLayout>

class LineStat : public QWidget
{
    Q_OBJECT
private:
    Tesserato* tess;

    void createLabels();

    Label* nome;
    Label* cognome;
    Label* numero;
    Label* ammo;
    Label* dueMin;
    Label* escl;
    Label* reti;
    Label* parate;
    Label* perc;
    Label* paratePerc;
public:
    explicit LineStat(Tesserato* t, QWidget *parent = 0);

signals:

public slots:
    void updateDati(Tesserato* t);

};

#endif // LINESTAT_H
