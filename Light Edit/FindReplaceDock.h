#pragma once

#include <QDockWidget>
#include "ui_FindReplaceDock.h"

class FindReplaceDock : public QDockWidget
{
	Q_OBJECT

public:
	FindReplaceDock(QWidget *parent = Q_NULLPTR);


public:
	// Prepares inputs to find
	void find(const QString &TARGET = "");

	// Prepares inputs to replace
	void replace(const QString& TARGET = "");


private:
	// When the user wants to focus this
	void userFocus(const bool REPLACE = false);


private:
	Ui::FindReplaceDock ui;
};
