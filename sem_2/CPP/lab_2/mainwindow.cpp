#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtAlgorithms>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::do_Update);
    timer->start(10000);

}

MainWindow::~MainWindow()
{
    this->getAverege_and_Median();
    delete ui;
}

void MainWindow::getAverege_and_Median() {
        for (int i = 0 ; i < this->data_vector.size(); ++i) {
            qDebug() << "Name: " << this->data_vector[i].Name;
            double sum = 0;
            for (int j = 0; j < this->data_vector[i].Value.size(); ++j) {
                sum += this->data_vector[i].Value[j];
            }

            qDebug() << "Nominal: " << this->data_vector[i].Nominal;
            qDebug() << "Avarage Value: " << sum/this->data_vector[i].Value.size();
            QVector<double> tmp = data_vector[i].Value;
            std::sort(tmp.begin(), tmp.end());
            qDebug() << "Median Value: " << (tmp.size() % 2 == 0 ? (tmp[tmp.size()/2 - 1] + tmp[tmp.size()/2])/2 : tmp[tmp.size()/2]) << '\n';

        }
}


void MainWindow::do_Update() {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::downloadFinished);

    manager->get(QNetworkRequest(QUrl("https://www.cbr-xml-daily.ru/daily_json.js")));
}

void MainWindow::downloadFinished(QNetworkReply *reply) {
    if(reply->error()) {
        return;
    }
    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    QJsonObject info = json.object();
    QJsonObject rate = info["Valute"].toObject();
    QVector<Exchange_Rate> all_rates;
    int count =  0;


    for(auto& valute: rate.keys()) {
        QJsonObject data = rate[valute].toObject();
        Exchange_Rate *cur_rate = new Exchange_Rate;
        all_rates.append(*cur_rate);
        for(auto& field: data.keys()) {
            if(field == "ID") {
                all_rates[count].ID = data[field].toString();
            }
            if (field == "NumCode") {
                all_rates[count].NumCode = data[field].toString();
            }
            if (field == "CharCode") {
                all_rates[count].CharCode = data[field].toString();
            }
            if (field == "Nominal") {
                all_rates[count].Nominal = data[field].toDouble();
            }
            if (field == "Name") {
                all_rates[count].Name = data[field].toString();
            }
            if (field == "Value") {
                all_rates[count].Value.append(data[field].toDouble());
            }
            if (field == "Previous") {
                all_rates[count].Previous = data[field].toDouble();
            }
        }

        qDebug() << "Name: " << all_rates[count].Name;
        qDebug() << "Nominal: " << all_rates[count].Nominal;
        qDebug() << "Value: " << all_rates[count].Value[0];
        qDebug() << '\n';

        count++;
    }
    if (!flag) {
        this->data_vector = all_rates;
    } else {
        for(int i = 0; i < this->data_vector.size(); ++i) {
            data_vector[i].Value.append(all_rates[i].Value[0]);
        }
    }


}

