#include "squadremodel.h"
#include <typeinfo>

SquadreModel::SquadreModel(QObject *parent) :
    QAbstractListModel(parent) {}

int SquadreModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return squadre.count();
}

QVariant SquadreModel::data(const QModelIndex &index, int role) const{
    if(index.row()<0 || index.row()>=squadre.count()){
        return QVariant::Invalid;
    }

    const Squadra* squadra = squadre[index.row()];
    if(role == Qt::DisplayRole){
        return squadra->getNome();
    }
    else if(role == SocietaRole){
        return squadra->getSocieta();
    }
    else if(role == VittorieRole){
        return squadra->getVittorie();
    }
    else if(role == PareggiRole){
        return squadra->getPareggi();
    }
    else if(role == SconfitteRole){
        return squadra->getSconfitte();
    }
    else if(role == PenalitaRole){
        return squadra->getPenalita();
    }
    else if(role == PuntiRole){
        return squadra->getPunti();
    }
    else if(role == DifferenzaRetiRole){
        return squadra->getDifferenzaReti();
    }
    else{
        return QVariant::Invalid;
    }
}

Squadra* SquadreModel::trova(const Squadra &s) const{
    for(QList<Squadra*>::ConstIterator it = squadre.constBegin(); it!=squadre.constEnd(); ++it){
        if(**it == s){
            return *it;
        }
    }
    return 0;
}

void SquadreModel::addSquadra(Squadra* s){
    bool inserito = false;
    for(QList<Squadra*>::Iterator it = squadre.begin(); it != squadre.end() && !inserito; ++it){
        if(s->getNome() < (*it)->getNome()){
            squadre.insert(it, s);
            inserito = true;
        }
    }
    if(!inserito){
        squadre.push_back(s);
    }
}

void SquadreModel::modificaSquadra(Squadra *vecchia, const Squadra &nuova) const{
    vecchia->modifica(nuova);
}

void SquadreModel::removeSquadra(Squadra *s){
    s->clear();
    squadre.removeAll(s);
    delete s;
}

void SquadreModel::addTesserato(Tesserato* t, const Squadra& s) const{
    for(QList<Squadra*>::ConstIterator it = squadre.constBegin(); it!=squadre.constEnd(); ++it){
        if((*it)->getNome() == s.getNome()){
            (*it)->addTesserato(t);

        }
    }
}

void SquadreModel::modificaTesserato(const Squadra& squadra, Tesserato* vecchio,  const Tesserato & nuovo) const{
    for(QList<Squadra*>::ConstIterator it=squadre.constBegin(); it!=squadre.constEnd(); ++it){
        if(**it == squadra && (*it)->trova(*vecchio)){
            (*it)->modificaTesserato(vecchio, nuovo);
        }
    }
}

unsigned int SquadreModel::size() const{
    return squadre.size();
}

bool SquadreModel::isEmpty() const{
    return squadre.isEmpty();
}

Squadra& SquadreModel::operator [] (int i) const{
    return *(squadre[i]);
}
Squadra* SquadreModel::at(int i) const{
    if(i>=0 && i<=squadre.size()){
        return squadre.at(i);
    }
    else{
        return 0;
    }
}

void SquadreModel::sort(int column, Qt::SortOrder order){
    if(column == PuntiRole && order == Qt::AscendingOrder){
        for(int i=1; i<squadre.size(); ++i){
            bool ordinato = false;
            for(int j=i-1; j>=0 && !ordinato; --j){
                Squadra* s1 = squadre.at(j+1);
                Squadra* s2 = squadre.at(j);
                if(s1->getPunti() > s2->getPunti()
                        || (s1->getPunti() == s2->getPunti()
                            && s1->getDifferenzaReti() > s2->getDifferenzaReti())
                        || (s1->getPunti() == s2->getPunti()
                            && s1->getDifferenzaReti() == s2->getDifferenzaReti()
                            && s1->getTiriSegnati() > s2->getTiriSegnati())){
                    Squadra temp = *s1;
                    *s1 = *s2;
                    *s2 = temp;
                }
                else{
                    ordinato = true;
                }
            }
        }
    }
}

void SquadreModel::clear(){
    for(QList<Squadra*>::Iterator it = squadre.begin(); it != squadre.end(); it++){
        delete *it;
    }
    squadre.clear();
}

SquadreModel::~SquadreModel(){
    for(QList<Squadra*>::Iterator it = squadre.begin(); it != squadre.end(); it++){
        delete *it;
    }
    squadre.clear();
}
