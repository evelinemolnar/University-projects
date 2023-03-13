#include "guimodele.h"
#include "Medicament.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include "MyListModel.h"
#include "MyTableModel.h"
void PetStoreGUIModele::initGUICmps() {
    QHBoxLayout* ly = new QHBoxLayout;
    setLayout(ly);

    //adaug lista si sub doua butoane de sort
    QWidget* widDreapta = new QWidget;
    QVBoxLayout* vl = new QVBoxLayout;
    widDreapta->setLayout(vl);

    vl->addWidget(lblCate);

    lstV = new QListView;
    lstV->setUniformItemSizes(true);
    vl->addWidget(lstV);


    QWidget* widBtnDreapta = new QWidget;
    QHBoxLayout* lyBtnsDr = new QHBoxLayout;
    widBtnDreapta->setLayout(lyBtnsDr);
    btnSortByPrice = new QPushButton("Sort by name");
    lyBtnsDr->addWidget(btnSortByPrice);

    btnSortByType = new QPushButton("Sort by brand");
    lyBtnsDr->addWidget(btnSortByType);
    vl->addWidget(widBtnDreapta);
    ly->addWidget(widDreapta);

    QWidget* formDel = new QWidget;

    QFormLayout* lyFormDel = new QFormLayout;
    formDel->setLayout(lyFormDel);

    delMed = new QPushButton("Sterge medicament");
    lyFormDel->addWidget(delMed);

    vl->addWidget(formDel);

    undo = new QPushButton("Undo");
    vl->addWidget(undo);

    reload_data = new QPushButton("Reload data");
    vl->addWidget(reload_data);

    QVBoxLayout* lyRadioBox2 = new QVBoxLayout;
    this->filterBox->setLayout(lyRadioBox2);

    lyRadioBox2->addWidget(filter_pret);
    lyRadioBox2->addWidget(filter_subs);

    filter = new QPushButton("FIltreaza medicamente");
    lyRadioBox2->addWidget(filter);

    vl->addWidget(filterBox);

    QWidget* widDreapta2 = new QWidget;
    QVBoxLayout *lyDreapta = new QVBoxLayout;
    widDreapta2->setLayout(lyDreapta);

    //fac un form pentru detalii
    QWidget* widDetalii = new QWidget;
    QFormLayout* formLDetalii = new QFormLayout;
    widDetalii->setLayout(formLDetalii);
    txtSpecies = new QLineEdit;
    formLDetalii->addRow(new QLabel("Denumire:"), txtSpecies);
    txtType = new QLineEdit;
    formLDetalii->addRow(new QLabel("Producator:"), txtType);
    txtSubst = new QLineEdit;
    formLDetalii->addRow(new QLabel("Subst:"), txtSubst);
    txtPrice = new QLineEdit;
    formLDetalii->addRow(new QLabel("Pret:"), txtPrice);

    btnAdd = new QPushButton("Add med");
    formLDetalii->addWidget(btnAdd);
    lyDreapta->addWidget(widDetalii);



    btnGenereaza10000 = new QPushButton("Genereaza 10000");
    lyDreapta->addWidget(btnGenereaza10000);

    ly->addWidget(widDreapta2);

    ly->addWidget(tblV);


}


void PetStoreGUIModele::connectSignalsSlots() {
    //cand se emite semnalul clicked de pe buton reincarc lista
    QObject::connect(btnSortByPrice, &QPushButton::clicked, [&]() {
        reloadList(ctr.sort_by_denumire());
    });
    //cand se emite semnalul clicked de pe buton reincarc lista
    QObject::connect(btnSortByType, &QPushButton::clicked, [&]() {
        reloadList(ctr.sort_by_producator());
    });

    QObject::connect(btnAdd, &QPushButton::clicked, this, &PetStoreGUIModele::addNewPet);

    QObject::connect(delMed, &QPushButton::clicked, this, &PetStoreGUIModele::guiDelMedicament);

    QObject::connect(filter, &QPushButton::clicked, [&]() {
        //string filtru_subs = this->editFilterCriteria->text().toStdString();
        if (this->filter_pret->isChecked()) {
            try {
                guifilter_pret();
            }
            catch (RepoException& re) {
                QMessageBox::information(this, "Info", QString::fromStdString(re.get_errorMsg()));
            }
        }
        else if (this->filter_subs->isChecked()) {

            try {
                guifilter_subs();
            }
            catch (RepoException& re) {
                QMessageBox::information(this, "Info", QString::fromStdString(re.get_errorMsg()));
            }
        }
        });
    QObject::connect(reload_data, &QPushButton::clicked, [&]() {
        this->reloadList(ctr.get_all());
        });

    QObject::connect(btnGenereaza10000, &QPushButton::clicked, [this]() {
        try {
            this->ctr.addRandom(10);
        }
        catch (const RepoException& re) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errorMsg()));
        }
        });
    QObject::connect(undo, &QPushButton::clicked, [&]() {
        try {
            ctr.undo();
        }
        catch (RepoException& re) {
            QMessageBox::information(this, "Info", QString::fromStdString(re.get_errorMsg()));
        }
        this->reloadList(ctr.get_all());
        });
    //selectia in tabel
    QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        if (tblV->selectionModel()->selectedIndexes().isEmpty()) {
            txtSpecies->setText("");
            txtType->setText("");
            txtSubst->setText("");
            txtPrice->setText("");
            return;
        }
        int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
        auto cel0Index = tblV->model()->index(selRow, 0);
        auto cel0Value= tblV->model()->data(cel0Index, Qt::DisplayRole).toString();
        txtSpecies->setText(cel0Value);
        auto cel1Index = tblV->model()->index(selRow, 1);
        auto cel1Value = tblV->model()->data(cel1Index, Qt::DisplayRole).toString();
        txtType->setText(cel1Value);
        auto cel2Index = tblV->model()->index(selRow, 2);
        auto cel2Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
        txtSubst->setText(cel2Value);
        auto cel3Index = tblV->model()->index(selRow, 3);
        auto cel3Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
        txtPrice->setText(cel2Value);
    });
}

void PetStoreGUIModele::addNewPet() {
    try {
        //preluare detalii din QLineEdit-uri
        string denumire = txtSpecies->text().toStdString();
        string producator = txtType->text().toStdString();
        string subs = txtSubst->text().toStdString();
        double pret = txtPrice->text().toDouble();

        //optional - golim QLineEdit-urile dupa apasarea butonului
        txtSpecies->clear();
        txtType->clear();
        txtSubst->clear();
        txtPrice->clear();

        this->ctr.adauga(denumire, producator, subs, pret);
        this->reloadList(this->ctr.get_all());


        QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes."));

    }
    catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errorMsg()));
    }
    catch (ValidationException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_error()));
    }
}

void PetStoreGUIModele::guiDelMedicament() {
    QWidget* modificaWindow = new QWidget;

    QWidget* formWidget = new QWidget;
    QFormLayout* formLayout = new QFormLayout;

    QLabel* denLabel = new QLabel("Denumire: ");
    QLineEdit* denLine = new QLineEdit;
    formLayout->addRow(denLabel, denLine);

    QLabel* producatorLabel = new QLabel("Producator: ");
    QLineEdit* producatorLine = new QLineEdit;
    formLayout->addRow(producatorLabel, producatorLine);

    formWidget->setLayout(formLayout);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(formWidget);

    QPushButton* sterge = new QPushButton("&Sterge");
    QObject::connect(sterge, &QPushButton::clicked, [=]() {
        try {
            this->ctr.sterge(denLine->text().toStdString(), producatorLine->text().toStdString());
            this->reloadList(this->ctr.get_all());
            modificaWindow->close();
        }
        catch (const ValidationException& ve) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Eroare validare");
            msgBox.setText(QString::fromUtf8(ve.get_error()));
            msgBox.exec();
            modificaWindow->close();
        }
        catch (const RepoException& re) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Eroare repo");
            msgBox.setText(QString::fromUtf8(re.get_errorMsg()));
            msgBox.exec();
            modificaWindow->close();
        }
        });
    vLayout->addWidget(sterge);

    modificaWindow->setLayout(vLayout);
    modificaWindow->show();


}

void PetStoreGUIModele::guifilter_pret() {
    QWidget* pretWindow = new QWidget;

    QWidget* formWidget = new QWidget;
    QFormLayout* formLayout = new QFormLayout;

    QLabel* pretLabel = new QLabel("Pret: ");
    QLineEdit* pretLine = new QLineEdit;
    formLayout->addRow(pretLabel, pretLine);

    formWidget->setLayout(formLayout);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(formWidget);

    QPushButton* filt_pret = new QPushButton("&Filtreaza");
    QObject::connect(filt_pret, &QPushButton::clicked, [=]() {
        try {
            this->ctr.filter_pret(pretLine->text().toDouble());
            this->reloadList(this->ctr.filter_pret(pretLine->text().toDouble()));
            pretWindow->close();
        }
        catch (const ValidationException& ve) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Eroare validare");
            msgBox.setText(QString::fromUtf8(ve.get_error()));
            msgBox.exec();
            pretWindow->close();
        }
        catch (const RepoException& re) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Eroare repo");
            msgBox.setText(QString::fromUtf8(re.get_errorMsg()));
            msgBox.exec();
            pretWindow->close();
        }
        });
    vLayout->addWidget(filt_pret);

    pretWindow->setLayout(vLayout);
    pretWindow->show();


}

void PetStoreGUIModele::guifilter_subs() {
    QWidget* pretWindow = new QWidget;

    QWidget* formWidget = new QWidget;
    QFormLayout* formLayout = new QFormLayout;

    QLabel* pretLabel = new QLabel("Substanta activa: ");
    QLineEdit* pretLine = new QLineEdit;
    formLayout->addRow(pretLabel, pretLine);

    formWidget->setLayout(formLayout);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(formWidget);

    QPushButton* filt_pret = new QPushButton("&Filtreaza");
    QObject::connect(filt_pret, &QPushButton::clicked, [=]() {
        try {
            this->ctr.filter_sub(pretLine->text().toStdString());
            this->reloadList(this->ctr.filter_sub(pretLine->text().toStdString()));
            pretWindow->close();
        }
        catch (const ValidationException& ve) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Eroare validare");
            msgBox.setText(QString::fromUtf8(ve.get_error()));
            msgBox.exec();
            pretWindow->close();
        }
        catch (const RepoException& re) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Eroare repo");
            msgBox.setText(QString::fromUtf8(re.get_errorMsg()));
            msgBox.exec();
            pretWindow->close();
        }
        });
    vLayout->addWidget(filt_pret);

    pretWindow->setLayout(vLayout);
    pretWindow->show();


}


void PetStoreGUIModele::reloadList(std::vector<Medicament> pets) {
    lblCate->setText(QString{ "Cate:" }+QString::number(pets.size()));
    model->setPets(pets);



}
