#include "Logger.h"

Logger::Logger(QString name)
	: file(name)
{
	file.open(QIODevice::WriteOnly | QIODevice::Append);
}

Logger::~Logger()
{
	
}

void Logger::write(QString str)
{
	QTextStream stream(&file);
	stream << str << endl;
}

Logger& Logger::getInstance()
{
	static Logger log(QDate::currentDate().toString(Qt::DateFormat::ISODate) + ".log");
	return log;
}