#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <QFile>
#include <QTime>

void FileMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QFile ErrorsFile(ErrorsLogPath);
    if ( ErrorsFile.open(QIODevice::WriteOnly | QIODevice::Append) )
    {
        QTextStream ErrorsStream(&ErrorsFile);

        switch (type)
        {
        case QtInfoMsg:
            ErrorsStream << QTime::currentTime().toString() << " Info: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
            break;

        case QtDebugMsg:
            ErrorsStream << QTime::currentTime().toString() << " Debug: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
            break;

        case QtWarningMsg:
            ErrorsStream << QTime::currentTime().toString() << " Warning: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
            break;

        case QtCriticalMsg:
            ErrorsStream << QTime::currentTime().toString() << " Critical: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
            break;

        case QtFatalMsg:
            ErrorsStream << QTime::currentTime().toString() << " Fatal: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
            abort();

        }
    }
}

#endif
