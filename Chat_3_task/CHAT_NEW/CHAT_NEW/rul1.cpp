#include "mainwindow.h"
#include "ui_mainwindow.h"

void Chat1::protocol(int flag){
    switch (flag){
      case 1: {
        yt=0;
        ay=0;
        sz=size_packet->toPlainText();
        delete dlg;

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
            break;
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
        break; }

    case 0: {
        int length=datagram_string.length();

        int marker=0;
        //schetchik=0;
        QString n_packet;

        if (datagram_string[0]=="|" && datagram_string[length-1]=="|" && datagram_string[1]!="|"){
            for (int i=1;i<length-1;i++){
                k_packet+=datagram_string[i];
                qDebug()<<k_packet;

            }
            collect_reading.clear();
            marker=1;
            schetchik++;
        }

        qDebug()<<reading_words.size();
        qDebug()<<k_packet.toInt();
        if (datagram_string[0]=="|" && datagram_string[1]=="|"
                && datagram_string[2]=="|" && length==3 && reading_words.size()==k_packet.toInt())
        {
        qDebug()<<"pri";
        schetchik++;
        collect_reading.clear();
        for (int i=0;i<reading_words.size();i++){
            for (int j = 0; j < reading_words[i].length(); j++) {
                if (reading_words[i][j]=="|") {
                    collect_reading+=reading_words[i].mid(j+1,reading_words[i].length()-j);
                    break;
                }
            }

        }
        reading_words.clear();
        qDebug()<<reading_words;
        schetchik++;
        }
        else {
        if (marker!=1){
           reading_words<<datagram_string;
           QString temp;
           QString kolvo1;
           QString kolvo2;

        for (int i = 0; i < reading_words.size() - 1; i++) {
                for (int j = 0; j < reading_words.size() - i - 1; j++) {
                   kolvo1 =  reading_words[j].mid(0, reading_words.indexOf("|"));
                   kolvo2 =  reading_words[j+1].mid(0, reading_words.indexOf("|"));
                    if ( kolvo1.toInt()> kolvo2.toInt()) {

                        temp = reading_words[j];
                        reading_words[j] = reading_words[j + 1];
                        reading_words[j + 1] = temp;

                    }
                }
            }


        }

        }

        qDebug()<<schetchik;
        if (schetchik==0) {collect_reading=datagram_string; reading_words.clear();}
        qDebug()<<collect_reading;
        break; }
    }

  }
