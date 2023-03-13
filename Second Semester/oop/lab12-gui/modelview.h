#pragma once

#include <QMainWindow>
#include "ui_modelview.h"


namespace Ui {
class ModelView;
}

class ModelView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModelView(QWidget *parent = nullptr);
    ~ModelView();

private:
    Ui::ModelView *ui;
};


