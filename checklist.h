#ifndef CHECKLIST_H
#define CHECKLIST_H

#include <QStringListModel>
#include <QStringList>
#include <QCheckBox>
#include <QSet>
#include <QGroupBox>
#include "squadra.h"

class CheckList : public QStringListModel
{
    Q_OBJECT
private:
    Squadra* squadra;
    QStringList strList;
    bool checkableItems;
    int giocatori;
    int allenatori;

public:
    explicit CheckList(Squadra* s, bool checkable, QObject *parent = 0);
    Qt::ItemFlags flags (const QModelIndex &index = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void updateList();
    bool itemsAreCheckable() const;
    int checkedGiocatori () const;
    int checkedAllenatori () const;
};

#endif // CHECKLIST_H
