#pragma once

#include <QtWidgets/QMainWindow>
#include <QDockWidget>
#include "ui_MainWindow.h"

#include "FindReplaceDock.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	// Singleton
	static MainWindow* instance;


public:
	MainWindow(int argc, char* argv[]);


public:
	// Whether the file is saved
	bool saved = true;


protected:
	// When we hit the quit button
	virtual void closeEvent(QCloseEvent* e) override;


private slots:
	//// File ////
	void actionNew();
	void actionOpen();
	void actionSave();
	void actionSaveAs();
	void actionQuit();

	//// Edit ////
	void actionFind();
	void actionReplace();

	//// Help ////
	void actionAbout();


private:
	// Bind the actions
	void setActions();

	// Save the content
	// Return if it's saved
	// - NEW if we want to override the file
	bool save(const bool NEW = false);

	// Read and open the document in the editor
	void open(const QString& FILE_PATH);

	// If it's saved returns true otherwise asks if we want to save
	// - If yes we save and return true
	// - If no we don't save and return true
	// - If cancel we don't save and return false
	bool assumeSaved();

	
private:
	Ui::MainWindowClass ui;

	FindReplaceDock* dockFindReplace = nullptr;

	// Current opened file path
	QString _currentFilePath;
};
