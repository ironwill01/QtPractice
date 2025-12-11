#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <QObject>
#include <QTime>
#include <QPointer>
#include <memory>
#include <qdatetime.h>

namespace Clock {
    class SystemTime : public QObject {
        private :
            Q_OBJECT
            std::unique_ptr<QTime> realTimer;

        public :
            SystemTime(QObject * parent = nullptr);
            static const QString currentSystemTime();
            
        public slots :
            bool updateClock();
        
        signals : 
            void currentTime(const QString time);
    };
}


#endif //DATETIME_HPP