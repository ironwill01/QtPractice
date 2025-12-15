#include <DateTime.hpp>
#include <memory>
#include <qdatetime.h>
#include <qlogging.h>
#include <qobject.h>
#include <iostream>



namespace Clock {

    //SystemTime

    SystemTime::SystemTime(QObject * parent)
    : QObject(parent) {
        this->realTimer = std::unique_ptr<QTime>(
            new(std::nothrow) QTime()
        );
    };

    const QString SystemTime::currentSystemTime() {
        return QTime::currentTime().toString();
    };

    bool SystemTime::updateClock() {
        if(!realTimer) {
            qCritical() << "Timer does not exist cannot update or send any system time by this call !";
            return false;
        }

        emit currentTime(realTimer->currentTime().toString());
        return true;
    };

    // Display

    Display::Display(QObject * parent) : QObject(parent) {};

    void Display::updateNewTime(const QString time) {
        
        std::cout << "\033[2J\033[H" << time.toStdString() << std::endl;
    }
}
