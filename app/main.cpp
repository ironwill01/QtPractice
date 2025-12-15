#include <DateTime.hpp>
#include <Binder.hpp>
#include <QCoreApplication>
#include <QTimer>

using namespace Clock;

int main(int argc , char ** argv) {
    QCoreApplication app(argc , argv);


    qSetMessagePattern("%{message}");

    SystemTime timer;
    Display display;

    if(!StartCore(&timer , &display)) {
        qCritical() << "Could not start the app !";
        return 1;
    }
    
    QTimer updateTimer;
    updateTimer.setParent(&app);
    QObject::connect(&updateTimer, &QTimer::timeout, &timer, &SystemTime::updateClock);
    updateTimer.start(1000);

    return app.exec();
}