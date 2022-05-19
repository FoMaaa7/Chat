#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QUdpSocket>
#include <QDialog>
#include <QLabel>
#include <QRegExpValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Chat1 : public QMainWindow
{
    Q_OBJECT

public:
    Chat1(QWidget *parent = nullptr);
    ~Chat1();
    QTextEdit* send;
    QPushButton* button_send;
    QPushButton* format;
    QTextEdit* communic;
    QDialog* dlg;
    QPushButton* dlg_ok;
    QLabel* dlg_text;
    QTextEdit* size_packet;
    QString sz;
    QString control;
    QStringList words;
    QString datagram_string;
    QStringList reading_words;
    QString collect_reading;
    QString last="|||";
    QString k_packet;
    int a=0;
    int schetchik;

public slots:
    void read();

private slots:
    void send_mes();
    void size_dlg();
    void protocol(int);
    void sending();

private:
    Ui::MainWindow *ui;
    QUdpSocket* socket;
    int yt=0;


};
#endif // MAINWINDOW_H
