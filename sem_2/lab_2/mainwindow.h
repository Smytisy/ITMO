#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextStream>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QTimer>
#include <QDebug>
#include <QtAlgorithms>

class Exchange_Rate {
public:
    QString Char_Name;
    QString ID;
    QString NumCode;
    QString CharCode;
    double Nominal;
    QString Name;
    QVector<double> Value;
    double Previous;
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<Exchange_Rate> data_vector;
    bool flag = false;
    void getAverege_and_Median();

public slots:
    void downloadFinished(QNetworkReply *reply);
    void do_Update();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
