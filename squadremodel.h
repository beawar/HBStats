#ifndef SQUADREMODEL_H
#define SQUADREMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include "squadra.h"

class SquadreModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<Squadra*> squadre;
public:
    enum {NomeRole = Qt::UserRole+1, SocietaRole, VittorieRole,
                      PareggiRole, SconfitteRole, PenalitaRole, PuntiRole, DifferenzaRetiRole};

    explicit SquadreModel(QObject *parent = 0);
    ~SquadreModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole ) const;

    Squadra* trova(const Squadra& s) const;
    void addSquadra(Squadra *);
    void modificaSquadra(Squadra*, const Squadra&) const;
    void removeSquadra(Squadra*);

    void addTesserato(Tesserato *, const Squadra&) const;
    void modificaTesserato(const Squadra& , Tesserato *, const Tesserato&) const;

    unsigned int size() const;
    bool isEmpty() const;
    Squadra& operator [](int) const;
    Squadra* at(int i) const;

    void sort(int column = PuntiRole, Qt::SortOrder order = Qt::AscendingOrder);

    void clear();
signals:

public slots:

};

#endif // SQUADREMODEL_H
