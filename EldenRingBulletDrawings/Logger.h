#pragma once
#include <QtCore>

class Logger
{
public:
	Logger(QString name);
	~Logger();
	void write(QString str);

	static Logger& getInstance();

private:
	QFile file;

};

