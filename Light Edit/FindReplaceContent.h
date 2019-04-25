#pragma once

#include <QDockWidget>
#include "ui_FindReplaceContent.h"

class FindReplaceContent : public QWidget
{
	Q_OBJECT

public:
	FindReplaceContent(QWidget* parent = Q_NULLPTR);


public:
	// Prepares inputs to find
	void find(const QString& TARGET);

	// Prepares inputs to replace
	void replace(const QString& TARGET);


private slots:
	void replaceChecked(int value);

	void nextPressed();
	void allPressed();


private:
	// Enables / Disables inputs to find
	void prepareFindInputs();

	// Enables / Disables inputs to replace
	void prepareReplaceInputs();


public:
	Ui::FindReplaceContent ui;
};
