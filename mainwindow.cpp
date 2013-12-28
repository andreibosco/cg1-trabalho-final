#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(luzLuminaria()));
    connect(ui->camerasCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(escolherCamera(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::luzLuminaria()
{
    qDebug() << "status da luz: " << ui->glDisplayWdgt->light2_enable;

    if (!ui->glDisplayWdgt->light2_enable)
        ui->glDisplayWdgt->light2_enable = true;
    else
        ui->glDisplayWdgt->light2_enable = false;

    ui->glDisplayWdgt->updateGL();
}

void MainWindow::escolherCamera(int cameraId)
{
    // Ids:
    // 0: mesa
    // 1: mesa 2
    // 2: geral
    // 3: topo
    ui->glDisplayWdgt->cameraInicial = 0;
    ui->glDisplayWdgt->cameraPosicao(cameraId);
}
