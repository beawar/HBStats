#include "linestat.h"
#include <QString>
#include <QGroupBox>

LineStat::LineStat(Tesserato*t, QWidget *parent) :
    QWidget(parent), tess(t)
{
    createLabels();
    QHBoxLayout* hbLayout = new QHBoxLayout;

    hbLayout->addWidget(numero);
    hbLayout->addWidget(cognome);
    hbLayout->addWidget(nome);
    hbLayout->addWidget(ammo);
    hbLayout->addWidget(dueMin);
    hbLayout->addWidget(escl);
    hbLayout->addWidget(reti);
    hbLayout->addWidget(perc);
    hbLayout->addWidget(parate);
    hbLayout->addWidget(paratePerc);

    setLayout(hbLayout);

}

void LineStat::createLabels(){
    cognome = new QLabel(tess->getCognome(), this);
    cognome->setMinimumSize(100, 15);
    cognome->setAlignment(Qt::AlignVCenter);
    nome = new QLabel(tess->getNome(), this);
    nome->setMinimumSize(100, 15);
    nome->setAlignment(Qt::AlignVCenter);
    numero = new QLabel(this);
    numero->setMinimumSize(30, 15);
    numero->setMaximumSize(50, 50);
    numero->setStyleSheet("color: white;"
                          "font-weight: bold;"
                          "background-color: rgba(0, 0, 128, 70%);"
                          "border 1px solid white;");
    numero->setAlignment(Qt::AlignCenter);

    ammo = new QLabel(this);
    ammo->setMinimumSize(30, 15);
    ammo->setAlignment(Qt::AlignCenter);
    dueMin = new QLabel(this);
    dueMin->setMinimumSize(80, 15);
    dueMin->setAlignment(Qt::AlignCenter);
    escl = new QLabel(this);
    escl->setMinimumSize(30, 15);
    escl->setAlignment(Qt::AlignCenter);
    reti = new QLabel(this);
    reti->setMinimumSize(100, 15);
    reti->setAlignment(Qt::AlignCenter);
    parate = new QLabel(this);
    parate->setMinimumSize(100, 15);
    parate->setAlignment(Qt::AlignCenter);
    perc = new QLabel(this);
    perc->setMinimumSize(100, 15);
    perc->setAlignment(Qt::AlignCenter);
    paratePerc = new QLabel(this);
    paratePerc->setMinimumSize(100, 15);
    paratePerc->setAlignment(Qt::AlignCenter);

    const Giocatore* g = dynamic_cast<const Giocatore*>(tess);
    if(g){
        numero->setText(QString::number(g->getNumero()));
    }
    else{
        numero->setText("All");
    }
}

void LineStat::updateDati(Tesserato* t){
    if(t->isAmmonito()){
        ammo->setText("X");
    }
    else{
        ammo->clear();
    }

    switch(t->get2Minuti()){
        case 1:
            dueMin->setText("X");
            break;
        case 2:
            dueMin->setText("XX");
            break;
        case 3:
            dueMin->setText("XXX");
            break;
        default:
            dueMin->clear();
            break;
    }

    if(t->isEscluso()){
        escl->setText("X");
    }
    else{
        escl->clear();
    }

    Giocatore* g = dynamic_cast<Giocatore*>(t);
    if(g){
        numero->setText(QString::number(g->getNumero()));
        reti->setText(tr("%1/%2 (%3/%4)").arg(QString::number(g->getTiriSegnati()),
                                              QString::number(g->getTiriTotali()),
                                              QString::number(g->getRigoriSegnati()),
                                              QString::number(g->getRigoriTotali())));
        perc->setText(tr("%1% (%2%)").arg(QString::number(g->getTiriPerc(), 'f', 2),
                                        QString::number(g->getRigoriPerc(), 'f', 2)));

        Portiere* p = dynamic_cast<Portiere*>(g);
        if(p){
            parate->setText(tr("%1/%2 (%3/%4)").arg(QString::number(p->getTiriParati()),
                                                    QString::number(p->getTiriRicevuti()),
                                                    QString::number(p->getRigoriParati()),
                                                    QString::number(p->getRigoriRicevuti())));
            paratePerc->setText(tr("%1% (%2%)").arg(QString::number(p->getTiriParatiPerc(), 'f', 2),
                                                  QString::number(p->getRigoriParatiPerc(), 'f', 2)));
        }
    }

    update();
}
