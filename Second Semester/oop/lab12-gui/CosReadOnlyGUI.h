#pragma once
#include "Observer.h"
#include "Medicament.h"
#include "Reteta.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <cmath>

#define RECTANGLE_MAX_DIM 256


class Desenator : public QWidget, public Observer
{
private:
    Reteta& srv;
    void connectSignals() {
        srv.addObserver(this);
    }
public:
    Desenator(Reteta& srv) : srv{ srv } { connectSignals(); }
    void paintEvent(QPaintEvent* ev) override {
        QPainter p{ this };
        int i = 50;
        for (const auto& el : srv.getReteta()) {
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

