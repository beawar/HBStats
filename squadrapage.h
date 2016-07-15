#ifndef SQUADRAPAGE_H
#define SQUADRAPAGE_H

#include <QWizardPage>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include "squadremodel.h"

class SquadraPage : public QWizardPage
{
    Q_OBJECT
private:
    SquadreModel* squadre;
    void createEditor();
    void createLayout();

    QVBoxLayout* layout;

    QLabel* nomeLabel;
    QLabel* societaLabel;
    QLineEdit* nomeEdit;
    QLineEdit* societaEdit;
    QPushButton* insertButton;

private slots:
    void insertTeam();
    void validateData();


public:
    explicit SquadraPage(SquadreModel* sm, QWidget *parent = 0);

    int nextId() const;

signals:
    void squadraCreata();

public slots:

};

#endif // SQUADRAPAGE_H
