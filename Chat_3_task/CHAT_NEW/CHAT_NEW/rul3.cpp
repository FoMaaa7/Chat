#include "mainwindow.h"
#include "ui_mainwindow.h"
//ⱽ

void Chat1::dostavka_otch(){
      QString coll;
      for (int i=2; i<collect_reading.length()-2;i++)
          coll+=collect_reading[i];

      QString packet_dostavka="Я: "+coll;

      QString after_check_dost="";
      QStringList all_from_commun=communic->toPlainText().split("\n");

      for (int i=0;i<=all_from_commun.length()-1;i++){
           if (all_from_commun[i]==packet_dostavka) {
               after_check_dost+="<div><b><font color=#FF0000>"+all_from_commun[i]+"   ⱽ</font></b></div>";
           }
           else {

               if (all_from_commun[i][0]=="Я"){
                   after_check_dost+="<div><b><font color=#FF0000>"+all_from_commun[i]+"</font></b></div>";
               }

               else{
                  after_check_dost+="<div><b><font color=#008000>"+all_from_commun[i]+"</font></b></div>";
               }
           }
      }

      communic->clear();
      communic->append(after_check_dost);
}

