#include "mainwindow.h"
#include "ui_mainwindow.h"

void Chat1::timer_to_send(){
    yt=0;
    ay=1;
    time_message_kl=-1;
    sz=time_packet->toPlainText();
    delete dialog;

    QString message=send->toPlainText();
    QByteArray d = message.toUtf8();

    int k_bite=sz.toInt()-1;
    if(k_bite==2) k_bite++;
    try {

    if (k_bite>1) qDebug()<<"success";
    else throw k_bite;

    } catch (int k_bite) {

        words<<message;
        control="|"+QString::number(words.size())+"|";
        yt=-1;
        return;
    }

    int full_mes=d.size();
    int last_pack=full_mes % k_bite;

    int k=0;
    if (last_pack!=0) k=(full_mes / k_bite)+1;
    else k=full_mes / k_bite;
    last_pack=(full_mes+k) % k_bite;
    if (last_pack!=0) k=(full_mes+k)/k_bite+1;
    else k=(full_mes+k)/k_bite;

    QString str;
    int a=0;
    int b=message.length();

    for (int i=0; i<b;i++){
        str=message[i];
        a+=str.toUtf8().size();
        if (a>=k_bite) {message.insert(i,"|"); a=0;b=message.length();}

    }
    qDebug()<<message;

    words = message.split("|");

    for (int i=0; i<words.size();i++) words[i]=QString::number(i)+"|"+words[i];

    qDebug()<<"1:"<<words;
    control="|"+QString::number(words.size())+"|";
    return;
}

void Chat1::send_split_time(){
    if(time_message_kl<time_kl+1){
    if ((yt!=-1) && (time_message_kl==-1))
    {
       socket->writeDatagram(control.toUtf8(),QHostAddress(ip_send), port_send);
    }

    if (time_message_kl>=0){
       socket->writeDatagram(words[time_message_kl].toUtf8(),QHostAddress(ip_send), port_send);
       qDebug()<<words[time_message_kl];
    }
    time_message_kl++;
    }
    else {
        if (yt!=-1) {
        socket->writeDatagram(last.toUtf8(),QHostAddress(ip_send), port_send);
        }
        timer->stop();
    }

}
