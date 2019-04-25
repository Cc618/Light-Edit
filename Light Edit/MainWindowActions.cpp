#include "MainWindow.h"

#include <QString>
#include <QFileDialog>
#include <QDialog>
#include <QUrl>
#include <QDesktopServices>

#include "ui_AboutDialog.h"

#include "FindReplaceContent.h"
#include "files.h"
#include "dialogs.h"


void MainWindow::setActions()
{
	//// File ////
	// New
	QObject::connect(ui.actionNew, &QAction::triggered, this, &MainWindow::actionNew);

	// Open
	QObject::connect(ui.actionOpen, &QAction::triggered, this, &MainWindow::actionOpen);

	// Save
	QObject::connect(ui.actionSave, &QAction::triggered, this, &MainWindow::actionSave);

	// Save as
	QObject::connect(ui.actionSaveAs, &QAction::triggered, this, &MainWindow::actionSaveAs);

	// Quit
	QObject::connect(ui.actionQuit, &QAction::triggered, this, &MainWindow::actionQuit);

	//// Edit ////
	// Find
	QObject::connect(ui.actionFind, &QAction::triggered, this, &MainWindow::actionFind);

	// Replace
	QObject::connect(ui.actionReplace, &QAction::triggered, this, &MainWindow::actionReplace);

	//// Help ////
	// About
	QObject::connect(ui.actionAbout, &QAction::triggered, this, &MainWindow::actionAbout);
}

void MainWindow::actionNew()
{
	// Save...
	if (!assumeSaved())
		return;

	// Set the current file path
	_currentFilePath.clear();

	// Clear the editor
	ui.editor->clear();

	saved = true;
}

void MainWindow::actionOpen()
{
	// Save...
	if (!assumeSaved())
		return;

	// Dialog from my documents
	const QString FILE_PATH = QFileDialog::getOpenFileName(this,
		"Open",
		QDir::homePath() + "/documents",
		"Text File (*.txt)");

	// Canceled
	if (FILE_PATH.isEmpty())
		return;

	// Read and open the document in the editor
	open(FILE_PATH);
}

void MainWindow::actionSave()
{
	save();
}

void MainWindow::actionSaveAs()
{
	save(true);
}

void MainWindow::actionQuit()
{
	this->close();
}

void MainWindow::actionFind()
{
	// Find
	dockFindReplace->find(ui.editor->textCursor().selectedText());
}

void MainWindow::actionReplace()
{
	// Replace
	dockFindReplace->replace(ui.editor->textCursor().selectedText());
}

void MainWindow::actionAbout()
{
	Ui::AboutDialog dialogUi;
	QDialog *aboutDialog = new QDialog(this);

	// UI setup
	dialogUi.setupUi(aboutDialog);

	// GitHub button to open the web url
	connect(dialogUi.github, &QPushButton::pressed, this, []() {
		QDesktopServices::openUrl(QUrl("https://github.com/Cc618"));
	});

	// Dialog's display
	aboutDialog->show();
}
