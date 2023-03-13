#include "petstoremodelview.h"
#include "./ui_petstoremodelview.h"

PetstoreModelView::PetstoreModelView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PetstoreModelView)
{
    ui->setupUi(this);
}

PetstoreModelView::~PetstoreModelView()
{
    delete ui;
}

