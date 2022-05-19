#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chat1 w;
    w.setGeometry(50,50,530,280);
    w.setWindowTitle("Chat");
    w.show();
    return a.exec();
}
/*
for (int i=1; i<reading_words.size();i++){
k=reading_words[i].length();
for (int j; j<k;j++){

    if (validator.validate(reading_words[i], j) == QValidator::Acceptable){
        n_packet+=reading_words[i][j];
        reading_words[i].remove(0,1);
        k=reading_words[i].length();
    }
}
collect_reading+=reading_words[i];

}
 */
