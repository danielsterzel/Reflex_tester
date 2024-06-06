#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QVBoxLayout>
#include <QIcon>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QColor>
#include <QRandomGenerator>
#include <QDebug>





QTimer* MainWindow::timer = nullptr;


class ImagePath{
private:
     static QString pressed_button;
    static QString button_;
     static QString background;
public:
    static QString get_pressed_button_path(){
        return pressed_button;
    }
    static QString get_button_path(){
        return button_;
    }
    static QString get_background(){
        return background;
    }



};
QString ImagePath::pressed_button = "C:/Users/gracz/Desktop/pressedbutton.png";
QString ImagePath::button_ = "C:/Users/gracz/Desktop/button.png";
QString ImagePath::background = "C:/Users/gracz/Desktop/whitepng.png";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    redTimer = new QTimer(this);
    greenTimer = new QTimer(this);
    Colortimer = new QTimer(this);
    clicked_on_green = false;



    ui->label->setText("Please press this button:");
    ui->label_2->setText("to begin your reflex testing");
    QPixmap button_imag(ImagePath::get_button_path());
    QIcon buttonIcon(button_imag);
    ui->button->setIcon(buttonIcon);

    connect(Colortimer, &QTimer::timeout, this, &MainWindow::switchColor);





}


MainWindow::~MainWindow()
{
    delete ui;
}


QPushButton* MainWindow::newButton(QWidget *object){
    QPushButton *button = new QPushButton(object);


    //create a layout for parent widget
    QVBoxLayout *layout = new QVBoxLayout(object);

    //Add button to layout
    layout->addWidget(button);



    //set the layout to the parent widget
    object->setLayout(layout);

    button->setFixedSize(250,250);
    QPixmap button_imag(ImagePath::get_button_path());
    QIcon buttonIcon(button_imag);
    button->setIcon(buttonIcon);
    button->setIconSize(button_imag.rect().size());
    layout->setAlignment(Qt::AlignVCenter);
    return button;

}

void MainWindow::openNewWindow(){
    QWidget *newWindow = new QWidget;
    newWindow->setWindowTitle("Tester");
    newWindow->resize(this->width(),this->height());

    //set background
    QPixmap bkgnd(ImagePath::get_background());
    bkgnd = bkgnd.scaled(newWindow->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    newWindow->setPalette(palette);

    QVBoxLayout *mainlayout = new QVBoxLayout(newWindow);

    customWidget = new CustomWidget;
    mainlayout->addWidget(customWidget);


    QPushButton *reflexButton = newButton(newWindow);
    mainlayout->addWidget(reflexButton,0,Qt::AlignHCenter);
    reflexButton->setFixedSize(250,250);


    connect(reflexButton, &QPushButton::clicked, this, [=]() {
        reflex_clicked(reflexButton);
        Check_color(customWidget);
    });
    result = new QLabel(this);
    result->setText("Your reaction time: ");
    result->setAlignment(Qt::AlignHCenter);
    mainlayout->addWidget(result);

    newWindow->show();
    this->close();
    startColorSwitching();

}

void MainWindow::on_button_clicked()

{
    QPixmap pressed_(ImagePath::get_pressed_button_path());
    QIcon button_press(pressed_);
    ui->button->setIcon(button_press);
    openNewWindow();

}
void MainWindow::reflex_clicked(QPushButton*button){
    QPixmap pixmap(ImagePath::get_pressed_button_path());
    QIcon button_press(pixmap);
    button->setIcon(button_press);
    if(!timer){
    timer = new QTimer(this);

    connect(timer,&QTimer::timeout,this,[=](){
        revert_button_time(button);
    });
    timer->start(1000);
    }

}
void MainWindow::revert_button_time(QPushButton *button){
    QPixmap revert_(ImagePath::get_button_path());
    QIcon revert_icon(revert_);
    button->setIcon(revert_icon);
}


void MainWindow::Check_color(CustomWidget* customwidget){
    if(customwidget->get_color() == Qt::green){
        QDateTime click_ = QDateTime::currentDateTime();
        qint64 reactionspeed = time_toReact.msecsTo(click_);
        clicked_on_green = true;
        Colortimer->stop();
        result->setText("Your reaction time is: " + QString::number(reactionspeed) + " ms");
        qDebug() << "Time: "<<reactionspeed;
    }else{
        result->setText("Click when green!!!");
    }
}
void MainWindow::startColorSwitching() {
    int initial_duration = QRandomGenerator::global()->bounded(4, 5);


    Colortimer->start(initial_duration*1000);

}

void MainWindow::togglecolor(){
    if(customWidget->get_color() == Qt::red){
        customWidget->Changecolor(Qt::green);
    }else{
        customWidget->Changecolor(Qt::red);

    }
}
void MainWindow::switchColor(){

    togglecolor();
    time_toReact = QDateTime::currentDateTime();
    if(customWidget->get_color() == Qt::green){
        int duration = QRandomGenerator::global()->bounded(1,3);
        Colortimer->start(duration*1000);
    }else{
    int duration = QRandomGenerator::global()->bounded(2, 12);
    Colortimer->start(duration*1000);
    }
}


