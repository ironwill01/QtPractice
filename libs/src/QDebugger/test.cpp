#include <qcontainerfwd.h>
#include <QJsonDocument>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qvariant.h>
#include <test.hpp>
#include <qobject.h>
#include <QJsonObject>

Test::Test(QObject * parent) : QObject(parent) {};

Test::Test(QObject * parent , const QMap<qint32, QStringMap> & u_map) : 
QObject(parent) , dataMap(u_map) {
    QJsonObject obj;
    for(const auto & key : u_map.keys()) {
        QJsonArray arr = QJsonArray();
        for(const auto & value : u_map.value(key)) {
            arr.append(value.trimmed());
        }
        obj[QString::number(key).trimmed()] = arr;
    }
    mapToString = QString(QJsonDocument(obj).toJson(QJsonDocument::Compact));
};

QDataStream & operator>>(QDataStream & stream, Test & t) {
    qInfo() << "Loading data !";
    stream >> t.dataMap;
    return stream;
};

QDataStream & operator<<(QDataStream & stream , const Test & t) {
    qInfo() << "Loading data !";
    stream << t.dataMap;
    return stream;
}

bool Test::setMap(const QMap<qint32, QStringMap> & map) {
    if(map.isEmpty()) {
        qInfo() << "Error : map was empty !";
        return false;
    }
    dataMap = map;
    return true;
};

const QMap<qint32 , QStringMap> & Test::getMapConst() const {
    return dataMap;
}

QMap<qint32 , QStringMap> & Test::getMap() {
    return dataMap;
}

QString Test::getStringMap() const {
    return mapToString;
}

void Test::printData() {
    if(dataMap.isEmpty()) {
        qInfo() << "Empty ...";
        return;
    }

    for(const auto & key : dataMap.keys()) {
        qInfo() << "Data in [" << key << "]" << " : ";
        for(const auto & value : dataMap[key]) {
            qInfo().noquote() << value;
        }
    }
}

