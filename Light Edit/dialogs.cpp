#include "dialogs.h"

#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>


namespace dialogs
{
	BTN yesNoCancel(const QString& TITLE, const QString& DESCRIPTION, QWidget *parent)
	{
		QMessageBox msgBox(parent);

		msgBox.setWindowTitle(TITLE);
		msgBox.setText(DESCRIPTION);

		QAbstractButton* yesBtn = msgBox.addButton("Yes", QMessageBox::YesRole),
			* cancelBtn = msgBox.addButton("Cancel", QMessageBox::RejectRole),
			* noBtn = msgBox.addButton("No", QMessageBox::NoRole);

		msgBox.exec();

		if (msgBox.clickedButton() == yesBtn)
			return BTN::YES;

		else if (msgBox.clickedButton() == noBtn)
			return BTN::NO;

		return BTN::CANCEL;
	}
};