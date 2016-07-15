#include "giocatore.h"

unsigned int Giocatore::max2Minuti = 3;

Giocatore::Giocatore(const QString& nome, const QString& cognome, const QDate& nascita, unsigned int num)
  :Tesserato(nome, cognome, nascita), numero(num), tiriSegnati(0), tiriTotali(0), rigoriSegnati(0),
    rigoriTotali(0), ammonizione(false), dueMinuti(0), esclusione(0) {}

Giocatore::Giocatore(const Giocatore &g)
    :Tesserato(g.getNome(), g.getCognome(), g.getData()), numero(g.numero), tiriSegnati(g.tiriSegnati),
      tiriTotali(g.tiriTotali), rigoriSegnati(g.rigoriSegnati), rigoriTotali(g.rigoriTotali),
      ammonizione(g.ammonizione), dueMinuti(g.dueMinuti), esclusione(g.esclusione)
{
    setChecked(g.isChecked());
}

unsigned int Giocatore::getNumero() const{
    return numero;
}

unsigned int Giocatore::getTiriSegnati() const{
  return tiriSegnati < 0 ? 0 : tiriSegnati;
}

unsigned int Giocatore::getTiriTotali() const{
  return tiriTotali < 0 ? 0 : tiriTotali;
}

unsigned int Giocatore::getRigoriSegnati() const{
  return rigoriSegnati < 0 ? 0 : rigoriSegnati;
}

unsigned int Giocatore::getRigoriTotali() const{
  return rigoriTotali < 0 ? 0 : rigoriTotali;
}

double Giocatore::getTiriPerc() const{
  return tiriTotali == 0 ? 0 : (double)(tiriSegnati*100)/tiriTotali;
}

double Giocatore::getRigoriPerc() const{
  return rigoriTotali == 0 ? 0 : (double)(rigoriSegnati*100)/rigoriTotali;
}

bool Giocatore::isAmmonito() const{
  return ammonizione;
}

int Giocatore::get2Minuti() const{
  return dueMinuti;
}

bool Giocatore::isEscluso() const{
  return esclusione;
}

void Giocatore::setNumero(unsigned int n){
    numero=n;
}

void Giocatore::addTiro(int x, const bool& segnato){
    if(segnato){
        tiriSegnati+=x;
    }
    (tiriTotali+x)<tiriSegnati ? tiriTotali=tiriSegnati : tiriTotali+=x;
}

void Giocatore::addRigore(int x, const bool& segnato){
    if(segnato){
        rigoriSegnati+=x;
    }
    (rigoriTotali+x)<rigoriTotali ? rigoriTotali=rigoriTotali : rigoriTotali+=x ;
    addTiro(x, segnato);
}

void Giocatore::ammonito(const bool& add) throw(Err_Ammonizione){
    if(add){
        isAmmonito() ? throw Err_Ammonizione() : ammonizione=true;
    }
    else{
        ammonizione=false;
    }
}

void Giocatore::add2Minuti(int x) throw(Err_DueMinuti){
    (dueMinuti+x <0 || dueMinuti+x>3) ? throw Err_DueMinuti(): dueMinuti+=x;
}

void Giocatore::escluso(const bool& add) throw(Err_Esclusione){
    if(add){
        isEscluso() ? throw Err_Esclusione() : esclusione = true;
    }
    else{
        esclusione = false;
    }
}

void Giocatore::modifica(const Tesserato &g){
    const Giocatore* aux = dynamic_cast<const Giocatore*>(&g);
    if(aux && *this != *aux){
        if(numero != aux->numero){
            setNumero(aux->numero);
        }
    }
    Tesserato::modifica(g);
}

Giocatore& Giocatore::operator =(const Giocatore& g){
    Tesserato::operator =(g);
    numero = g.numero;
    tiriSegnati = g.tiriSegnati;
    tiriTotali = g.tiriTotali;
    rigoriSegnati = g.rigoriSegnati;
    rigoriTotali = g.rigoriTotali;
    ammonizione = g.ammonizione;
    dueMinuti = g.dueMinuti;
    esclusione = g.esclusione;
    return *this;
}

bool Giocatore::operator ==(const Giocatore& g) const{
    return Tesserato::operator ==(g) && numero==g.numero;
}

bool Giocatore::operator !=(const Giocatore& g) const{
    return !(operator ==(g));
}

bool Giocatore::operator <(const Giocatore& g) const{
    if(Tesserato::operator <(g)){
        return true;
    }
    else if(Tesserato::operator ==(g) && numero<g.numero){
        return true;
    }
    else{
        return false;
    }
}

bool Giocatore::operator <=(const Giocatore& g) const{
    return (operator <(g)) || (operator ==(g));
}

bool Giocatore::operator >(const Giocatore& g) const{
    return !(operator <=(g));
}

bool Giocatore::operator >=(const Giocatore& g) const{
    return !(operator <(g));
}

QString Giocatore::getInfo() const{
    QString info;
    if(getNumero() < 10){
        info.append("  ");
    }
    info.append(QString::number(getNumero()) + "   ");
    info.append(Tesserato::getInfo());
    return info;
}

void Giocatore::reset(){
    tiriSegnati = 0;
    tiriTotali = 0;
    rigoriSegnati = 0;
    rigoriTotali = 0;
    ammonizione = false;
    dueMinuti = 0;
    esclusione = false;
}
