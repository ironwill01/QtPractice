#include <qcoreapplication.h>
#include <Debugger.hpp>
#include <qlogging.h>
#include <QDebug>

int main(int argc , char ** argv) {
    
    qInstallMessageHandler(handler);

    if(argc < 2) {
        qInfo() << "Enter an directory path !";
    }

    QCoreApplication app(argc , argv);

    

    return 0;
}