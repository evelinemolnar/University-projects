#pragma once
#include<QAbstractListModel>
#include "Medicament.h"
#include "QtGui/qcolor.h"
#include <vector>
#include <qdebug.h>
class MyListModel :public QAbstractListModel {
    std::vector<Medicament> pets;
public:
    MyListModel(const std::vector<Medicament>& pets) :pets{ pets } {
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return pets.size();
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole) {
            qDebug() << "get row:" << index.row();
            auto sp = pets[index.row()].get_denumire();
            return QString::fromStdString(sp);
        }
        if (role == Qt::UserRole) {
            auto tp = pets[index.row()].get_producator();
            return QString::fromStdString(tp);
        }

        return QVariant{};
    }
};
