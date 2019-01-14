#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>

/*To Do Working plan -- bis Marz */
/*
 * 1. grayscale histogram equalization   ! 2/3 finished still need to write Mat2QImage functions
 * 3. multiply regions histogram equalization
 * 2. adaptive histogram equalization using CLAHE function in OpenCV
 * 4. 3D color image histogran equalization
 * *extra QT Data visuliazation QT Charts
*/

/*
 * color image histogram qualization functions
*/
cv::Mat hsv_equalized(cv::Mat& src){   // the color format is BGR
    std::vector<cv::Mat> hsvChannel(3), hsvchannel_temp(3),output_hsv;
    cv::Mat temp_src,output,output_converted;
    std::vector<cv::Mat> channel; // spearate channel for merage functions

    //use temp the get the color transfer image
    cv::cvtColor(src,temp_src,CV_BGR2HSV);
    cv::split(temp_src,hsvChannel);
    cv::split(temp_src,hsvchannel_temp);
    cv::equalizeHist(hsvChannel[2],hsvchannel_temp[2]);

    //push the converted and original channels and merge into the original image
    output_hsv.push_back(hsvChannel[0]);
    output_hsv.push_back(hsvChannel[1]);
    output_hsv.push_back(hsvchannel_temp[2]);

    cv::merge(output_hsv,output);
    cv::cvtColor(output,output_converted,CV_HSV2BGR);
    //cv::imshow("histogram equalized color image -- BGR format",output_converted);  testing result

    return output_converted;
}


QImage Mat2QImage(cv::Mat& src){
    cv::Mat temp;
    temp = src;
    cv::cvtColor(src,temp,CV_BGR2RGB);  //might need it in the future
    QImage dest(temp.data,temp.cols,temp.rows,static_cast<int>(temp.step),QImage::Format_RGB888);
    dest.bits(); //enforce deep copy of QImage
    return dest;
}

QImage Mat2QImageGrayscale(cv::Mat& src){
    cv::Mat temp;
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
    cv::imwrite(std::string("C:/HIWI/test-hiwi/equalized.jpg"),equalized_image);

    equalized_scene.addPixmap(QPixmap::fromImage(Mat2QImageGrayscale(equalized_image)));

    /*
     * colored image equalization
    */
    //historgram equalization for colored image
    cv::Mat image_color = cv::imread(std::string("C:/HIWI/images/transmission/B.png"),-1); //read the image

    //HSV color image histogram equalization
    cv::Mat equalized_image_color = hsv_equalized(image_color);
    cv::imwrite("C:/HIWI/images/transmission/equalized_B_final.jpg",equalized_image_color);
    equ_color.addPixmap(QPixmap::fromImage(Mat2QImage(equalized_image_color)));
}
