#pragma once
#include <QAbstractTableModel>
#include "Medicament.h"
#include "QtGui/qbrush.h"
#include <vector>
#include <qdebug.h>

class MyTableModel :public QAbstractTableModel {
    std::vector<Medicament> pets;
public:
    MyTableModel(const std::vector<Medicament>& pets) :pets{ pets } {
    }

    int rowCount(const QModelIndex & parent = QModelIndex()) const override{
        return pets.size();
    }
    int columnCount(const QModelIndex & parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
        qDebug() << "row:" << index.row() << " col:" << index.column()<<" role"<<role;
        if (role == Qt::ForegroundRole) {
            Medicament p = pets[index.row()];
            if (p.get_pret() > 0) {
                return QBrush{ Qt::red };
            }
        }
        if (role == Qt::DisplayRole) {

            Medicament p = pets[index.row()];
            if (index.column() == 0) {
                return QString::fromStdString(p.get_denumire());
            }else if (index.column() == 1) {
                return QString::fromStdString(p.get_producator());
            }
            else if (index.column() == 2) {
                return QString::fromStdString(p.get_substanta_activa());
            }
            else if (index.column() == 3) {
                return QString::number(p.get_pret());
            }
        }

        return QVariant{};
    }

    void setPets(const std::vector<Medicament>& pets) {
        this->pets = pets;
        auto topLeft = createIndex(0,0);
        auto bottomR = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomR);
    }
};
