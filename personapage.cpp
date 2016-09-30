#include "personapage.h"
#include <QMessageBox>

PersonaPage::PersonaPage(SquadreModel *sm, ArbitriModel* am, QWidget *parent)
    : QWizardPage(parent), squadre(sm), arbitri (am)
{
    createButtons();
    createEditor();
    createLayout();

    changeEditor();

    setLayout(layout);
}

void PersonaPage::createButtons(){
    giocatoreButton = new QRadioButton(tr("Giocatore"), this);
    connect(giocatoreButton, SIGNAL(clicked()), this, SLOT(changeEditor()));
    giocatoreButton->setChecked(true);
    portiereButton = new QCheckBox(tr("Portiere"), this);
    allenatoreButton = new QRadioButton(tr("Allenatore"), this);
    connect(allenatoreButton, SIGNAL(clicked()), this, SLOT(changeEditor()));
    //arbitroButton = new QRadioButton(tr("Arbitro"), this);
    //connect(arbitroButton, SIGNAL(clicked()), this, SLOT(changeEditor()));

    radioButtonGroup = new QButtonGroup(this);
    radioButtonGroup->addButton(giocatoreButton, giocatore);
    radioButtonGroup->addButton(allenatoreButton, allenatore);
    //radioButtonGroup->addButton(arbitroButton, arbitro);

    if(squadre->isEmpty()){
        giocatoreButton->setDisabled(true);
        allenatoreButton->setDisabled(true);
        //arbitroButton->setChecked(true);
    }

    insertButton = new QPushButton(tr("Inserisci"), this);
    insertButton->setEnabled(false);
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertPerson()));
}

void PersonaPage::createEditor(){
    nomeLabel = new QLabel(tr("Nome:"), this);
    nomeLabel->setAlignment(Qt::AlignCenter);
    nomeEdit = new QLineEdit(this);
    connect(nomeEdit, SIGNAL(textChanged(QString)), this, SLOT(validateData()));

    cognomeLabel = new QLabel(tr("Cognome:"), this);
    cognomeLabel->setAlignment(Qt::AlignCenter);
    cognomeEdit = new QLineEdit(this);
    connect(cognomeEdit, SIGNAL(textChanged(QString)), this, SLOT(validateData()));

    dataLabel = new QLabel(tr("Data di Nascita:"), this);
    dataLabel->setAlignment(Qt::AlignCenter);
    dataEdit = new QDateEdit(this);
    dataEdit->setDisplayFormat("dd/MM/yyyy");
    dataEdit->setMaximumDate(QDate::currentDate());
    dataEdit->setDate(QDate(1990, 1, 1));
    dataEdit->calendarPopup();

    numeroLabel = new QLabel(tr("Numero:"), this);
    numeroLabel->setAlignment(Qt::AlignCenter);
    numeroEdit = new QSpinBox(this);
    numeroEdit->setRange(1, 99);

    squadraLabel = new QLabel(tr("Squadra:"), this);
    squadraLabel->setAlignment(Qt::AlignCenter);
    squadraEdit = new QComboBox(this);
    squadraEdit->setModel(squadre);

    /*
     *livelloLabel = new QLabel(tr("Livello:"), this);
     *livelloLabel->setAlignment(Qt::AlignCenter);
     *livelloEdit = new QSpinBox(this);
     *livelloEdit->setRange(0, 3);
    */
}

void PersonaPage::createLayout(){
    radioLayout = new QVBoxLayout;
    radioLayout->addWidget(giocatoreButton);
    radioLayout->addWidget(portiereButton);
    radioLayout->addWidget(allenatoreButton);
    //radioLayout->addWidget(arbitroButton);
    radioLayout->addStretch(1);

    buttonGroupBox = new QGroupBox(tr("Nuovo"), this);
    buttonGroupBox->setLayout(radioLayout);

    editorLayout = new QGridLayout;
    editorLayout->addWidget(nomeLabel, 1, 1);
    editorLayout->addWidget(nomeEdit, 1, 2, 1, 2);
    editorLayout->addWidget(cognomeLabel, 2, 1);
    editorLayout->addWidget(cognomeEdit, 2, 2, 1, 2);
    editorLayout->addWidget(dataLabel, 3, 1);
    editorLayout->addWidget(dataEdit, 3, 2);
    editorLayout->addWidget(numeroLabel, 4, 1);
    editorLayout->addWidget(numeroEdit, 4, 2);
    editorLayout->addWidget(squadraLabel, 5, 1);
    editorLayout->addWidget(squadraEdit, 5, 2, 1, 2);
    //editorLayout->addWidget(livelloLabel, 6, 1);
    //editorLayout->addWidget(livelloEdit, 6, 2);

    layout = new QHBoxLayout;
    layout->addWidget(buttonGroupBox);
    layout->addLayout(editorLayout);
    layout->addWidget(insertButton, 3, Qt::AlignBottom);
}


int PersonaPage::nextId() const{
    return -1;
}

void PersonaPage::validateData(){
    if(!nomeEdit->text().isEmpty() && !cognomeEdit->text().isEmpty()){
        insertButton->setEnabled(true);
    }
    else{
        insertButton->setEnabled(false);
    }
}

void PersonaPage::changeEditor(){
    switch(radioButtonGroup->checkedId()){
    case giocatore:
        portiereButton->setEnabled(true);
        numeroEdit->setEnabled(true);
        squadraEdit->setEnabled(true);
        //livelloEdit->setEnabled(false);
        break;
    case allenatore:
        portiereButton->setEnabled(false);
        numeroEdit->setEnabled(false);
        squadraEdit->setEnabled(true);
        //livelloEdit->setEnabled(false);
        break;
    case arbitro:
        portiereButton->setEnabled(false);
        numeroEdit->setEnabled(false);
        squadraEdit->setEnabled(false);
        //livelloEdit->setEnabled(true);
        break;
    default:
        break;
    }
}

void PersonaPage::insertPerson(){
    try{
        switch(radioButtonGroup->checkedId()){
            case giocatore:
            {
                if(portiereButton->isChecked()){
                    Portiere* gioc = new Portiere;
                    gioc->setNome(nomeEdit->text());
                    gioc->setCognome(cognomeEdit->text());
                    gioc->setData(dataEdit->date());
                    gioc->setNumero(numeroEdit->value());
                    squadre->addTesserato(gioc, Squadra(squadraEdit->currentText()));
                }
                else{
                    Giocatore* gioc = new Giocatore;
                    gioc->setNome(nomeEdit->text());
                    gioc->setCognome(cognomeEdit->text());
                    gioc->setData(dataEdit->date());
                    gioc->setNumero(numeroEdit->value());
                    squadre->addTesserato(gioc, Squadra(squadraEdit->currentText()));
                }
            }
            break;
            case allenatore:
            {
                Allenatore* all = new Allenatore;
                all->setNome(nomeEdit->text());
                all->setCognome(cognomeEdit->text());
                all->setData(dataEdit->date());
                squadre->addTesserato(all, Squadra(squadraEdit->currentText()));
            }
            break;
        /*
        *case arbitro:
        *    {
        *        Arbitro* arb = new Arbitro;
        *        arb->setNome(nomeEdit->text());
        *        arb->setCognome(cognomeEdit->text());
        *        arb->setData(dataEdit->date());
        *        arb->setLivello(livelloEdit->value());
        *        arbitri->addArbitro(arb);
        *    }
        *    break;
        */
        }
        nomeEdit->clear();
        cognomeEdit->clear();
        dataEdit->setDate(QDate(1990, 1, 1));
        numeroEdit->clear();
        //livelloEdit->clear();
        emit personaCreata();
    }
    catch(Err_Tesserato e){
        QMessageBox::warning(this, tr("Inserimento non riuscito"),
                             tr("Il tesserato che si vuole inserire è già presente in memoria"),
                             QMessageBox::Ok);
    }
}
