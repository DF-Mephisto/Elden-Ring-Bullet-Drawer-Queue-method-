#pragma once
#include <QtCore>

class Logger
{
public:
	void write(QString str);

	static Logger& getInstance();

private:
	Logger(QString name);
	~Logger();
	QFile file;

};

