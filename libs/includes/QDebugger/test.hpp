#include <QFile>
#include <QDebug>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qlogging.h>
#include <qmap.h>
#include <qobject.h>
#include <qset.h>
#include <qtmetamacros.h>
#include <qtypes.h>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

typedef QVector<QString> QStringMap;

class Test : public QObject {
    Q_OBJECT

    private :
        QMap<qint32 , QStringMap> dataMap;
    
    public : 
        explicit Test(QObject * parent = nullptr) : QObject(parent) {};

        Test(QObject * parent , const QMap<qint32, QStringMap> & u_map) : QObject(parent) {
            dataMap = u_map;
        };

        friend QDataStream & operator <<(QDataStream & stream , const Test & t) {
            qInfo() << "Loading data !";
            stream << t.dataMap;
            return stream;
        };

        friend QDataStream & operator>>(QDataStream & stream, Test & t) {
            qInfo() << "Loading data !";
            stream >> t.dataMap;
            return stream;
        };

        friend QJsonObject & operator<<(QJsonObject & jsonObj , Test & t) {
            const QMap<qint32 , QStringMap> & objRef = t.getMap();
            for(const auto & key : objRef.keys()) {
                QJsonArray arr = QJsonArray();
                for(const auto & value : objRef.value(key)) {
                    arr.append(value);
                }
                jsonObj[QString::number(key)] = arr;
            }
            return jsonObj;
        };

        friend QJsonObject & operator>>(QJsonObject & jsonObj , Test & t) {
            QMap<qint32 , QStringMap> & objRef = t.getMap();
            objRef.clear();

            for(const auto & key : jsonObj.keys()) {
                QStringMap vec = QStringMap();
                qint32 intkey = key.toInt();
                for(auto value : jsonObj.value(key).toArray() ) {
                    vec.append(value.toString());
                }
                objRef[intkey] = vec;
            }
            return jsonObj;
        };

        bool setMap(const QMap<qint32, QStringMap> & map) {
            if(map.isEmpty()) {
                qInfo() << "Error : map was empty !";
                return false;
            }
            dataMap = map;
            return true;
        };

        void printData() {
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
        };

        QMap<qint32 , QStringMap> & getMap() { 
            return dataMap; 
        };
};
