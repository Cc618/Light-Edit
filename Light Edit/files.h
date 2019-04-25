#pragma once

#include <QString>


namespace files
{
	// Write to a file
	// Returns true if the writing is done
	bool write(const QString& PATH, const QString& DATA);

	// Read a file
	QString read(const QString &PATH);
};

