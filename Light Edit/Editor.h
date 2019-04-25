#pragma once

#include "qplaintextedit.h"

#include "ui_Editor.h"


class Editor : public QPlainTextEdit
{
	Q_OBJECT

public:
	// Singleton
	static Editor *instance;


public:
	Editor(QWidget *parent = Q_NULLPTR);


public:
	// Finds the TARGET (select the first occurence of TARGET from the cursor position)
	// - Returns true if it finds an occurence after the cursor position
	bool find(const QString& TARGET, const bool CASE_SENSITIVE);
	bool findRegex(const QString& TARGET, const bool CASE_SENSITIVE);

	// Find and replace TARGET by CONTENT
	bool replace(const QString& TARGET, const QString& CONTENT, const bool CASE_SENSITIVE);
	bool replaceRegex(const QString& TARGET, const QString& CONTENT, const bool CASE_SENSITIVE);

	// Replace all occurences
	void replaceAll(const QString& TARGET, const QString& CONTENT, const bool CASE_SENSITIVE);
	void replaceRegexAll(const QString& TARGET, const QString& CONTENT, const bool CASE_SENSITIVE);

private slots:
	void onTextChanged();


private:
	Ui::Editor ui;
};
