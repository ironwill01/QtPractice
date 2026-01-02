#include <qcontainerfwd.h>
#include <qcoreapplication.h>
#include <Debugger.hpp>
#include <qdir.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonvalue.h>
#include <qlogging.h>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <qobject.h>
#include <test.hpp>

bool loadFile(Test & dataTest) {
    QFile file("./test.txt");
    if(!file.open(QIODevice::ReadOnly)) return false;

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Version::Qt_6_10);
    
    if(ds.version() != QDataStream::Version::Qt_6_10) {
       qWarning() << "Data stream is not compatible exiting ...";
       return false; 
    }
    
    ds >> dataTest;
    return true;
}

bool saveFile(const Test & dataTest) {
    QFile file("./test.txt");
    if(!file.open(QIODevice::WriteOnly)) return false;

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Version::Qt_6_10);
    
    if(ds.version() != QDataStream::Version::Qt_6_10) {
       qWarning() << "Data stream is not compatible exiting ...";
       return false; 
    }

    ds << dataTest;

    return true;
}

bool writeJson(const QJsonObject & obj) {
    QFile jsonFile("./data.json");
    if(!jsonFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;

    QJsonDocument jsonDoc = QJsonDocument(obj);
    jsonFile.write(jsonDoc.toJson(QJsonDocument::Indented));

    jsonFile.close();

    return true;
}

bool readJson(QJsonObject & obj) {
    QFile jsonFile("./data.json");
    if(!jsonFile.open(QIODevice::ReadOnly)) return false;    
    if(!obj.isEmpty()) obj = QJsonObject();

    const QByteArray & bytes = jsonFile.readAll();
    
    jsonFile.close();

    const QJsonDocument & doc = QJsonDocument::fromJson(bytes);

    if(!doc.isObject()) return false;

    obj = doc.object();

    jsonFile.close();

    return true;
}


int main(int argc , char ** argv) {
    
    // if(argc < 2) {
    //     qInfo() << "Enter an directory path !";
    // }

    qInstallMessageHandler(handler);

    QCoreApplication app(argc , argv);

    QMap<qint32, QStringMap> map = {
        std::pair<qint32, QStringMap>(qint32(1) , QStringMap({"something" , " is " , "Right"})), 
        std::pair<qint32, QStringMap>(qint32(2) , QStringMap({"and" , "im" , "testing"})) ,
        std::pair<qint32, QStringMap>(qint32(3) , QString("this")),
    };

    Test data(&app , map);

    QJsonObject json = QJsonObject();

    json << data;
    writeJson(json);
    readJson(json);

    qInfo() << json;

    return 0;
}