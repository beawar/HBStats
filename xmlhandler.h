#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include "squadremodel.h"
#include "eccezioni.h"

class XmlHandler
{
private:
    void writeItem();
    void readSquadra();
    void readGiocatore(const Squadra &squadra);
    void readAllenatore(const Squadra &squadra);
    void readArbitro();

    QXmlStreamWriter xmlWriter;
    QXmlStreamReader xmlReader;
    SquadreModel* squadreModel;

public:
    XmlHandler(SquadreModel* sm);
    void writeFile(QFile& file) throw(Err_Save);
    void readFile(const QString& filename) throw(Err_Open);
};

#endif // XMLHANDLER_H
