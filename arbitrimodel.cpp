#include "arbitrimodel.h"

ArbitriModel::ArbitriModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int ArbitriModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return arbitri.count();
}

int ArbitriModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 4;
}

QVariant ArbitriModel::data(const QModelIndex &index, int role) const{

    if(index.row()<0 || index.row()>=arbitri.count()){
        return QVariant::Invalid;
    }

    const Arbitro* arbitro = arbitri[index.row()];
    if(role == Qt::DisplayRole){
        return QString(arbitro->getNome() + " " + arbitro->getCognome());
    }
    else if(role == ArbitroRole){
        return arbitro;
    }
    else{
        return QVariant::Invalid;
    }
}

QVariant ArbitriModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation == Qt::Horizontal){
        Q_UNUSED(section);
        if(role == NomeRole)
            return tr("Nome");
        else if(role == CognomeRole){
            return tr("Cognome");
        }
        else if(role == DataRole){
            return tr("Data di Nascita");
        }
        else if(role == LivelloRole){
            return tr("Livello");
        }
    }
    return "";
}

void ArbitriModel::addArbitro(Arbitro *a){
    arbitri.push_back(a);
}

void ArbitriModel::modificaArbitro(Arbitro *vecchio, const Arbitro &nuovo) const{
    vecchio->modifica(nuovo);
}

void ArbitriModel::removeArbitro(Arbitro *a){
    arbitri.removeAll(a);
    delete a;
}

unsigned int ArbitriModel::size() const{
    return arbitri.size();
}

Arbitro* ArbitriModel::trova(const Arbitro &a) const{
    for(QList<Arbitro*>::ConstIterator it = arbitri.constBegin(); it<arbitri.constEnd(); ++it){
        if(**it == a){
            return *it;
        }
    }
    return 0;
}

Arbitro* ArbitriModel::at(int i) const{
    if(i>=0){
        return arbitri[i];
    }
    else{
        return 0;
    }
}

Arbitro& ArbitriModel::operator [] (int i) const{
    return *(arbitri[i]);
}

bool ArbitriModel::isEmpty() const{
    return arbitri.isEmpty();
}

void ArbitriModel::clear(){
    arbitri.clear();
}

ArbitriModel::~ArbitriModel(){
    for(QList<Arbitro*>::Iterator it = arbitri.begin(); it != arbitri.end(); it++){
        delete *it;
    }
}
