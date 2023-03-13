#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PetstoreModelView; }
QT_END_NAMESPACE

class PetstoreModelView : public QMainWindow
{
    Q_OBJECT

public:
    PetstoreModelView(QWidget *parent = nullptr);
    ~PetstoreModelView();

private:
    Ui::PetstoreModelView *ui;
};
