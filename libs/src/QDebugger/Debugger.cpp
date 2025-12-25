#include <Debugger.hpp>
#include <QString>
#include <QMessageLogContext>
#include <qlogging.h>
#include <QFile>
#include <qtextstream.h>
#include <QDateTime>
#include <QMessageLogContext>
#include <QDebug>

const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

//This should be clear that what does this function actually does right ? 
void handler(QtMsgType type , const QMessageLogContext & context, const QString & msg) {
    QString txt("");
    switch (type) {
        case QtInfoMsg : 
            txt = QString("Info : %1").arg(msg);
            break;
        case QtDebugMsg :
            txt = QString("Debug : %1").arg(msg);
            break;
        case QtWarningMsg : 
            txt = QString("Warning : %1").arg(msg);
            break;
        case QtCriticalMsg :
            txt = QString("Critical : %1").arg(msg);
            break;
        case QtFatalMsg :
            txt = QString("Fatal : %1").arg(msg);
            break;
    }

    QFile logfile("log.txt");
    if(logfile.open(QIODevice::Append | QIODevice::ReadWrite)) {
        QTextStream textsteam_buffer(&logfile);
        textsteam_buffer << QDateTime::currentDateTime().toString() << " - " << txt << " file : " << context.file << " line : " << context.line << "\r\n";
        textsteam_buffer.flush();
        logfile.close();
    }

    (*QT_DEFAULT_MESSAGE_HANDLER)(type , context , msg);
}