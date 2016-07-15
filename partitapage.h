#ifndef PARTITAPAGE_H
#define PARTITAPAGE_H

#include <QWizardPage>
#include <QListView>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>
#include <QRadioButton>
#include <vector>
#include "checklist.h"
#include "squadremodel.h"
#include "tabs.h"

class PartitaPage : public QWizardPage
{
    Q_OBJECT
private:
    enum {maxGiocatori = 14, maxAllenatori = 2};
    void createView();
    void createLayout();
    Squadra* homeTeam() const;
    Squadra* guestTeam() const;

    SquadreModel* squadre;

    QVBoxLayout* layout;

    QGroupBox* squadra1Group;
    QGroupBox* squadra2Group;
    QGroupBox* radioGroup;

    QRadioButton* nomeButton;
    QRadioButton* numeroButton;

    QComboBox* squadra1ComboBox;
    QComboBox* squadra2ComboBox;

    QListView* squadra1List;
    QListView* squadra2List;

    std::vector<CheckList*> checkArray;

    CheckList* squadra1;
    CheckList* squadra2;

private slots:
    void updateList();
    void checkItemS1(QModelIndex index);
    void checkItemS2(QModelIndex index);
    void sort();

public:
    explicit PartitaPage(SquadreModel* sm, QWidget *parent = 0);

    int nextId() const;
    bool validatePage() const;

signals:

public slots:

};

#endif // PARTITAPAGE_H
