#include "MainWindow.h"

#include <QFileDialog>

#include "FindReplaceDock.h"
#include "files.h"
#include "dialogs.h"


MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(int argc, char* argv[])
	: QMainWindow(nullptr)
{
	//// Singleton ////
	instance = this;

	//// UI ////
	ui.setupUi(this);

	dockFindReplace = new FindReplaceDock(this);
	dockFindReplace->hide();
	addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockFindReplace);

	//// Actions ////
	setActions();

	//// Arguments ////
	// Only if 1 argument ore more (the first argument is the current working directory)
	if (argc > 1)
		open(argv[1U]);
}

void MainWindow::closeEvent(QCloseEvent* e)
{
	if (assumeSaved())
		e->accept();
	else
		e->ignore();
}

bool MainWindow::save(const bool NEW)
{
	if (NEW || _currentFilePath.isEmpty())
	{
		// Dialog from my documents
		const QString FILE_PATH = QFileDialog::getSaveFileName(this,
			"Save",
			QDir::homePath() + "/documents",
			"Text File (*.txt)");

		// Canceled
		if (FILE_PATH.isEmpty())
			return false;

		// Set the current file path
		_currentFilePath = FILE_PATH;
	}

	// Write the content to the file
	saved = files::write(_currentFilePath, ui.editor->toPlainText());

	return saved;
}

void MainWindow::open(const QString& FILE_PATH)
{
	// Set the current file path
	_currentFilePath = FILE_PATH;

	// Read the file
	ui.editor->setPlainText(files::read(FILE_PATH));

	saved = true;
}

bool MainWindow::assumeSaved()
{
	if (saved)
		return true;

	// Dialog to save or not
	switch (dialogs::save(this))
	{
	case dialogs::BTN::YES:
		return save();

	case dialogs::BTN::CANCEL:
		return false;
	}

	return true;
}
