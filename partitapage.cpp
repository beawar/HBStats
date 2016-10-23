#include "partitapage.h"
#include "checklist.h"
#include <QMessageBox>


PartitaPage::PartitaPage(SquadreModel *sm, ArbitriModel *am, QWidget *parent) :
    QWizardPage(parent), squadre(sm), arbitri(am), squadra1(0), squadra2(0)
{ 

    if(!squadre->isEmpty()){
        for(unsigned int i=0; i<squadre->size(); ++i){
            squadre->at(i)->sortByName();
            checkArray.push_back(new CheckList(squadre->at(i), true, this));
        }

        layout = new QVBoxLayout;
        createView();
        createLayout();

        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        setLayout(layout);

        registerField("partita.homeTeam", squadra1ComboBox);
        registerField("partita.guestTeam", squadra2ComboBox);
        //registerField("partita.arbitro1", arbitro1ComboBox);
        //registerField("partita.arbitro2", arbitro2ComboBox);
    }
}

void PartitaPage::createView(){
    nomeButton = new QRadioButton(tr("Nome"), this);
    nomeButton->setChecked(true);
    nomeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    numeroButton = new QRadioButton(tr("Numero"), this);
    numeroButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    squadra1ComboBox = new QComboBox(this);
    squadra1ComboBox->setModel(squadre);

    squadra2ComboBox = new QComboBox(this);
    squadra2ComboBox->setModel(squadre);

    selectAllSquadra1 = new QCheckBox(tr("Seleziona tutto"), this);
    selectAllSquadra2 = new QCheckBox(tr("Seleziona tutto"), this);

    //arbitro1ComboBox = new QComboBox(this);
    //arbitro1ComboBox->setModel(arbitri);

    //arbitro2ComboBox = new QComboBox(this);
    //arbitro2ComboBox->setModel(arbitri);

    squadra1 = checkArray[squadra1ComboBox->currentIndex()];
    squadra2 = checkArray[squadra2ComboBox->currentIndex()];

    numbersSquadra1 = new QLabel(tr("Giocatori: %1 - Allenatori: %2")
                                 .arg(squadra1->checkedGiocatori()).arg(squadra1->checkedAllenatori()));
    numbersSquadra2 = new QLabel(tr("Giocatori: %1 - Allenatori: %2")
                                 .arg(squadra2->checkedGiocatori()).arg(squadra2->checkedAllenatori()));

    squadra1List = new QListView(this);
    squadra1List->setAlternatingRowColors(true);
    squadra1List->setModel(squadra1);

    squadra2List = new QListView(this);
    squadra2List->setAlternatingRowColors(true);
    squadra2List->setModel(squadra2);

    categoriaLabel = new QLabel(tr("Categoria: "), this);

    categoria = new QComboBox(this);
    categoria->addItem(tr("Regionale"));
    categoria->addItem(tr("Nazionale"));
    categoria->addItem(tr("Internazionale"));

    connect(nomeButton, SIGNAL(clicked()), this, SLOT(sort()));
    connect(numeroButton, SIGNAL(clicked()), this, SLOT(sort()));

    connect(selectAllSquadra1, SIGNAL(clicked(bool)), this, SLOT(checkAllS1(bool)));
    connect(selectAllSquadra2, SIGNAL(clicked(bool)), this, SLOT(checkAllS2(bool)));

    connect(squadra1ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateList()));
    connect(squadra2ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateList()));

    connect(squadra1List, SIGNAL(clicked(QModelIndex)), this, SLOT(checkItemS1(QModelIndex)));
    connect(squadra2List, SIGNAL(clicked(QModelIndex)), this, SLOT(checkItemS2(QModelIndex)));

    connect(squadra1, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra1List, SLOT(update()));
    connect(squadra1, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra2List, SLOT(update()));

    connect(squadra2, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra2List, SLOT(update()));
    connect(squadra2, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra1List, SLOT(update()));

    connect(squadra1, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateCheckBox()));
    connect(squadra2, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateCheckBox()));
}

void PartitaPage::createLayout(){
    squadra1Group = new QGroupBox(tr("In Casa"), this);
    squadra2Group = new QGroupBox(tr("Ospiti"), this);
    //arbitriGroup = new QGroupBox(tr("Arbitri"), this);
    radioGroup = new QGroupBox(tr("Ordina per:"), this);

    QVBoxLayout* squadra1Layout = new QVBoxLayout;
    squadra1Layout->addWidget(squadra1ComboBox);
    squadra1Layout->addWidget(selectAllSquadra1);
    squadra1Layout->addWidget(squadra1List);
    squadra1Layout->addWidget(numbersSquadra1);

    QVBoxLayout* squadra2Layout = new QVBoxLayout;
    squadra2Layout->addWidget(squadra2ComboBox);
    squadra2Layout->addWidget(selectAllSquadra2);
    squadra2Layout->addWidget(squadra2List);
    squadra2Layout->addWidget(numbersSquadra2);

    //QHBoxLayout* arbitriLayout = new QHBoxLayout;
    //arbitriLayout->addWidget(arbitro1ComboBox);
    //arbitriLayout->addWidget(arbitro2ComboBox);

    QVBoxLayout* radioLayout = new QVBoxLayout;
    radioLayout->addWidget(nomeButton);
    radioLayout->addWidget(numeroButton);

    squadra1Group->setLayout(squadra1Layout);
    squadra2Group->setLayout(squadra2Layout);
    //arbitriGroup->setLayout(arbitriLayout);
    radioGroup->setLayout(radioLayout);

    QHBoxLayout* squadreLayout = new QHBoxLayout;
    squadreLayout->addWidget(squadra1Group);
    squadreLayout->addWidget(radioGroup);
    squadreLayout->addWidget(squadra2Group);

    QHBoxLayout* categoriaLayout = new QHBoxLayout;
    categoriaLayout->addWidget(categoriaLabel);
    categoriaLayout->addWidget(categoria);

    layout->addLayout(categoriaLayout);
    layout->addLayout(squadreLayout);
    //layout->addWidget(arbitriGroup);
}

Squadra* PartitaPage::homeTeam() const{
    return squadre->at(squadra1ComboBox->currentIndex());
}

Squadra* PartitaPage::guestTeam() const{
    return squadre->at(squadra2ComboBox->currentIndex());
}

int PartitaPage::getNumberOf(Team team, Type type){
    if(type == gioc){
        if(team == home){
            return squadra1->checkedGiocatori();
        }
        else{
            return squadra2->checkedGiocatori();
        }
    }
    else{
        if(team == home){
            return squadra1->checkedAllenatori();
        }
        else{
            return squadra2->checkedAllenatori();
        }
    }
}

int PartitaPage::nextId() const{
    return -1;
}

bool PartitaPage::validatePage() const{
    if(squadra1ComboBox->currentText() == squadra2ComboBox->currentText() ||
            //arbitro1ComboBox->currentText() == arbitro2ComboBox->currentText() ||
            squadra1->checkedGiocatori() < 7 || squadra2->checkedGiocatori() < 7){
        return false;
    }
    return true;

}

Arbitro::Categoria PartitaPage::getCategoria() const{
    if(categoria->currentText() == tr("Regionale")){
        return Arbitro::regionale;
    }
    else if(categoria->currentText() == tr("Nazionale")){
        return Arbitro::nazionale;
    }
    else /*if(categoria->currentText() == tr("Internazionale"))*/
        return Arbitro::internazionale;
}

void PartitaPage::updateList(){
    squadra1 = checkArray[squadra1ComboBox->currentIndex()];
    squadra2 = checkArray[squadra2ComboBox->currentIndex()];
    squadra1List->setModel(squadra1);
    squadra2List->setModel(squadra2);

    connect(squadra1, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra1List, SLOT(update()));
    connect(squadra1, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra2List, SLOT(update()));

    connect(squadra2, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra2List, SLOT(update()));
    connect(squadra2, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra1List, SLOT(update()));

    connect(squadra1, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateCheckBox()));
    connect(squadra2, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateCheckBox()));

    updateCheckBox();
}

void PartitaPage::updateCheckBox(){
    if(squadra1->checkedGiocatori()+squadra1->checkedAllenatori() == 0){
        selectAllSquadra1->setCheckState(Qt::Unchecked);
    }
    else if(squadra1->checkedGiocatori()+squadra1->checkedAllenatori() == homeTeam()->size()){
        selectAllSquadra1->setCheckState(Qt::Checked);
    }
    else{
        selectAllSquadra1->setCheckState(Qt::PartiallyChecked);
    }

    if(squadra2->checkedGiocatori()+squadra2->checkedAllenatori() == 0){
        selectAllSquadra2->setCheckState(Qt::Unchecked);
    }
    else if(squadra2->checkedGiocatori()+squadra2->checkedAllenatori() == guestTeam()->size()){
        selectAllSquadra2->setCheckState(Qt::Checked);
    }
    else{
        selectAllSquadra2->setCheckState(Qt::PartiallyChecked);
    }

    numbersSquadra1->setText(tr("Giocatori: %1 - Allenatori: %2").arg(squadra1->checkedGiocatori()).arg(squadra1->checkedAllenatori()));

    numbersSquadra2->setText(tr("Giocatori: %1 - Allenatori: %2").arg(squadra2->checkedGiocatori()).arg(squadra2->checkedAllenatori()));

    update();
}

void PartitaPage::checkItemS1(QModelIndex index){
    bool ischeck = squadra1->data(index, Qt::CheckStateRole).toBool();
    if(ischeck){  
        squadra1->setData(index, Qt::Unchecked, Qt::CheckStateRole);
    }
    else{
        if(dynamic_cast<Giocatore*>(homeTeam()->at(index.row())) && squadra1->checkedGiocatori()<maxGiocatori){
            squadra1->setData(index, Qt::Checked, Qt::CheckStateRole);
        }
        else if(dynamic_cast<Allenatore*>(homeTeam()->at(index.row())) && squadra1->checkedAllenatori()<maxAllenatori){
            squadra1->setData(index, Qt::Checked, Qt::CheckStateRole);
        }
        else{
            QMessageBox::warning(this, tr("Numero massimo raggiunto"),
                                 tr("E' stato raggiunto il numero massimo di giocatori (%1) "
                                    "o allenatori (%2) consentiti a referto").arg(QString::number(maxGiocatori),
                                                                                  QString::number(maxAllenatori)));
        }
    }
}

void PartitaPage::checkItemS2(QModelIndex index){
    bool ischeck = squadra2->data(index, Qt::CheckStateRole).toBool();
    if(ischeck){
        squadra2->setData(index, Qt::Unchecked, Qt::CheckStateRole);
    }
    else{
        if(dynamic_cast<Giocatore*>(guestTeam()->at(index.row())) && squadra2->checkedGiocatori()<maxGiocatori){
            squadra2->setData(index, Qt::Checked, Qt::CheckStateRole);
        }
        else if(dynamic_cast<Allenatore*>(guestTeam()->at(index.row())) && squadra2->checkedAllenatori()<maxAllenatori){
            squadra2->setData(index, Qt::Checked, Qt::CheckStateRole);
        }
        else{
            QMessageBox::warning(this, tr("Numero massimo raggiunto"),
                                 tr("E' stato raggiunto il numero massimo di giocatori (%1) "
                                    "o allenatori (%2) consentiti a referto").arg(QString::number(maxGiocatori),
                                                                                  QString::number(maxAllenatori)));
        }
    }
}

void PartitaPage::checkAllS1(bool c){
    if(c){
        for(unsigned int i=0; i<homeTeam()->size(); ++i)
        {
            /*if(dynamic_cast<Giocatore*>(homeTeam()->at(i)) && squadra1->checkedGiocatori()<maxGiocatori){
                squadra1->setData(squadra1->index(i), Qt::Checked, Qt::CheckStateRole);
            }
            else if(dynamic_cast<Allenatore*>(homeTeam()->at(i)) && squadra1->checkedAllenatori()<maxAllenatori){
                squadra1->setData(squadra1->index(i), Qt::Checked, Qt::CheckStateRole);
            }*/
            squadra1->setData(squadra1->index(i), Qt::Checked, Qt::CheckStateRole);
        }
    }
    else if(!c){
        for(unsigned int i=0; i<homeTeam()->size(); ++i)
        {
            squadra1->setData(squadra1->index(i), Qt::Unchecked, Qt::CheckStateRole);
        }
    }

}

void PartitaPage::checkAllS2(bool c){
    if(c){
        for(unsigned int i=0; i<guestTeam()->size(); ++i)
        {
            /*
            if(dynamic_cast<Giocatore*>(guestTeam()->at(i)) && squadra2->checkedGiocatori()<maxGiocatori){
                squadra2->setData(squadra2->index(i), Qt::Checked, Qt::CheckStateRole);
            }
            else if(dynamic_cast<Allenatore*>(guestTeam()->at(i)) && squadra2->checkedAllenatori()<maxAllenatori){
                squadra2->setData(squadra2->index(i), Qt::Checked, Qt::CheckStateRole);
            }
            */
            squadra2->setData(squadra2->index(i), Qt::Checked, Qt::CheckStateRole);
        }
    }
    else if(!c){
        for(unsigned int i=0; i<guestTeam()->size(); ++i)
        {
            squadra2->setData(squadra2->index(i), Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}

void PartitaPage::sort(){
    for(unsigned int i=0; i<squadre->size(); ++i){
        if(nomeButton->isChecked()){
            squadre->at(i)->sortByName();
        }
        else if(numeroButton->isChecked()){
            squadre->at(i)->sortByNumber();
        }
        checkArray[i]->updateList();
    }
}
