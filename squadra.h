#ifndef SQUADRA_H
#define SQUADRA_H

#include <QString>
#include "vettore.h"
#include "eccezioni.h"
#include "tesserato.h"
#include "giocatore.h"
#include "arbitro.h"
#include "portiere.h"
#include "allenatore.h"

class Squadra
{
private:
    QString nome;
    QString societa;
    Vettore<Tesserato*> tesserati;

    unsigned int vittorie;
    unsigned int pareggi;
    unsigned int sconfitte;

    unsigned int goalFatti;
    unsigned int goalSubiti;

    unsigned int penalita;

    static unsigned int maxAmmonizioni;
    static unsigned int maxEsclusioni;
    static unsigned int puntiVittoria;
    static unsigned int puntiPareggio;

public:
    Squadra(const QString& = "");
    Squadra(const QString&, const QString&);
    ~Squadra();

    QString getNome () const;
    QString getSocieta () const;
    unsigned int getVittorie() const;
    unsigned int getPareggi() const;
    unsigned int getSconfitte() const;

    void setNome (const QString&);
    void setSocieta(const QString&);
    void addVittoria (int =1, unsigned int =0, unsigned int =0);
    void addPareggio(int =1, unsigned int =0);
    void addSconfitta(int =1, unsigned int =0, unsigned int =0);

    void addPenalita(int);
    int getPenalita() const;

    int getPunti() const;

    void addGoalFatti(unsigned int);
    void addGoalSubiti(unsigned int);
    unsigned int getGoalFatti() const;
    unsigned int getGoalSubiti() const;

    int getDifferenzaReti() const;

    unsigned int getTiriSegnati() const;
    unsigned int getTiriEffettuati() const;

    unsigned int getRigoriSegnati() const;
    unsigned int getRigoriEffettuati() const;

    unsigned int getTiriParati() const;
    unsigned int getTiriRicevuti() const;

    unsigned int getRigoriParati() const;
    unsigned int getRigoriRicevuti() const;

    double getTiriPerc() const;
    double getRigoriPerc() const;
    double getParatePerc() const;
    double getParateRigoriPerc() const;

    void addTesserato (Tesserato*) throw(Err_Tesserato);
    void modificaTesserato(Tesserato*, const Tesserato&);
    void removeTesserato(Tesserato*);
    void sostituisciTesserato(int, Tesserato*);

    void modifica(const Squadra&);

    Tesserato* trova(Tesserato &) const;
    int pos(Tesserato&) const;
    Tesserato* at (int) const;
    Tesserato& operator [] (int) const;
    bool operator == (const Squadra&) const;
    void sortByName();
    void sortByNumber();

    void reset();
    void clear();

    unsigned int size() const;
};


#endif // SQUADRA_H
