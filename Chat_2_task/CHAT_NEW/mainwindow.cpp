#include "mainwindow.h"
#include "ui_mainwindow.h"

Chat1::Chat1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    send= new QTextEdit(this);
    send->setGeometry(10,230,300,40);
    send->show();

    button_send=new QPushButton(this);
    button_send->setGeometry(520,230,100,40);
    button_send->setText("Отправить");
    button_send->show();

    format=new QPushButton(this);
    format->setGeometry(320,230,100,40);
    format->setText("Размер");
    format->show();

    time_send=new QPushButton(this);
    time_send->setGeometry(420,230,100,40);
    time_send->setText("Частота");
    time_send->show();

    take_ip=new QTextEdit(this);
    take_ip->setGeometry(540,40,150,30);
    take_ip->show();

    take_port=new QTextEdit(this);
    take_port->setGeometry(540,120,150,30);
    take_port->show();

    line_ip=new QLabel(this);
    line_ip->setText("Take ip:");
    line_ip->setGeometry(540,10,100,20);
    line_ip->show();

    line_port=new QLabel(this);
    line_port->setText("Take port:");
    line_port->setGeometry(540,90,100,20);
    line_port->show();

    communic=new QTextEdit(this);
    communic->setGeometry(10,10,500,200);
    communic->setReadOnly(true);
    communic->show();

    socket=new QUdpSocket(this);
    socket->bind(QHostAddress("192.168.56.1"),1111);
    qDebug()<<"bilding succes";
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));
    connect(format,SIGNAL(clicked()),this, SLOT(size_dlg()));
    connect(button_send,SIGNAL(clicked()),this, SLOT(send_mes()));
    connect(time_send,SIGNAL(clicked()),this, SLOT(time_dlg()));
}

void Chat1::take_ip_port(){
    if (take_ip->toPlainText()=="" || take_port->toPlainText()==""){
        ip_send="192.168.56.101";
        port_send=9999;
    }
    else{
        ip_send=take_ip->toPlainText();
        port_var=take_port->toPlainText();
        port_send=port_var.toInt();
    }

}

void Chat1::read(){
    QHostAddress sending;
    quint16 port;
    while(socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(),datagram.size(),&sending,&port);

        datagram_string=QString(datagram);
        protocol(0);

        //communic->append("От: "+datagram_string);
        qDebug()<<datagram.data()<<"IP: " + sending.toString()<<"Port: " + QString("%1").arg(port);

    }
    if (collect_reading!="" ){
    communic->append("<b><font color=#008000>От: "+collect_reading+ "</font></p>");
    collect_reading.clear();
    schetchik=0;
    k_packet="";
    }

}

void Chat1::size_dlg(){

    dlg= new QDialog(this);
    dlg->resize(290,150);
    dlg->setWindowTitle("Size");
    dlg->show();

    dlg_ok=new QPushButton(dlg);
    dlg_ok->setGeometry(210,110,80,30);
    dlg_ok->setText("OK");
    dlg_ok->show();

    dlg_text=new QLabel(dlg);
    dlg_text->setText("Введите размер отправляемого пакета:\n\t\t(байт)");
    dlg_text->setGeometry(20,10,270,30);
    dlg_text->show();

    size_packet= new QTextEdit(dlg);
    size_packet->setGeometry(110,70,70,26);
    size_packet->show();
    ay=0;
    connect(dlg_ok, SIGNAL(clicked()), this, SLOT(send_mes()));
}

void Chat1::send_mes(){
    take_ip_port();

    if (send->toPlainText()!=""){
        switch (ay) {
        case 0:
            protocol(1);
            if (yt!=-1)
            socket->writeDatagram(control.toUtf8(),QHostAddress(ip_send), port_send);

            for (int i=0; i<words.size();i++)
            socket->writeDatagram(words[i].toUtf8(),QHostAddress(ip_send), port_send);

            control.clear();
            words.clear();

            if (yt!=-1)
            socket->writeDatagram(last.toUtf8(),QHostAddress(ip_send), port_send);

            break;

        case 1:
            timer_to_send();
            qDebug()<<words.size();
            qDebug()<<yt;
            time_kl=words.size()-1;
            timer= new QTimer;
            connect (timer,SIGNAL(timeout()),this, SLOT(send_split_time()));
            timer->start(1000);
            break;

        case -1:
            socket->writeDatagram(send->toPlainText().toUtf8(),QHostAddress(ip_send), port_send);
            break;
        }

    communic->append("<b><font color=#FF0000>Я: "+ send->toPlainText()+ "</font></b>");
    send->clear();
    ay=-1;
}
}

Chat1::~Chat1()
{
    delete ui;
}

void Chat1::time_dlg(){

    dialog= new QDialog(this);
    dialog->resize(290,150);
    dialog->setWindowTitle("Frequency");
    dialog->show();

    dialog_ok=new QPushButton(dialog);
    dialog_ok->setGeometry(210,110,80,30);
    dialog_ok->setText("OK");
    dialog_ok->show();

    dialog_text=new QLabel(dialog);
    dialog_text->setText("Введите частоту отправляемого пакета:\n\t\t(байт/c)");
    dialog_text->setGeometry(20,10,270,30);
    dialog_text->show();

    time_packet= new QTextEdit(dialog);
    time_packet->setGeometry(110,70,70,26);
    time_packet->show();
    ay=1;
    connect(dialog_ok, SIGNAL(clicked()), this, SLOT(send_mes()));
}
