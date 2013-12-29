#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

public slots:
    void escolherCamera(int cameraId);
    void estiloIlum(int ilumId);
    void luz(int luzId);
    void textoNotebook(QString textoInput);
};

#endif // MAINWINDOW_H
