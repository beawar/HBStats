#include "checklist.h"
#include <QVBoxLayout>
#include "squadremodel.h"

CheckList::CheckList(Squadra *s, bool checkable, QObject *parent) :
    QStringListModel(parent), squadra(s), checkableItems(checkable)
{
    giocatori = 0;
    allenatori = 0;
    if(squadra){
        for(int i=0; i<squadra->size(); ++i){
            strList.push_back(squadra->at(i)->getInfo());
            if(squadra->at(i)->isChecked()){
                if(dynamic_cast<const Giocatore*>(squadra->at(i))){
                    giocatori++;
                }
                else if(dynamic_cast<const Allenatore*>(squadra->at(i))){
                    allenatori++;
                }
            }
        }
    }
    setStringList(strList);
}

Qt::ItemFlags CheckList::flags(const QModelIndex &index) const{
    if(index.isValid()){
        if(itemsAreCheckable()){
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemNeverHasChildren;
        }
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
}

QVariant CheckList::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    else if(itemsAreCheckable() && role == Qt::CheckStateRole){
        return squadra->at(index.row())->isChecked() ?
                    Qt::Checked : Qt::Unchecked;
    }
    else if(role == Qt::DisplayRole){
        if(index.row()<strList.size()){
            return strList[index.row()];
        }
    }
    return QVariant();
}

bool CheckList::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid()){
        return false;
    }
    else if(itemsAreCheckable() && role == Qt::CheckStateRole){
        if(value == Qt::Checked){
            squadra->at(index.row())->setChecked(true);
            if(dynamic_cast<const Giocatore*>(squadra->at(index.row()))){
                giocatori++;
            }
            else if(dynamic_cast<const Allenatore*>(squadra->at(index.row()))){
                allenatori++;
            }
            emit dataChanged(index, index);
            return true;
        }
        else if(value == Qt::Unchecked){
            squadra->at(index.row())->setChecked(false);
            if(dynamic_cast<const Giocatore*>(squadra->at(index.row()))){
                giocatori--;
            }
            else if(dynamic_cast<const Allenatore*>(squadra->at(index.row()))){
                allenatori--;
            }
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;

}

void CheckList::updateList(){
    if(squadra){
        strList.clear();
        for(int i=0; i<squadra->size(); ++i){
            strList.push_back(squadra->at(i)->getInfo());
        }
        setStringList(strList);
    }
}

bool CheckList::itemsAreCheckable() const{
    return checkableItems;
}

int CheckList::checkedGiocatori() const{
    return giocatori;
}

int CheckList::checkedAllenatori () const{
    return allenatori;
}
