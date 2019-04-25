#include "FindReplaceContent.h"

#include "MainWindow.h"
#include "Editor.h"


FindReplaceContent::FindReplaceContent(QWidget* parent)
	: QWidget(parent)
{
	//// UI ////
	ui.setupUi(this);

	//// Slots ////
	// CheckBoxes
	connect(ui.replaceMode, &QCheckBox::stateChanged, this, &FindReplaceContent::replaceChecked);

	// Buttons
	connect(ui.next, &QPushButton::pressed, this, &FindReplaceContent::nextPressed);
	connect(ui.all, &QPushButton::pressed, this, &FindReplaceContent::allPressed);
}

void FindReplaceContent::find(const QString& TARGET)
{
	// Update text
	ui.find->setText(TARGET);

	// Update ui
	prepareFindInputs();
}

void FindReplaceContent::replace(const QString& TARGET)
{
	// Update text
	ui.find->setText(TARGET);

	// Update ui
	prepareReplaceInputs();
}

void FindReplaceContent::replaceChecked(int value)
{
	if (value == Qt::Checked)
	{
		// Prepare
		prepareReplaceInputs();

		// Focus
		ui.replace->setFocus();
		ui.replace->selectAll();
	}
	else
	{
		// Prepare
		prepareFindInputs();

		// Focus
		ui.find->setFocus();
		ui.find->selectAll();
	}
}

void FindReplaceContent::nextPressed()
{
	if (!ui.replaceMode->isChecked())
	{
		if (ui.regex->isChecked())
			Editor::instance->findRegex(ui.find->text(), ui.caseMode->isChecked());
		else
			Editor::instance->find(ui.find->text(), ui.caseMode->isChecked());
	}
	else if(ui.regex->isChecked())
		Editor::instance->replaceRegex(ui.find->text(), ui.replace->text(), ui.caseMode->isChecked());
	else
		Editor::instance->replace(ui.find->text(), ui.replace->text(), ui.caseMode->isChecked());
}

void FindReplaceContent::allPressed()
{
	if (ui.regex->isChecked())
		Editor::instance->replaceRegexAll(ui.find->text(), ui.replace->text(), ui.caseMode->isChecked());
	else
		Editor::instance->replaceAll(ui.find->text(), ui.replace->text(), ui.caseMode->isChecked());
}

void FindReplaceContent::prepareFindInputs()
{
	ui.replaceMode->setChecked(false);
	ui.replace->setEnabled(false);
	ui.all->setEnabled(false);
}

void FindReplaceContent::prepareReplaceInputs()
{
	ui.replaceMode->setChecked(true);
	ui.replace->setEnabled(true);
	ui.all->setEnabled(true);
}
