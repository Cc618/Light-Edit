#include "files.h"

#include <QFile>
#include <QTextStream>

namespace files
{
	bool files::write(const QString& PATH, const QString& DATA)
	{
		QFile file(PATH);

		if (file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QTextStream stream(&file);

			stream << DATA;

			file.close();

			return true;
		}

		return false;
	}

	QString read(const QString& PATH)
	{
		QFile file(PATH);

		if (!file.open(QIODevice::OpenModeFlag::ReadOnly | QIODevice::OpenModeFlag::Text))
			return "";

		QString data;
		QTextStream in(&file);

		// Reading
		while (!in.atEnd())
			data += in.readLine() + '\n';

		file.close();

		return data;
	}
};
