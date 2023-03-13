#include "modelview.h"
#include "ui_modelview.h"

ModelView::ModelView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModelView)
{
    ui->setupUi(this);
}

ModelView::~ModelView()
{
    delete ui;
}
