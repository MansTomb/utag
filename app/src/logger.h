#ifndef LOGGER
#define LOGGER

#include <QTextEdit>

class Logger : public QTextEdit
{
    Q_OBJECT
 public:
    explicit Logger(QWidget *parent = Q_NULLPTR);
 public slots:
    void WriteToLog(QString message);
};

#endif // LOGGER
