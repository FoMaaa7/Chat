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
    button_send->setGeometry(420,230,100,40);
    button_send->setText("Отправить");
    button_send->show();

    format=new QPushButton(this);
    format->setGeometry(320,230,100,40);
    format->setText("Формат");
    format->show();

    communic=new QTextEdit(this);
    communic->setGeometry(10,10,500,200);
    communic->setReadOnly(true);
    communic->show();

    socket=new QUdpSocket(this);
    socket->bind(QHostAddress("192.168.56.1"),1111);
    qDebug()<<"bilding succes";

    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));
    connect(format,SIGNAL(clicked()),this, SLOT(size_dlg()));
    connect(button_send,SIGNAL(clicked()),this, SLOT(sending()));

    //ui->setupUi(this);
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
    communic->append("От: "+collect_reading);
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
    connect(dlg_ok, SIGNAL(clicked()), this, SLOT(send_mes()));
}

void Chat1::send_mes(){
    if (send->toPlainText()!=""){
    yt=0;
    sz=size_packet->toPlainText();
    delete dlg;

    protocol(1);

    if (yt!=-1)
    socket->writeDatagram(control.toUtf8(),QHostAddress("192.168.56.101"), 9999);

    for (int i=0; i<words.size();i++)
    socket->writeDatagram(words[i].toUtf8(),QHostAddress("192.168.56.101"), 9999);

    if (yt!=-1)
    socket->writeDatagram(last.toUtf8(),QHostAddress("192.168.56.101"), 9999);

    communic->append("Я: "+ send->toPlainText());

    control.clear();
    words.clear();
    send->clear();
}
}

Chat1::~Chat1()
{
    delete ui;
}

void Chat1::sending(){
    if(send->toPlainText()!=""){
        socket->writeDatagram(send->toPlainText().toUtf8(),QHostAddress("192.168.56.101"), 9999);
        communic->append("Я: "+ send->toPlainText());
        send->clear();}
}
