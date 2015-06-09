#include "xmldom.h"

XmlDom::XmlDom(string Home)
{
    HOME=Home;
    dom=new QDomDocument("xml_doc");
    file=new QFile(QString::fromStdString(HOME+"datas.xml"));
    bool exist=file->exists();
    if(!file->open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this, "Erreur fichier", "Le fichier de données n'a pus être ouvert !");
        delete dom;
        exit(1);
    }
    if(exist) {
        if(!dom->setContent(file)) {
            file->close();
            delete dom;
            QMessageBox::warning(this, "Erreur XML", "Les données sont corrompues.");
            exit(1);
        }
    } else {
        root=dom->createElement("root");
        dom->appendChild(root);
        saveDom();
    }
    file->close();
    root=dom->documentElement();
}

QStringList XmlDom::getMonthsOfYear(int yearVal) {
    QStringList list;
    QDomNodeList nodes=root.childNodes();
    for(int i=0; i<nodes.size(); i++) {
        QDomNode node=nodes.item(i);
        QDomNode year=node.namedItem("year");
        int val=year.toElement().text().toInt();
        if(val==yearVal) {
            QDomNode month=node.namedItem("month");
            int valM=month.toElement().text().toInt();
            if(!list.contains(QString::number(valM))) {
                list.insert(0, QString::number(valM));
            }
        }
    }
    list.sort();
    return list;
}

QStringList XmlDom::getAllYears() {
    QStringList list;
    QDomNodeList nodes=root.childNodes();
    for(int i=0; i<nodes.size(); i++) {
        QDomNode node=nodes.item(i);
        QDomNode year=node.namedItem("year");
        int val=year.toElement().text().toInt();
        if(!list.contains(QString::number(val))) {
            list.insert(0, QString::number(val));
        }
    }
    list.sort();
    return list;
}


double XmlDom::getCaMois(int month, int year) {
    QDate *qDate=new QDate(year, month, 1);
    Record *record=new Record(qDate);
    int exist=exists(record);
    if(exist==-1) {
        return 0.0;
    } else {
        QDomNodeList list=root.childNodes();
        QDomNode node=list.item(exist);
        QDomNode ca=node.namedItem("ca");
        return ca.toElement().text().toDouble();
    }
}

int XmlDom::exists(Record *record) {
    QString qStrMonth=QString::number(record->getQDate()->month());
    QString qStrYear=QString::number(record->getQDate()->year());
    int exists=-1;
    QDomNodeList list=root.childNodes();
    for(int i=0; i<list.size(); i++) {
        QDomNode node=list.item(i);
        QDomNode year=node.namedItem("year");
        QDomNode month=node.namedItem("month");
        //cout << month.toElement().text().toStdString() << " " << qStrMonth.toStdString() << endl;
        if(year.toElement().text().toStdString()==qStrYear.toStdString()&&month.toElement().text().toStdString()==qStrMonth.toStdString()) {
            exists=i;
            break;
        }
    }
    //cout << exists << endl;
    return exists;
}

void XmlDom::addMonth(Record *record) {
    int exis=exists(record);
    //
    QString qStrMonth=QString::number(record->getQDate()->month());
    QDomText mText=dom->createTextNode(qStrMonth);
    QString qStrYear=QString::number(record->getQDate()->year());
    QDomText yText=dom->createTextNode(qStrYear);
    QString qStrCa=QString::number(record->getCa());
    QDomText caText=dom->createTextNode(qStrCa);
    if(exis>=0) {
        QDomNodeList list=root.childNodes();
        QDomNode node=list.item(exis);
        QDomNode ca=node.namedItem("ca");
        node.removeChild(ca);
        ca=dom->createElement("ca");
        ca.appendChild(caText);
        node.appendChild(ca);
    } else {
    QDomElement rec=dom->createElement("record");
    QDomElement month=dom->createElement("month");
    month.appendChild(mText);
    QDomElement year=dom->createElement("year");
    year.appendChild(yText);
    //
    QDomElement ca=dom->createElement("ca");

    ca.appendChild(caText);
    //
    rec.appendChild(year);
    rec.appendChild(month);
    rec.appendChild(ca);
    //
    root.appendChild(rec);
    //
    }
    saveDom();
}

void XmlDom::saveDom() {
    file=new QFile(QString::fromStdString(HOME+"datas.xml"));
    if(file->open(QIODevice::WriteOnly)) {
    QString writeDoc=dom->toString();
    QTextStream stream(file);
    stream << writeDoc;
    file->close();
    }
}
string XmlDom::getHOME() const
{
    return HOME;
}

void XmlDom::setHOME(const string &value)
{
    HOME = value;
}


XmlDom::~XmlDom() {
    delete dom;
}
