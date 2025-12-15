#include <Binder.hpp>


bool StartCore(Clock::SystemTime * clock , Clock::Display * display) {
    QObject::connect(clock, &Clock::SystemTime::currentTime 
    , display , &Clock::Display::updateNewTime);

    return true;
}