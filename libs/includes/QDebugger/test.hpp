#include <QFile>
#include <QDebug>
#include <qcborcommon.h>
#include <qlogging.h>
#include <qmap.h>
#include <qobject.h>
#include <qset.h>
#include <qtmetamacros.h>
#include <qtypes.h>
#include <qxmlstream.h>

typedef QVector<QString> QStringMap;

class Test : public QObject {
    Q_OBJECT

    private :
        QMap<qint32 , QStringMap> dataMap;
        QString mapToString;
    
    public : 
        explicit Test(QObject * parent = nullptr);
        Test(QObject * parent , const QMap<qint32, QStringMap> & u_map);

        friend QDataStream & operator<<(QDataStream & stream, const Test & t);

        friend QDataStream & operator>>(QDataStream & stream, Test & t);

        bool setMap(const QMap<qint32, QStringMap> & map);

        const QMap<qint32 , QStringMap> & getMapConst() const;

        QMap<qint32 , QStringMap> & getMap();

        QString getStringMap() const ;

        void printData();
};
