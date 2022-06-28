#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QUdpSocket>
#include <QDialog>
#include <QLabel>
#include <QTimer>
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
    QPushButton* time_send;
    QTextEdit* communic;
    QDialog* dlg;
    QDialog* dialog;
    QPushButton* dialog_ok;
    QLabel* dialog_text;
    QPushButton* dlg_ok;
    QLabel* dlg_text;
    QTextEdit* size_packet;
    QTextEdit* time_packet;
    QString sz;
    QString control;
    QLabel* line_port;
    QLabel* line_ip;
    QTextEdit* take_ip;
    QTextEdit* take_port;
    QStringList words;
    QString datagram_string;
    QStringList reading_words;
    QString collect_reading;
    QString last="|||";
    QString k_packet;
    QTimer* timer;
    QString ip_send;
    QString port_var;

    int port_send;
    int time_kl=0;
    int time_message_kl=0;
    int a=0;
    int ay=-1;
    int yt;
    int schetchik=0;

public slots:
    void read();
    void take_ip_port();
    void dostavka_otch();

private slots:
    void send_mes();
    void size_dlg();
    void time_dlg();
    void timer_to_send();
    void protocol(int);
    void send_split_time();

private:
    Ui::MainWindow *ui;
    QUdpSocket* socket;



};
#endif // MAINWINDOW_H
