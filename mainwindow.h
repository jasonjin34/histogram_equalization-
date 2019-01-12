#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsTextItem>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <iostream>

//opencv library
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT  //macro for slot connection
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*
     * Histogram equalization
    */
    void on_button_equal_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene, equalized_scene,unequ_color,equ_color;
    QGraphicsView view;

};

#endif // MAINWINDOW_H
