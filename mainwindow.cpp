#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>

/*To Do*/
/*
 * 1. grayscale histogram equalization   ! 2/3 finished still need to write Mat2QImage functions
 * 2. multiply regions histogram equalization
 * 3. adaptive histogram equalization using CLAHE function in OpenCV
 * 4. 3D color image histogran equalization
 * 5. Backprojection OpenCV (maybe???)2
*/



QImage Mat2QImage(cv::Mat& src){
    cv::Mat temp;
    cv::cvtColor(src,temp,CV_BGR2RGB);  //might need it in the future
    temp = src;
    QImage dest(temp.data,temp.cols,temp.rows,static_cast<int>(temp.step),QImage::Format_RGB888);
    dest.bits(); //enforce deep copy of QImage
    return dest;
}

QImage Mat2QImageGrayscale(cv::Mat& src){
    cv::Mat temp;
    cv::cvtColor(src,temp,CV_GRAY2RGB);  //might need it in the future
    temp = src;
    QImage dest(temp.data,temp.cols,temp.rows,static_cast<int>(temp.step),QImage::Format_Grayscale8);
    dest.bits(); //enforce deep copy of QImage
    return dest;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->equalizedView->setScene(&equalized_scene);
    ui->equalizedColor->setScene(&unequ_color);
    ui->unequalizedColor->setScene(&equ_color);

    /*Equalization button slot connection */
    connect(ui->button_equal,SIGNAL(clicked()),this,SLOT(on_button_equal_clicked()));

    //set path
    std::string imageName("C:/HIWI/test-hiwi/unequalized.jpg");
    cv::Mat image;
    image = cv::imread(imageName,-1); //read the image
    //load on check
    if(image.empty()){
        qDebug() <<"the pic can not load";
    }
    else qDebug() << "load success";
    /*
     * function convert Opencv Mat image to a Qt QImage
     * use cvtColor and setPixmap to to QGraphicDisplay
    */
    scene.addPixmap(QPixmap::fromImage(Mat2QImage(image)));

 /************************************************************************************************/
    /* Histogram with colored image
    */
    cv::Mat image_color = cv::imread(std::string("C:/HIWI/images/transmission/B.png"),-1); //read the image
    //load on check
    if(image_color.empty()){
        qDebug() <<"the pic can not load";
    }
    else qDebug() << "load success";
    //convert to QImage and display
    unequ_color.addPixmap(QPixmap::fromImage(Mat2QImage(image_color)));

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_equal_clicked()
{
    cv::Mat image = cv::imread(std::string("C:/HIWI/test-hiwi/unequalized.jpg"),-1); //read the image
    /*
     * histogram equalization
     */
    //convert to grayscale
    cv::Mat gray_image,equalized_image;
    cv::cvtColor(image,gray_image,cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray_image,equalized_image);

    equalized_scene.addPixmap(QPixmap::fromImage(Mat2QImageGrayscale(equalized_image)));

    /*
     * colored image equalization    !!!!!!!!!!! not finished
    */
    //historgram equalization for colored image
    cv::Mat image_color = cv::imread(std::string("C:/HIWI/images/transmission/B.png"),-1); //read the image
    cv::Mat gray_image_color,equalized_image_color_gray,equalized_image_color;
    cv::cvtColor(image_color,gray_image_color,cv::COLOR_RGB2GRAY);
    cv::equalizeHist(gray_image_color,equalized_image_color_gray);
    cv::cvtColor(equalized_image_color_gray,equalized_image_color,cv::COLOR_GRAY2BGR);
    //cv::imshow("equalized color image",equalized_image_color);
    equ_color.addPixmap(QPixmap::fromImage(Mat2QImage(equalized_image_color)));

}
