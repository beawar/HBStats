#ifndef NEWWIZARD_H
#define NEWWIZARD_H

#include <QWizard>
#include <QRadioButton>
#include <QPushButton>
#include "squadremodel.h"
#include "arbitrimodel.h"
#include "squadra.h"
#include "arbitro.h"
#include "intropage.h"
#include "personapage.h"
#include "squadrapage.h"
#include "partitapage.h"

class NewWizard : public QWizard
{
    Q_OBJECT
private:
    IntroPage* introP;
    PersonaPage* personaP;
    SquadraPage* squadraP;
    PartitaPage* partitaP;

    SquadreModel* squadre;
    ArbitriModel* arbitri;

private slots:
    void nuovaSquadra();
    void nuovaPersona();

public:
    enum {Page_Intro, Page_Persona, Page_Squadra, Page_Partita};
    explicit NewWizard( SquadreModel* sm =0, ArbitriModel* am =0, QWidget *parent = 0);

    Squadra* getHomeTeam() const;
    Squadra* getGuestTeam() const;
    Arbitro* getArbitro1() const;
    Arbitro* getArbitro2() const;
    Arbitro::Categoria getCategoria() const;

    void accept();

signals:
    void partitaCreata();
    void squadraCreata();
    void dataChanged(bool);
};

#endif // NEWWIZARD_H
