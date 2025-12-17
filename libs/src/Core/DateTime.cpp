#include <DateTime.hpp>
#include <cstdlib>
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

    void SystemTime::updateClock() {
        if(!realTimer) {
            qFatal() << "Timer does not exist cannot update or send any system time by this call !";
        }

        emit currentTime(realTimer->currentTime().toString("HH:mm:ss"));
    };

    // Display

    Display::Display(QObject * parent) : QObject(parent) {};

    void Display::updateNewTime(const QString time) {        
        
        #if defined (__linux__)
            system("clear");
        #elif defined(_WIN32)
            system("cls");
        #endif

        std::cout << "\033[2J\033[H" << time.toStdString() << std::endl;
    }
}
