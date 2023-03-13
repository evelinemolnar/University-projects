#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtablewidget.h>
#include "QtWidgets/qgroupbox.h"
#include "QtWidgets/qradiobutton.h"
#include "Service.h"
#include "Medicament.h"
#include <vector>
#include <MyTableModel.h>

class PetStoreGUIModele : public QWidget {
private:
    Service& ctr;
    MyTableModel* model;
    QLabel* lblCate = new QLabel{ "Cate:" };
    QListView* lstV;

    QTableView* tblV = new QTableView;

    QPushButton* btnSortByPrice;
    QPushButton* btnSortByType;

    QLineEdit* txtSpecies;
    QLineEdit* txtType;
    QLineEdit* txtSubst;
    QLineEdit* txtPrice;
    QPushButton* btnAdd;

    QLabel* del_denumire = new QLabel{ "Denumire medicament sters: " };
    QLabel* del_prod = new QLabel{ "Producator medicament sters: " };
    QLineEdit* edit_del_den;
    QLineEdit* edit_del_prod;

    QPushButton* delMed;

    QPushButton* undo;

    QPushButton* reload_data;

    QTableWidget* medicamente;

    QGroupBox* filterBox = new QGroupBox(tr("Tip filtrare"));

    QRadioButton* filter_pret = new QRadioButton(QString::fromStdString("Pret"));
    QRadioButton* filter_subs = new QRadioButton(QString::fromStdString("Substanta activa"));

    QPushButton* filter;

    QPushButton* btnGenereaza10000;

    void initGUICmps();
    void connectSignalsSlots();
    void reloadList(std::vector<Medicament> pets);
    void addNewPet();
public:
    PetStoreGUIModele(Service& ctr) :ctr{ ctr } {
        initGUICmps();
        model = new MyTableModel{ ctr.get_all() };
        lstV->setModel(model);
        tblV->setModel(model);
        connectSignalsSlots();
    }
    void guiDelMedicament();
    void guifilter_pret();
    void guifilter_subs();

};
