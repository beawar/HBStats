#include "linestat.h"
#include <QString>
#include <QGroupBox>
#include <QStyleOption>
#include <QPaintEvent>
#include <QPainter>

LineStat::LineStat(Tesserato*t, QWidget *parent) :
    QWidget(parent), tess(t)
{
    createLabels();
    QHBoxLayout* hbLayout = new QHBoxLayout;

    hbLayout->setSpacing(0);
    hbLayout->setMargin(0);

    hbLayout->addWidget(numero);
    hbLayout->addSpacing(2);
    hbLayout->addWidget(cognome);
    //hbLayout->addWidget(nome);
    hbLayout->addWidget(ammo);
    hbLayout->addWidget(dueMin);
    hbLayout->addWidget(escl);
    hbLayout->addWidget(reti);
    hbLayout->addSpacing(2);
    hbLayout->addWidget(perc);
    hbLayout->addSpacing(2);
    hbLayout->addWidget(parate);
    hbLayout->addSpacing(2);
    hbLayout->addWidget(paratePerc);


    hbLayout->setAlignment(numero, Qt::AlignVCenter);
    hbLayout->setAlignment(ammo, Qt::AlignVCenter);
    hbLayout->setAlignment(dueMin, Qt::AlignVCenter);
    hbLayout->setAlignment(escl, Qt::AlignVCenter);

    setLayout(hbLayout);
}

void LineStat::createLabels(){
    cognome = new QLabel(tess->getCognome().toUpper() + " " + tess->getInitial(tess->getNome()), this);
    cognome->setObjectName("cognome_line");
    /*
    cognome->setMinimumSize(100, 10);
    cognome->setAlignment(Qt::AlignVCenter);
    */

    /*
    nome = new QLabel(tess->getInitial(tess->getNome()), this);
    nome->setObjectName("nome_line");
    nome->setAlignment(Qt::AlignVCenter);
    */

    numero = new QLabel(this);
    numero->setObjectName("numero");
    numero->setAlignment(Qt::AlignCenter);

    ammo = new QLabel(this);
    ammo->setObjectName("ammo");
    ammo->setAlignment(Qt::AlignCenter);

    dueMin = new QLabel(this);
    dueMin->setObjectName("dueMin");
    dueMin->setAlignment(Qt::AlignCenter);

    escl = new QLabel(this);
    escl->setObjectName("escl");
    escl->setAlignment(Qt::AlignCenter);

    reti = new QLabel(this);
    reti->setObjectName("goal1");
    reti->setAlignment(Qt::AlignCenter);

    parate = new QLabel(this);
    parate->setObjectName("goal2");
    parate->setAlignment(Qt::AlignCenter);

    perc = new QLabel(this);
    perc->setObjectName("goal3");
    perc->setAlignment(Qt::AlignCenter);

    paratePerc = new QLabel(this);
    paratePerc->setObjectName("goal4");
    paratePerc->setAlignment(Qt::AlignCenter);


    const Giocatore* g = dynamic_cast<const Giocatore*>(tess);
    if(g){
        numero->setText(QString::number(g->getNumero()));
    }
    else{
        numero->setText("All");
    }
}

void LineStat::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LineStat::updateDati(Tesserato* t){
    if(t->isAmmonito()){
        ammo->setPixmap(QPixmap(":/images/images/bullet-yellow.png").scaled(20,20));
    }
    else{
        ammo->clear();
    }

    switch(t->get2Minuti()){
        case 1:
            dueMin->setPixmap(QPixmap(":/images/images/bullet-black.png").scaled(20, 20));
            break;
        case 2:
            dueMin->setPixmap(QPixmap(":/images/images/bullet-black_x2.png").scaled(40, 20));
            break;
        case 3:
            dueMin->setPixmap(QPixmap(":/images/images/bullet-black_x3.png").scaled(60, 20));
            break;
        default:
            dueMin->clear();
            break;
    }

    if(t->isEscluso()){
        escl->setPixmap(QPixmap(":/images/images/bullet-red.png").scaled(20, 20));
    }
    else{
        escl->clear();
    }

    Giocatore* g = dynamic_cast<Giocatore*>(t);
    if(g){
        numero->setText(QString::number(g->getNumero()));
        if(g->getTiriTotali() != 0 && g->getRigoriTotali() != 0){
            reti->setText(tr("%1/%2 (%3/%4)").arg(QString::number(g->getTiriSegnati()),
                                                  QString::number(g->getTiriTotali()),
                                                  QString::number(g->getRigoriSegnati()),
                                                  QString::number(g->getRigoriTotali())));
            perc->setText(tr("%1% (%2%)").arg(QString::number(g->getTiriPerc(), 'f', 2),
                                              QString::number(g->getRigoriPerc(), 'f', 2)));
        }
        else if(g->getTiriTotali() != 0 && g->getRigoriTotali() == 0){
            reti->setText(tr("%1/%2 (-)").arg(QString::number(g->getTiriSegnati()),
                                                  QString::number(g->getTiriTotali())));
            perc->setText(tr("%1% (-)").arg(QString::number(g->getTiriPerc(), 'f', 2)));
        }
        else{
            reti->clear();
            perc->clear();
        }

        Portiere* p = dynamic_cast<Portiere*>(g);
        if(p){
            if(p->getTiriRicevuti() != 0 && p->getRigoriRicevuti() != 0){
                parate->setText(tr("%1/%2 (%3/%4)").arg(QString::number(p->getTiriParati()),
                                                        QString::number(p->getTiriRicevuti()),
                                                        QString::number(p->getRigoriParati()),
                                                        QString::number(p->getRigoriRicevuti())));
                paratePerc->setText(tr("%1% (%2%)").arg(QString::number(p->getTiriParatiPerc(), 'f', 2),
                                                        QString::number(p->getRigoriParatiPerc(), 'f', 2)));
            }
            else if(p->getTiriRicevuti() != 0 && p->getRigoriRicevuti() == 0){
                parate->setText(tr("%1/%2 (-)").arg(QString::number(p->getTiriParati()),
                                                        QString::number(p->getTiriRicevuti())));
                paratePerc->setText(tr("%1% (-)").arg(QString::number(p->getTiriParatiPerc(), 'f', 2)));
            }
            else{
                reti->clear();
                perc->clear();
            }
        }
    }

    update();
}
