#include "stat.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QStyleOption>
#include <QPainter>
#include <QSizePolicy>
#include <QSize>

Stat::Stat(Squadra *s, QWidget *parent) :
    QWidget(parent), squadra(s)
{   

    createHeader();

    QFont font;
    font.setBold(true);
    font.setItalic(true);
    font.setPointSize(14);
    squadraLabel = new QLabel(squadra->getNome(), this);
    squadraLabel->setFont(font);

    QFont font2;
    font2.setBold(true);
    font2.setItalic(false);
    font2.setPointSize(10);
    percSquadra = new QLabel(this);
    percSquadra->setText(tr("Realizzazioni: %1% (Rigori: %2%) Parate: %3% (Rigori: %4%)")
                         .arg("--", "--", "--", "--"));
    percSquadra->setFont(font2);
    percSquadra->setAlignment(Qt::AlignLeft);


    QHBoxLayout* squadraLayout = new QHBoxLayout;
    squadraLayout->addWidget(squadraLabel);
    squadraLayout->addWidget(percSquadra);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(squadraLayout);
    layout->addLayout(headerLayout);

    //Creating and setting a groupbox that contain all the header labels
    QGroupBox* headerGroup = new QGroupBox(this);
    headerGroup->setObjectName("HeaderGroup");
    headerGroup->setLayout(layout);
    headerGroup->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(3);
    mainLayout->setMargin(5);
    mainLayout->addWidget(headerGroup);

    int j = 0;
    for(unsigned int i=0; i<squadra->size() && j<maxPersone; ++i){
        if(squadra->at(i)->isChecked()){
            persona[j] = new LineStat(squadra->at(i), this);
            mainLayout->addWidget(persona[j]);
            j++;
        }
    }
    persona[j-1]->setObjectName("LastPerson");
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void Stat::createHeader(){
    headerLayout = new QHBoxLayout;

    /*
    numero = new QLabel("N°", this);
    numero->setObjectName("numero_header");

    cognome = new QLabel(tr("Cognome"), this);
    cognome->setObjectName("cognome");

    nome = new QLabel(tr("Nome"), this);
    nome->setObjectName("nome");
    */

    ammo = new QLabel(this);
    ammo->setPixmap(QPixmap(":/images/images/giallo.png").scaled(20, 20));
    ammo->setObjectName("ammo_h");
    ammo->setAlignment(Qt::AlignCenter);

    dueMin = new QLabel(this);
    dueMin->setPixmap(QPixmap(":/images/images/two_fingers.png").scaled(20, 20));
    dueMin->setObjectName("dueMin_h");
    dueMin->setAlignment(Qt::AlignCenter);

    escl = new QLabel(this);
    escl->setPixmap(QPixmap(":/images/images/rosso.png").scaled(20, 20));
    escl->setObjectName("escl_h");
    escl->setAlignment(Qt::AlignCenter);

    reti = new QLabel(this);
    reti->setPixmap(QPixmap(":/images/images/footbal.png").scaled(20, 20));
    reti->setObjectName("goal_h1");
    reti->setAlignment(Qt::AlignCenter);

    parate = new QLabel(this);
    parate->setPixmap(QPixmap(":/images/images/portiere.png").scaled(20, 20));
    parate->setObjectName("goal_h2");
    parate->setAlignment(Qt::AlignCenter);

    perc = new QLabel(this);
    perc->setPixmap(QPixmap(":/images/images/footbal_perc.png").scaled(20, 20));
    perc->setObjectName("goal_h3");
    perc->setAlignment(Qt::AlignCenter);

    parateperc = new QLabel(this);
    parateperc->setPixmap(QPixmap(":/images/images/portiere_perc.png").scaled(20, 20));
    parateperc->setObjectName("goal_h4");
    parateperc->setAlignment(Qt::AlignCenter);

    /*
    headerLayout->addWidget(numero);
    headerLayout->addWidget(cognome);
    headerLayout->addWidget(nome);
    */
    headerLayout->setSpacing(0);
    headerLayout->addSpacing(220);
    headerLayout->addWidget(ammo);
    headerLayout->addWidget(dueMin);
    headerLayout->addWidget(escl);
    headerLayout->addWidget(reti);
    headerLayout->addWidget(perc);
    headerLayout->addWidget(parate);
    headerLayout->addWidget(parateperc);
}

void Stat::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Stat::updateDati(){
    percSquadra->setText(tr("Realizzazioni: %1% (Rigori: %2%) Parate: %3% (Rigori: %4%)")
                         .arg(QString::number(squadra->getTiriPerc(), 'f', 2))
                         .arg(QString::number(squadra->getRigoriPerc(), 'f', 2))
                         .arg(QString::number(squadra->getParatePerc(), 'f', 2))
                         .arg(QString::number(squadra->getParateRigoriPerc(), 'f', 2)));
    int j = 0;
    bool last = false;
    for(unsigned int i=0; i<squadra->size() && !last; ++i){
        if(squadra->at(i)->isChecked()){
            persona[j]->updateDati(squadra->at(i));
            if(persona[j]->objectName() == "LastPerson"){
                last = true;
            }
            j++;
        }
    }
    update();
}
