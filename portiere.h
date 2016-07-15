#ifndef PORTIERE_H
#define PORTIERE_H

#include "giocatore.h"

class Portiere : public Giocatore
{
private:
    int tiriParati;
    int tiriRicevuti;
    int rigoriParati;
    int rigoriRicevuti;

public:
    Portiere(const QString& nome ="", const QString& cognome ="",
             const QDate& nascita = QDate::currentDate(), unsigned int numero = 0);
    Portiere(const Portiere& p);
    Portiere(const Giocatore& g);

    unsigned int getTiriParati() const;
    unsigned int getTiriRicevuti() const;
    unsigned int getRigoriParati() const;
    unsigned int getRigoriRicevuti() const;

    unsigned int getGoalSubiti () const;
    unsigned int getRigoriSubiti () const;

    double getTiriParatiPerc() const;
    double getRigoriParatiPerc() const;

    void addTiroRicevuto(int x = 1, const bool& parato= false);
    void addRigoreRicevuto(int x =1, const bool& parato = false);

    Portiere& operator =(const Portiere& p);

    virtual QString getInfo() const;
    virtual void reset();
};

#endif // PORTIERE_H
