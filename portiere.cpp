#include "portiere.h"

Portiere::Portiere(const QString & nome, const QString & cognome, const QDate & nascita, unsigned int numero)
    : Giocatore(nome, cognome, nascita, numero), tiriParati(0),
      tiriRicevuti(0), rigoriParati(0), rigoriRicevuti(0) {}

Portiere::Portiere(const Portiere &p)
    : Giocatore(p.getNome(), p.getCognome(), p.getData(), p.getNumero()), tiriParati(p.tiriParati),
      tiriRicevuti(p.tiriRicevuti), rigoriParati(p.rigoriParati), rigoriRicevuti(p.rigoriRicevuti)
{
    addTiro(p.getTiriSegnati(), true);
    addTiro(p.getTiriTotali()-p.getTiriSegnati(), false);
    addRigore(p.getRigoriSegnati(), true);
    addRigore(p.getRigoriTotali()-p.getRigoriSegnati(), false);
    ammonito(p.isAmmonito());
    add2Minuti(p.get2Minuti());
    escluso(p.isEscluso());
    setChecked(p.isChecked());
}

Portiere::Portiere(const Giocatore &g)
    : Giocatore(g), tiriParati(0), tiriRicevuti(0),
      rigoriParati(0), rigoriRicevuti(0) {}

unsigned int Portiere::getTiriParati() const{
    return tiriParati;
}

unsigned int Portiere::getTiriRicevuti() const{
    return tiriRicevuti;
}

unsigned int Portiere::getRigoriParati() const{
    return rigoriParati;
}

unsigned int Portiere::getRigoriRicevuti() const{
    return rigoriRicevuti;
}

unsigned int Portiere::getGoalSubiti() const{
    return tiriRicevuti-tiriParati;
}

unsigned int Portiere::getRigoriSubiti() const{
    return rigoriRicevuti-rigoriParati;
}

double Portiere::getTiriParatiPerc() const{
    return tiriRicevuti == 0 ? 0 : (double)(tiriParati*100)/tiriRicevuti;
}

double Portiere::getRigoriParatiPerc() const{
    return rigoriRicevuti == 0 ? 0 : (double)(rigoriParati*100)/rigoriRicevuti;
}

void Portiere::addTiroRicevuto(int x, const bool & parato){
    if(parato){
        tiriParati+x <0 ? tiriParati=0 : tiriParati+=x;
    }
    tiriRicevuti+x <0 ? tiriRicevuti=0 : tiriRicevuti+=x;
}

void Portiere::addRigoreRicevuto(int x, const bool & parato){
    if(parato){
        rigoriParati+x <0 ? rigoriParati=0 : rigoriParati+=x;
    }
    rigoriRicevuti+x <0 ? rigoriRicevuti=0 : rigoriRicevuti+=x;
    addTiroRicevuto(x, parato);
}

Portiere& Portiere::operator =(const Portiere& p){
    Giocatore::operator =(p);
    tiriParati = p.tiriParati;
    tiriRicevuti = p.tiriRicevuti;
    rigoriParati = p.rigoriParati;
    rigoriRicevuti = p.rigoriRicevuti;
    return *this;
}

QString Portiere::getInfo() const{
    QString info;
    info.append(Giocatore::getInfo());
    info.append("  (P)");
    return info;
}

void Portiere::reset(){
    Giocatore::reset();
    tiriParati=0;
    tiriRicevuti=0;
    rigoriParati=0;
    rigoriRicevuti=0;
}
