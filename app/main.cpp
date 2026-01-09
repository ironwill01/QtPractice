#include <qcontainerfwd.h>
#include <qcoreapplication.h>
#include <Debugger.hpp>
#include <qdir.h>
#include <qfileinfo.h>
#include <qlogging.h>
#include <QDebug>
#include <qobject.h>
#include <qtypes.h>
#include <qxmlstream.h>
#include <test.hpp>

bool writeXML(const Test & obj , const QString & path) {
    if(QFileInfo(path).suffix() != "xml") {
        qCritical() << "File is not XML returning !";
        return false;
    } 
    
    QFile file(path);
    
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Could not write file !";
        qCritical() << file.errorString();
        return false;
    }

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);

    stream.writeStartDocument();
        stream.writeStartElement("data");
            for(const auto & key : obj.getMapConst().keys()) {
                stream.writeStartElement("row");
                stream.writeAttribute("id" , QString::number(key));
                for(const auto & value : obj.getMapConst().value(key)) {
                    stream.writeTextElement("value" , value);
                }
                stream.writeEndElement();
            }
        stream.writeEndElement();
    stream.writeEndDocument();

    file.close();

    return true;
}

bool readXML(Test & obj , const QString & path) {

    if(QFileInfo(path).suffix() != "xml") {
        qCritical() << "File is not XML returning !";
        return false;
    } 
    
    QFile file(path);
    
    if(!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Could not write file !";
        qCritical() << file.errorString();
        return false;
    }

    QXmlStreamReader stream(&file);
    QMap<qint32, QStringMap> & objDataRef = obj.getMap();
    objDataRef.clear(); 

    qint32 currentRowId = -1;

    while(!stream.atEnd()) {
        QXmlStreamReader::TokenType token = stream.readNext();
        switch(token) {
            case QXmlStreamReader::Comment :
                //Skip
            break;

            case QXmlStreamReader::DTD :
                //Skip
            break;

            case QXmlStreamReader::Characters :
                //Skip
            break;

            case QXmlStreamReader::ProcessingInstruction :
                //Skip
            break;

            case QXmlStreamReader::EntityReference :
                //Skip
            break;

            case QXmlStreamReader::NoToken :
                //Skip
            break;

            case QXmlStreamReader::Invalid :
                //Skip
            break;
            
            case QXmlStreamReader::StartDocument :
                //Skip
            break;

            case QXmlStreamReader::EndDocument :
                file.close();
                return true;
            break;

            case QXmlStreamReader::StartElement :
                if(stream.name().toString() == "row") {
                    currentRowId = stream.attributes().value("id").toInt();
                    objDataRef[currentRowId] = QStringList();
                }
                if(stream.name().toString() == "value" && currentRowId != -1) {
                    QString val = stream.readElementText().trimmed();
                    objDataRef[currentRowId].append(val);
                }
            break;

            case QXmlStreamReader::EndElement :
                if(stream.isEndElement() && stream.name().toString() == "row") currentRowId = -1;
            break;

        }
    }

    return true;
}

int main(int argc , char ** argv) {
    
    if(argc < 2) {
         qInfo() << "Enter an directory path !";
    }

    qInstallMessageHandler(handler);

    QCoreApplication app(argc , argv);

    QMap<qint32, QStringMap> map = {
        std::pair<qint32, QStringMap>(qint32(1) , QStringMap({"something" , " is " , "Right"})), 
        std::pair<qint32, QStringMap>(qint32(2) , QStringMap({"and" , "im" , "testing"})) ,
        std::pair<qint32, QStringMap>(qint32(3) , QString("this")),
    };

    Test data(&app , map);

    readXML(data , argv[1]);

    data.printData();

    return 0;
}