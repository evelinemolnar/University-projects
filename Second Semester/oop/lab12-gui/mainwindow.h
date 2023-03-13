#pragma once

#include "Service.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "RetetaGUI.h"
/*
class Console;
class Desenator : public QWidget, public Observer
{
private:
    Service& srv;
    void connectSignals() {
        srv.addObserver(this);
    }
public:
    Desenator(Service& srv) : srv{ srv } { connectSignals(); }
    void paintEvent(QPaintEvent* ev) override {
        QPainter p{ this };
        int i = 50;
        for (const auto& el : srv.toateDinCos()) {
            p.drawRect(i, i, 150, 150);
            p.fillRect(i, i, 150, 150, QBrush{ Qt::cyan, Qt::SolidPattern });
            i = i + 50;
        }
    }
    void update() override {
        repaint();
    }

    ~Desenator() {
        srv.removeObserver(this);
    }
};

*/
class GUI: public QWidget {
private:
    Service& serv;

    QLabel* denumire = new QLabel{ "Denumire: " };
    QLabel* producator = new QLabel{ "Producator: " };
    QLabel* subs_act = new QLabel{ "Substanta activa: " };
    QLabel* pret = new QLabel{ "Pret: " };

    QLineEdit* edit_denumire;
    QLineEdit* edit_producator;
    QLineEdit* edit_subs;
    QLineEdit* edit_pret;

    QPushButton* addMed;

    QLabel* mod_denumire = new QLabel{ "Modifica denumire medicament: " };
    QLabel* mod_prod = new QLabel{ "Modifica denumire producator: " };
    QLabel* mod_subs = new QLabel{ "Modifica substanta activa: " };
    QLabel* mod_pret = new QLabel{ "Modifica pretul: " };

    QLineEdit* edit_mod_den;
    QLineEdit* edit_mod_prod;
    QLineEdit* edit_mod_subs;
    QLineEdit* edit_mod_pret;

    QPushButton* modMed;

    QLabel* del_denumire = new QLabel{ "Denumire medicament sters: " };
    QLabel* del_prod = new QLabel{ "Producator medicament sters: " };
    QLineEdit* edit_del_den;
    QLineEdit* edit_del_prod;

    QPushButton* delMed;

    QGroupBox* sortBox = new QGroupBox(tr("Tip sortare"));

    QRadioButton* sort_denumire = new QRadioButton(QString::fromStdString("Denumire"));
    QRadioButton* sort_producator = new QRadioButton(QString::fromStdString("Producator"));
    QRadioButton* sort_subAndPrice = new QRadioButton(QString::fromStdString("Substanta activa + Pret"));

    QPushButton* sort;

    QGroupBox* filterBox = new QGroupBox(tr("Tip filtrare"));

    QRadioButton* filter_pret = new QRadioButton(QString::fromStdString("Pret"));
    QRadioButton* filter_subs = new QRadioButton(QString::fromStdString("Substanta activa"));

    QPushButton* filter;

    QPushButton* reteta;
    RetetaGUI* RetetaWindow;

    QPushButton* reload_data;

    QPushButton* undo;

    QTableWidget* medicamente;

    QLineEdit* adaugaCosLine;
    QPushButton* adaugaCosButton;
    QLineEdit* stergeCosLine;
    QPushButton* stergeCosButton;
    QLineEdit* genereazaCosLine;
    QPushButton* genereazaCosButton;

    void initializeGUIComponents();

    void connectSignalsSlots();
    void reloadMedicamente(vector<Medicament> medicamente);

public:
    GUI(Service& serv) : serv{ serv } {
        initializeGUIComponents();
        connectSignalsSlots();
        reloadMedicamente(serv.get_all());
        RetetaWindow = new RetetaGUI(serv);
    };
    GUI(const GUI& ot) = delete;

    void guiAddMedicament();
    void guiModMedicament();
    void guiDelMedicament();
    void guifilter_pret();
    void guifilter_subs();
    void guiReteta();
};
