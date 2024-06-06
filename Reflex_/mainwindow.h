#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QDateTime>
#include <QLabel>
class CustomWidget : public QWidget {
    Q_OBJECT
public:
    QColor get_color()const {
        return color;
    }
protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QBrush brush(color);
        painter.setBrush(brush);
        painter.drawRect(rectangle);
    }
public slots:
    void Changecolor(QColor color_){
        color = color_;
        update();

    }
private:
    QRect rectangle = {290,120,200,100};
    QColor color = Qt::red;
};
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void openNewWindow();
    QPushButton* newButton(QWidget *object);


    ~MainWindow();

private slots:
    void on_button_clicked();
    void reflex_clicked(QPushButton* button);
    void revert_button_time(QPushButton *button);
    void Check_color(CustomWidget *customwidget);
    void startColorSwitching();
    void togglecolor();
    void switchColor();


private:
    Ui::MainWindow *ui;
    static QTimer *timer;
    QTimer *redTimer;
    QTimer *greenTimer;
    QTimer *Colortimer;
    CustomWidget* customWidget;
    bool clicked_on_green;
    QDateTime time_toReact;
    QLabel *result;
};

#endif // MAINWINDOW_H
