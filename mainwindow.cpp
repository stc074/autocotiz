#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     init();
}

MainWindow::~MainWindow()
{
    delete domParams;
    delete xmlDom;
    delete ui;
}

void MainWindow::init() {
    setWindowTitle("Auto-Cotiz 15.6");
    eventOk=false;
    HOME=getenv("HOME");
    if(HOME.empty()) {
        HOME="/home";
    }
    HOME+="/ca_auto_entrepreneur/";
    domParams=new QDomDocument("xml_params");
    initFiles();
    QDate qDate;
    qDate=qDate.currentDate();
    ui->dateEdit->setDate(qDate);
    ui->formFrame->hide();
    ui->formFrame2->hide();
    ui->formFrame1->hide();
    //
    initPcs();
    //
    QStringList list;
    int year=qDate.year();
    for(int i=2008; i<=year; i++) {
        list.insert(0, QString::number(i));
    }
    ui->comboBox->addItems(list);
    list.clear();
    //
    list.insert(0, QString::fromStdString("4°Trimestre Oct/Nov/Déc"));
    list.insert(0, QString::fromStdString("3°Trimestre Juil/Aou/Sep"));
    list.insert(0, QString::fromStdString("2°Trimestre Avr/Mai/Jui"));
    list.insert(0, QString::fromStdString("1°Trimestre Jan/Fév/Mar"));
    ui->comboBox_2->addItems(list);
    int month=qDate.month();
    int index=month/4;
    //
    //
    trimestre=index;
    annee=year;
    calcCa();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(index);
    //
    xmlDom=new XmlDom(HOME);
    //
    ui->comboBox_3->addItems(xmlDom->getAllYears());
    if(!ui->comboBox_3->size().isEmpty()) {
        convertMonthsArchive(xmlDom->getMonthsOfYear(ui->comboBox_3->itemText(0).toInt()));
    }
    //
    eventOk=true;
}

void MainWindow::convertMonthsArchive(QStringList list) {
    ui->comboBox_4->clear();
    ui->comboBox_4->addItem(QString::fromStdString("Choisissez :"));
    QStringList monthsList;
    string months[12]={"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"};
    for(int i=0; i<list.size(); i++) {
        int index=list.value(i).toInt();
        monthsList.insert(index, QString::fromStdString(months[index-1]));
    }
    ui->comboBox_4->addItems(monthsList);
}

void MainWindow::initPcs() {
    QFile *file=new QFile(QString::fromStdString(HOME+"params.xml"));
    file->open(QIODevice::ReadOnly);
    domParams->setContent(file);
    file->close();
    delete file;
    QDomElement root=domParams->documentElement();
    QDomNode nodPcPrinc=root.firstChild();
    QDomNode nodPcForm=root.lastChild();
    pcPrinc=nodPcPrinc.toElement().text().toDouble();
    pcForm=nodPcForm.toElement().text().toDouble();
    ui->doubleSpinBox_2->setValue(pcPrinc);
    ui->doubleSpinBox_3->setValue(pcForm);
}

void MainWindow::initFiles() {
    string dir=HOME;
    struct stat sb;
    if (!(stat(dir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)))
    {
        mkdir(dir.c_str(), 0777);
    }
    QFile *file=new QFile(QString::fromStdString(HOME+"params.xml"));
    if(!file->exists()) {
        file->open(QIODevice::WriteOnly);
        QDomElement root=domParams->createElement("root");
        domParams->appendChild(root);
        QDomElement pcCotElem=domParams->createElement("pccotis");
        QString qStrPcCot=QString::number(22.9);
        QDomText qdText=domParams->createTextNode(qStrPcCot);
        pcCotElem.appendChild(qdText);
        root.appendChild(pcCotElem);
        QDomElement pcCotFormElem=domParams->createElement("pcform");
        QString qStrPcForm=QString::number(1.0);
        qdText=domParams->createTextNode(qStrPcForm);
        pcCotFormElem.appendChild(qdText);
        root.appendChild(pcCotFormElem);
        saveParams();
        file->close();
     }
    delete file;

}

void MainWindow::saveParams() {
    QFile *file=new QFile(QString::fromStdString(HOME+"params.xml"));
    if(file->open(QIODevice::WriteOnly)) {
    QString writeDoc=domParams->toString();
    QTextStream stream(file);
    stream << writeDoc;
    file->close();
    }
    delete file;
}

void MainWindow::calcCa() {
        Declaration *decla=new Declaration(trimestre, annee, pcPrinc, pcForm, HOME);
        ui->label_mois1->setText(QString::fromStdString("CA "+decla->getMois1()+" : "));
        ui->label_mois2->setText(QString::fromStdString("CA "+decla->getMois2()+" : "));
        ui->label_mois3->setText(QString::fromStdString("CA "+decla->getMois3()+" : "));
        ui->label_ca_mois1->setText(QString::number(decla->getCa1())+QString::fromStdString(" €."));
        ui->label_ca_mois2->setText(QString::number(decla->getCa2())+QString::fromStdString(" €."));
        ui->label_ca_mois3->setText(QString::number(decla->getCa3())+QString::fromStdString(" €."));
        ui->label_ca_trim->setText(QString::number(decla->getCatTotal())+QString::fromStdString(" €."));
        ui->label_cotis1->setText(QString::number(decla->getCotis())+QString::fromStdString(" €."));
        ui->label_cotis_form_2->setText(QString::number(decla->getCotisForm())+QString::fromStdString(" €."));
        ui->label_cotis->setText(QString::number((int)decla->getCotisTotal())+QString::fromStdString(" €."));
        delete decla;
}

void MainWindow::on_actionAjouter_un_mois_triggered()
{
    ui->formFrame->hide();
    ui->formFrame2->hide();
    ui->formFrame1->show();
}

void MainWindow::on_actionD_claration_urssaf_triggered()
{
    ui->formFrame->hide();
    ui->formFrame1->hide();
    calcCa();
    ui->formFrame2->show();
}

void MainWindow::on_actionArchives_CA_triggered()
{
    ui->formFrame1->hide();
    ui->formFrame2->hide();
    ui->formFrame->show();
}

void MainWindow::on_pushButton_clicked()
{
    QDate qDate=ui->dateEdit->date();
    double ca=ui->doubleSpinBox->value();
    Record *record=new Record(&qDate, ca);
    bool rec=true;
    if(xmlDom->exists(record)>=0) {
    QMessageBox::StandardButton reply;
        reply=QMessageBox::question(this, "Attention", "Un enregistrement pour cette date a déjà été enregistré, voulez vous l'écraser ?", QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::No) {
            rec=false;
        }
    }
    if(rec) {
    xmlDom->addMonth(record);
    ui->formFrame->hide();
    QMessageBox::information(this, "Enregistrement effectué.", "Votre CA a bien été enregistré !");
    } else {
        QMessageBox::information(this, "Enregistrement abandonné.", "Saisie abandonnée !");
    }
}



void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(eventOk) {
    annee=arg1.toInt();
    //cout << "annee " << annee << endl;
    calcCa();
    }
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if(eventOk) {
    trimestre=index;
    //cout << "trimestre " << trimestre << endl;
    calcCa();
    }
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    if(eventOk) {
    //cotisation normale
    QDomElement root=domParams->documentElement();
    QDomNode nod=root.firstChild();
    QDomNode nodRep=domParams->createElement(QString::fromStdString("pccotis"));
    QDomText qdTextNew=domParams->createTextNode(QString::number(arg1));
    nodRep.appendChild(qdTextNew);
    root.replaceChild(nodRep, nod);
    pcPrinc=arg1;
    saveParams();
    calcCa();
    }
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
    if(eventOk) {
    //cotisation normale
    QDomElement root=domParams->documentElement();
    QDomNode nod=root.lastChild();
    QDomNode nodRep=domParams->createElement(QString::fromStdString("pcform"));
    QDomText qdTextNew=domParams->createTextNode(QString::number(arg1));
    nodRep.appendChild(qdTextNew);
    root.replaceChild(nodRep, nod);
    pcForm=arg1;
    saveParams();
    calcCa();
    }

}


void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    if(index<=12&&index>=1&&eventOk) {
        int month=getMonthKey(ui->comboBox_4->itemText(index).toStdString());
        if(month!=0) {
        int year=ui->comboBox_3->itemText(ui->comboBox_3->currentIndex()).toInt();
        Archive *archive=new Archive(month, year, HOME);
        ui->label_ca_mois_enr->setText(QString::fromStdString("Mois de "+archive->getMonthName()+" "+archive->getYear()+" : "));
        ui->label_ca_mois_enr_val->setText(QString::fromStdString(archive->getCa()+" € de chiffre d'affaire."));
        delete archive;
        }
    }
}

int MainWindow::getMonthKey(string month) {
    string months[12]={"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"};
    int key=0;
    for(int i=1; i<=12; i++) {
        if(month==months[i-1]) {
            key=i;
            break;
        }
    }
    return key;
}

void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    if(eventOk) {
        convertMonthsArchive(xmlDom->getMonthsOfYear(arg1.toInt()));
    }
}

void MainWindow::on_actionA_propos_triggered()
{
    QMessageBox::information(this, "Auto-cotiz : à propos", "<div style=\"font-family: Arial, sans-serif; color: #3333cc;\"><h1>Auto-Cotiz 15.6</h1><p>Codé par Pierre-jean Hardibo</p><p><a href=\"http://www.hardibopj.com\">http://www.hardibopj.com</a></p>");
}
