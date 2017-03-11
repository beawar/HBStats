#include "squadra.h"
#include "allenatore.h"

unsigned int Squadra::maxAmmonizioni = 3;
unsigned int Squadra::maxEsclusioni = 4;
unsigned int Squadra::puntiVittoria = 3;
unsigned int Squadra::puntiPareggio = 1;

Squadra::Squadra(const QString& n)
    :nome(n), societa(n), tesserati(), vittorie(0), pareggi(0),
      sconfitte(0), goalFatti(0), goalSubiti(0), penalita(0) {}

Squadra::Squadra(const QString& n, const QString& s)
    : nome(n), societa(s), tesserati(), vittorie(0), pareggi(0),
      sconfitte(0), goalFatti(0), goalSubiti(0), penalita(0) {}

QString Squadra::getNome() const{
    return nome;
}

QString Squadra::getSocieta() const{
    return societa;
}

unsigned int Squadra::getVittorie() const{
    return vittorie;
}

unsigned int Squadra::getPareggi() const{
    return pareggi;
}

unsigned int Squadra::getSconfitte() const{
    return sconfitte;
}

void Squadra::setNome(const QString &n){
    nome = n;
}

void Squadra::setSocieta(const QString &s){
    societa = s;
}

void Squadra::addVittoria(int x, unsigned int fatti, unsigned int subiti){
    vittorie+x >0 ? vittorie+=x : vittorie=0;
    goalFatti += fatti;
    goalSubiti += subiti;
}

void Squadra::addPareggio(int x, unsigned int goal){
    pareggi+x >0 ? pareggi+=x : pareggi=0;
    goalFatti += goal;
    goalSubiti += goal;
}

void Squadra::addSconfitta(int x, unsigned int fatti, unsigned int subiti){
    sconfitte+x >0 ? sconfitte+=x : sconfitte=0;
    goalFatti += fatti;
    goalSubiti += subiti;
}

void Squadra::addPenalita(int x){
     penalita+x >0 ? penalita+=x : penalita=0;
}

int Squadra::getPenalita() const{
    return penalita;
}

int Squadra::getPunti() const{
    return (vittorie*puntiVittoria)
            + (pareggi*puntiPareggio)
            - penalita;
}

void Squadra::addGoalFatti(unsigned int x){
    goalFatti += x;
}

void Squadra::addGoalSubiti(unsigned int x){
    goalSubiti += x;
}

unsigned int Squadra::getGoalFatti() const{
    return goalFatti;
}

unsigned int Squadra::getGoalSubiti() const{
    return goalSubiti;
}

int Squadra::getDifferenzaReti() const{
    return getGoalFatti() - getGoalSubiti();
}

unsigned int Squadra::getTiriSegnati() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit = tesserati.cbegin(); cit<tesserati.cend(); ++cit){
        const Giocatore* g = dynamic_cast<const Giocatore*>(*cit);
        if(g){
            tot+= g->getTiriSegnati();
        }
    }
    return tot;
}

unsigned int Squadra::getTiriEffettuati() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit = tesserati.cbegin(); cit<tesserati.cend(); ++cit){
        const Giocatore* g = dynamic_cast<const Giocatore*>(*cit);
        if(g){
            tot+= g->getTiriTotali();
        }
    }
    return tot;
}

unsigned int Squadra::getRigoriSegnati() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit = tesserati.cbegin(); cit<tesserati.cend(); ++cit){
        const Giocatore* g = dynamic_cast<const Giocatore*>(*cit);
        if(g){
            tot+= g->getRigoriSegnati();
        }
    }
    return tot;
}

unsigned int Squadra::getRigoriEffettuati() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit = tesserati.cbegin(); cit<tesserati.cend(); ++cit){
        const Giocatore* g = dynamic_cast<const Giocatore*>(*cit);
        if(g){
            tot+= g->getRigoriTotali();
        }
    }
    return tot;
}

unsigned int Squadra::getTiriParati() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit = tesserati.cbegin(); cit<tesserati.cend(); ++cit){
        const Portiere* p = dynamic_cast<const Portiere*>(*cit);
        if(p){
            tot+= p->getTiriParati();
        }
    }
    return tot;
}

unsigned int Squadra::getTiriRicevuti() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit = tesserati.cbegin(); cit<tesserati.cend(); ++cit){
        const Portiere* p = dynamic_cast<const Portiere*>(*cit);
        if(p){
            tot+= p->getTiriRicevuti();
        }
    }
    return tot;
}

unsigned int Squadra::getRigoriParati() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit = tesserati.cbegin(); cit<tesserati.cend(); ++cit){
        const Portiere* p = dynamic_cast<const Portiere*>(*cit);
        if(p){
            tot+= p->getRigoriParati();
        }
    }
    return tot;
}

unsigned int Squadra::getRigoriRicevuti() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit = tesserati.cbegin(); cit<tesserati.cend(); ++cit){
        const Portiere* p = dynamic_cast<const Portiere*>(*cit);
        if(p){
            tot+= p->getRigoriRicevuti();
        }
    }
    return tot;
}

double Squadra::getTiriPerc() const{
    return getTiriEffettuati() > 0 ? (double)getTiriSegnati()*100 /getTiriEffettuati() : 0;
}

double Squadra::getRigoriPerc() const{
    return getRigoriEffettuati() > 0 ? (double)getRigoriSegnati()*100 /getRigoriEffettuati() : 0;
}

double Squadra::getParatePerc() const{
    return getTiriRicevuti() > 0 ? (double)getTiriParati()*100 /getTiriRicevuti() : 0;
}

double Squadra::getParateRigoriPerc() const{
    return getRigoriRicevuti() ? (double)getRigoriParati()*100 /getRigoriRicevuti() : 0;
}

void Squadra::addTesserato(Tesserato *t) throw(Err_Tesserato){
    if(!dynamic_cast<const Arbitro*>(t)){
        if(trova(*t)){
            throw Err_Tesserato();
        }
        else{
            tesserati.push_back(t);
        }
    }
    else{
        throw Err_Tesserato();
    }
}

void Squadra::modificaTesserato(Tesserato* cur, const Tesserato& nuovo){
    cur->modifica(nuovo);
}

void Squadra::removeTesserato(Tesserato* t){
    if(trova(*t)){
        tesserati.erase(t);
        delete t;
    }
}

void Squadra::sostituisciTesserato(int i, Tesserato *nuovo){
    Tesserato* vecchio = tesserati.at(i);
    delete vecchio;
    tesserati.at(i) = nuovo;
}

void Squadra::modifica(const Squadra& s){
    if(nome != s.nome){
        setNome(s.nome);
    }
    if(societa != s.societa){
        setSocieta(s.societa);
    }
    if(penalita != s.penalita){
        addPenalita(s.penalita);
    }
}

Tesserato* Squadra::trova(Tesserato& t) const{
    for(Vettore<Tesserato*>::iterator it=tesserati.begin(); it<tesserati.end(); ++it){
        if(**it == t){
            return *it;
        }
    }
    return 0;
}

int Squadra::pos(Tesserato & t) const{
    for(int i=0; i< tesserati.size(); ++i){
        if(*(tesserati.at(i)) == t){
            return i;
        }
    }
    return -1;
}

Tesserato* Squadra::at (int i) const{
    return tesserati.at(i);
}

Tesserato& Squadra::operator [] (int i) const{
    return *(tesserati[i]);
}
bool Squadra::operator ==(const Squadra& s) const{
    if(tesserati.size() != s.tesserati.size()){
        return false;
    }
    else{
        for(unsigned int i=0; i<tesserati.size(); ++i){
            if(*(tesserati[i]) != s[i]){
                return false;
            }
        }
        return true;
    }
}

void Squadra::sortByName(){
    Vettore<Tesserato*> giocatori;
    Vettore<Tesserato*> allenatori;
    for(unsigned int i=0; i<tesserati.size(); ++i){
        bool inserito = false;
        if(dynamic_cast<Giocatore*>(tesserati[i])){
            for(unsigned int j=0; j<giocatori.size() && !inserito; ++j){
                if(*tesserati[i] < *giocatori[j]){
                    giocatori.insert(j, tesserati[i]);
                    inserito = true;
                }
            }
            if(!inserito){
                giocatori.push_back(tesserati[i]);
            }
        }
        else{
            for(unsigned int j=0; j<allenatori.size() && !inserito; ++j){
                if(*tesserati[i] < *allenatori[j]){
                    allenatori.insert(j, tesserati[i]);
                    inserito = true;
                }
            }
            if(!inserito){
                allenatori.push_back(tesserati[i]);
            }
        }
    }
    tesserati = giocatori + allenatori;
}

void Squadra::sortByNumber(){
    Vettore<Tesserato*> giocatori;
    Vettore<Tesserato*> allenatori;
    for(unsigned int i=0; i<tesserati.size(); ++i){
        bool inserito = false;
        Giocatore* gioc = dynamic_cast<Giocatore*>(tesserati[i]);
        if(gioc){
            for(unsigned int j=0; j<giocatori.size() && !inserito; ++j){
                Giocatore* g2 = dynamic_cast<Giocatore*>(giocatori[j]);
                if(gioc->getNumero() < g2->getNumero() || (gioc->getNumero() == g2->getNumero() && *gioc < *g2)){
                    giocatori.insert(j, gioc);
                    inserito = true;
                }
            }
            if(!inserito){
                giocatori.push_back(gioc);
            }
        }
        else{
            for(unsigned int j=0; j<allenatori.size() && !inserito; ++j){
                if(*tesserati[i] < *allenatori[j]){
                    allenatori.insert(j, tesserati[i]);
                    inserito = true;
                }
            }
            if(!inserito){
                allenatori.push_back(tesserati[i]);
            }
        }
    }
    tesserati = giocatori + allenatori;
}

void Squadra::reset(){
    vittorie = 0;
    pareggi = 0;
    sconfitte = 0;
    penalita = 0;
}

void Squadra::clear(){
    for(Vettore<Tesserato*>::iterator it = tesserati.begin(); it!=tesserati.end(); ++it){
        delete (*it);
    }
    tesserati.clear();
}

unsigned int Squadra::size() const{
    return tesserati.size();
}

Squadra::~Squadra(){
    for(Vettore<Tesserato*>::iterator it = tesserati.begin(); it!=tesserati.end(); ++it){
        delete (*it);
    }
}
