#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>

#include <cstdlib>
#include <sys/stat.h>
#include "xmldom.h"
#include "record.h"
#include "declaration.h"
#include "archive.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAjouter_un_mois_triggered();

    void on_pushButton_clicked();

    void on_actionD_claration_urssaf_triggered();


    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_actionArchives_CA_triggered();

    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_actionA_propos_triggered();

private:
    Ui::MainWindow *ui;
    void init();
    void calcCa();
    void initFiles();
    void saveParams();
    void initPcs();
    void convertMonthsArchive(QStringList);
    int getMonthKey(string);
    QWidget* mainWidget;
    QMenu* menu;
    QDomDocument *domParams;
    XmlDom* xmlDom;
    int trimestre;
    int annee;
    double pcPrinc;
    double pcForm;
    string HOME;
    bool eventOk;
};

#endif // MAINWINDOW_H
