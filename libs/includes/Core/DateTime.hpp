#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <QObject>
#include <QTime>
#include <QPointer>
#include <memory>
#include <qdatetime.h>
#include <qobject.h>

namespace Clock {

    class SystemTime : public QObject {
        Q_OBJECT

        private :
            std::unique_ptr<QTime> realTimer;

        public :
            explicit SystemTime(QObject * parent = nullptr);
            static const QString currentSystemTime();

        public slots :
            bool updateClock();

        signals :
            void currentTime(const QString time);
    };

    class Display : public QObject {
        Q_OBJECT

        public :
            explicit Display(QObject * parent = nullptr);

        public slots :
            void updateNewTime(const QString time);
    };
}

#endif //DATETIME_HPP