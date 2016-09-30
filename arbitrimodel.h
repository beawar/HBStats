#ifndef ARBITRIMODEL_H
#define ARBITRIMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "arbitro.h"

class ArbitriModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QList<Arbitro*> arbitri;
public:
    enum {ArbitroRole = Qt::UserRole+1, NomeRole, CognomeRole, DataRole, LivelloRole};
    explicit ArbitriModel(QObject *parent = 0);
    ~ArbitriModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void addArbitro(Arbitro* a);
    void modificaArbitro(Arbitro* vecchio, const Arbitro& nuovo) const;
    void removeArbitro(Arbitro* a);

    unsigned int size() const;
    Arbitro* trova(const Arbitro& a) const;
    Arbitro* at(int i) const;
    Arbitro& operator [] (int) const;
    bool isEmpty() const;

    void clear();
signals:

public slots:

};

#endif // ARBITRIMODEL_H
