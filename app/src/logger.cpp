#include "logger.h"
#include <QtCore/QDate>
#include <QDebug>

void Logger::WriteToLog(QString message) {
    insertPlainText(QDate::currentDate().toString("[dd:MM:yyyy] "));
    insertPlainText(message.append("\n"));
}

Logger::Logger(QWidget *parent) : QTextEdit(parent) {

}
