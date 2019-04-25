#include "FindReplaceDock.h"

#include <QTimer>


FindReplaceDock::FindReplaceDock(QWidget *parent)
	: QDockWidget(parent)
{
	ui.setupUi(this);
}

void FindReplaceDock::userFocus(const bool REPLACE)
{
	activateWindow();

	if (REPLACE)
	{
		ui.child->ui.replace->setFocus();
		ui.child->ui.replace->selectAll();
	}
	else
	{
		ui.child->ui.find->setFocus();
		ui.child->ui.find->selectAll();
	}
}

void FindReplaceDock::find(const QString& TARGET)
{
	// Prepare child //
	ui.child->find(TARGET);

	// Activate the window //
	if (isHidden())
		show();

	userFocus();
}

void FindReplaceDock::replace(const QString& TARGET)
{
	// Prepare child //
	ui.child->replace(TARGET);

	// Activate the window //
	if (isHidden())
		show();

	userFocus(true);
}
