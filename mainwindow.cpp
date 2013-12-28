#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->camerasCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(escolherCamera(int)));
    connect(ui->estiloIlumSlider, SIGNAL(valueChanged(int)), this, SLOT(estiloIlum(int)));
    connect(ui->luminariaBtn, SIGNAL(clicked()), this, SLOT(luzLuminaria()));
    connect(ui->lavaBtn, SIGNAL(clicked()), this, SLOT(luzLavaLamp()));
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::estiloIlum(int ilumId)
{
    // Ids:
    // 0: dia
    // 1: noite
    ui->glDisplayWdgt->definirIluminacao(ilumId);

    if (ilumId == 0)
    {
        ui->luminariaBtn->setChecked(false);
        ui->lavaBtn->setChecked(false);
    }
    else
    {
        ui->luminariaBtn->setChecked(true);
        ui->lavaBtn->setChecked(true);
    }
}

void MainWindow::luzLuminaria()
{
    if (!ui->glDisplayWdgt->light2_enable)
        ui->glDisplayWdgt->light2_enable = true;
    else
        ui->glDisplayWdgt->light2_enable = false;

    ui->glDisplayWdgt->updateGL();
}

void MainWindow::luzLavaLamp()
{
    if (!ui->glDisplayWdgt->light4_enable)
        ui->glDisplayWdgt->light4_enable = true;
    else
        ui->glDisplayWdgt->light4_enable = false;

    ui->glDisplayWdgt->updateGL();
}

