#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // criando objeto de mapeando para botões de luzes
    QSignalMapper* signalLuzes = new QSignalMapper (this);

    connect(ui->camerasCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(escolherCamera(int)));
    connect(ui->estiloIlumSlider, SIGNAL(valueChanged(int)), this, SLOT(estiloIlum(int)));
    connect(ui->luminariaBtn, SIGNAL(clicked()), signalLuzes, SLOT(map()));
    connect(ui->lavaBtn, SIGNAL(clicked()), signalLuzes, SLOT(map()));
    connect(ui->notebookBtn, SIGNAL(clicked()), signalLuzes, SLOT(map()));
    connect(ui->notebookText, SIGNAL(textChanged(QString)), this, SLOT(textoNotebook(QString)));

    // mapeando sinais dos botões das luzes
    signalLuzes->setMapping(ui->luminariaBtn, 0);
    signalLuzes->setMapping(ui->lavaBtn, 1);
    signalLuzes->setMapping(ui->notebookBtn, 2);

    // conectando objeto de mapeamento à função de controle das luzes
    connect(signalLuzes, SIGNAL(mapped(int)), this, SLOT(luz(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::escolherCamera(int cameraId)
{
    // Ids:
    // 0: geral
    // 1: mesa
    // 2: mesa 2
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
        ui->notebookBtn->setChecked(false);
    }
    else
    {
        ui->luminariaBtn->setChecked(true);
        ui->lavaBtn->setChecked(true);
        ui->notebookBtn->setChecked(true);
    }
}
void MainWindow::luz(int luzId)
{
    // Ids:
    // 0: luminaria
    // 1: lava
    // 2: notebook

    if (luzId == 0)
    {
        if (!ui->glDisplayWdgt->light2_enable)
            ui->glDisplayWdgt->light2_enable = true;
        else
            ui->glDisplayWdgt->light2_enable = false;
    }
    else if (luzId == 1)
    {
        if (!ui->glDisplayWdgt->light4_enable)
            ui->glDisplayWdgt->light4_enable = true;
        else
            ui->glDisplayWdgt->light4_enable = false;
    }
    else
    {
        if (!ui->glDisplayWdgt->light5_enable)
            ui->glDisplayWdgt->light5_enable = true;
        else
            ui->glDisplayWdgt->light5_enable = false;

    }

    ui->glDisplayWdgt->updateGL();
}

void MainWindow::textoNotebook(QString textoInput)
{
    ui->glDisplayWdgt->texto = textoInput;
    ui->glDisplayWdgt->updateGL();
}
