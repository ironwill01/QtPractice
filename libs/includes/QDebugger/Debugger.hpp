#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP
#include <qlogging.h>

class QMessageLogContext;
class QString;

void handler(QtMsgType type , const QMessageLogContext & context , const QString & msg);


#endif //DEBUGGER_HPP