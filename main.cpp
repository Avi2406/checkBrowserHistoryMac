#include "mainwindow.h"
#include <QApplication>

#include <QProcess>
#include <QDebug>
#include <qfile.h>
#include <qtextstream.h>
#include <qmessagebox.h>
int main(int argc, char **argv)
{
 QApplication a(argc, argv);
//MainWindow w;

//QString aScript =
// "tell application quot;System Eventsquot;"
// " activate\n"
// " display dialog quot;Hello worldquot;"
// "end tell\n";

while(1)
{
QString aScript =  "set myFile to open for access \"/Users/verificient/Documents/check3.txt\" with write permission\n"
        "set titleString to \"\"\n"
"tell application \"Google Chrome\"\n"

        "set window_list to every window # get the windows\n"
        "repeat with the_window in window_list\n"
            "set tab_list to every tab in the_window\n"
            "repeat with the_tab in tab_list\n"
                "set the_title to the title of the_tab\n"
                "set titleString to titleString & the_title & return \n"
            "end repeat\n"

        "end repeat\n"
        "write titleString to myFile\n"

"end tell\n"
"close access myFile\n";


QString osascript = "/usr/bin/osascript";
QStringList processArguments;
 processArguments << "-l" << "AppleScript";

QProcess p;

 p.start(osascript, processArguments);

p.write(aScript.toUtf8());
 p.closeWriteChannel();


 //p.start();
 p.waitForReadyRead(200000);
 //p.waitForReadyRead(–1);
 //p.readyRead();
// QByteArray result = p.readAll();
// QString resultAsString =result; // if appropriate
// qDebug() << "the result of the script is" << resultAsString;

QFile tabHistory("/Users/verificient/Documents/check3.txt");
//qDebug() << "Checking for restricted activities";
if(tabHistory.open(QIODevice::ReadWrite))
{
   // qDebug() << "Inside file";
    QTextStream title(&tabHistory);
    while(!title.atEnd())
    {
        QString s = title.readLine();
       // qDebug() << s;
        if(s.contains("Google Hangouts"))
        {
           // qDebug() << "Found";
            QMessageBox messageBox;
            messageBox.critical(0,"Warning","Close Hangout to continue !",Qt::WindowOkButtonHint,Qt::WindowStaysOnTopHint);
            //return 0;
        }
    }
}
tabHistory.close();

if(tabHistory.open(QFile::WriteOnly| QFile::Truncate))
{
    tabHistory.remove();
}


}
// w.show();
 a.exec();
//return 0;
}

