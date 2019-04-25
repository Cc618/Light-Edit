#pragma once

#include <QString>
#include <QWidget>


namespace dialogs
{
	enum class BTN
	{
		YES,
		NO,
		CANCEL
	};

	// A yes-no-cancel dialog 
	BTN yesNoCancel(const QString &TITLE, const QString &DESCRIPTION, QWidget* parent = nullptr);

	// If the work is not saved
	inline BTN save(QWidget* parent = nullptr)
	{
		return yesNoCancel("Save", "Do you want to save before ?", parent);
	}
};

