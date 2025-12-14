#include <Binder.hpp>



bool StartCore(Clock::SystemTime * clock , Clock::Display * display) {
    QObject::connect(clock, &Clock::SystemTime::currentTime 
    , display , &Clock::Display::updateNewTime);

    QObject::connect(display , &Clock::Display::updateNewTime 
        , clock, &Clock::SystemTime::currentTime);

    return true;
}