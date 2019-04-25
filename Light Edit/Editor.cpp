#include "Editor.h"

#include <QRegularExpression>

#include "MainWindow.h"


Editor* Editor::instance = nullptr;

Editor::Editor(QWidget *parent)
	: QPlainTextEdit(parent)
{
	instance = this;

	ui.setupUi(this);

	connect(this, &QPlainTextEdit::textChanged, this, &Editor::onTextChanged);
}

bool Editor::find(const QString& TARGET, const bool CASE_SENSITIVE)
{
	const QString DATA = toPlainText();
	QTextCursor c = textCursor();

	const int RESULT = DATA.indexOf(TARGET, c.position(), CASE_SENSITIVE ? Qt::CaseSensitivity::CaseSensitive : Qt::CaseSensitivity::CaseInsensitive);

	// No occurence found
	if (RESULT == -1)
	{
		// We set the cursor position to the start of the document
		c.setPosition(0);
		setTextCursor(c);

		return false;
	}

	// Select the target
	c.setPosition(RESULT);
	c.movePosition(QTextCursor::MoveOperation::Right, QTextCursor::MoveMode::KeepAnchor, TARGET.size());

	setTextCursor(c);

	// Focus
	activateWindow();
	setFocus();

	return true;
}

bool Editor::findRegex(const QString& TARGET, const bool CASE_SENSITIVE)
{
	const QString DATA = toPlainText();
	QTextCursor c = textCursor();

	QRegularExpressionMatch match;

	DATA.indexOf(QRegularExpression(TARGET, 
		CASE_SENSITIVE ? QRegularExpression::PatternOption::NoPatternOption : 
		QRegularExpression::PatternOption::CaseInsensitiveOption), c.position(), &match);

	// No occurence found
	if (!match.hasMatch())
	{
		// We set the cursor position to the start of the document
		c.setPosition(0);
		setTextCursor(c);

		return false;
	}

	// Select the target
	c.setPosition(match.capturedStart());
	c.movePosition(QTextCursor::MoveOperation::Right, QTextCursor::MoveMode::KeepAnchor, match.capturedLength());

	setTextCursor(c);

	// Focus
	activateWindow();
	setFocus();

	return true;
}

bool Editor::replace(const QString& TARGET, const QString& CONTENT, const bool CASE_SENSITIVE)
{
	const QString DATA = toPlainText();
	QTextCursor c = textCursor();

	const int RESULT = DATA.indexOf(TARGET, c.position(), CASE_SENSITIVE ? Qt::CaseSensitivity::CaseSensitive : Qt::CaseSensitivity::CaseInsensitive);

	// No occurence found
	if (RESULT == -1)
	{
		// We set the cursor position to the start of the document
		c.setPosition(0);
		setTextCursor(c);

		return false;
	}

	c.beginEditBlock();

	// Select the target
	c.setPosition(RESULT);
	c.movePosition(QTextCursor::MoveOperation::Right, QTextCursor::MoveMode::KeepAnchor, TARGET.size());
	c.insertText(CONTENT);

	c.endEditBlock();

	setTextCursor(c);

	// Focus
	activateWindow();
	setFocus();

	return true;
}

bool Editor::replaceRegex(const QString& TARGET, const QString& CONTENT, const bool CASE_SENSITIVE)
{
	const QString DATA = toPlainText();
	QTextCursor c = textCursor();

	QRegularExpressionMatch match;

	DATA.indexOf(QRegularExpression(TARGET,
		CASE_SENSITIVE ? QRegularExpression::PatternOption::NoPatternOption :
		QRegularExpression::PatternOption::CaseInsensitiveOption), c.position(), &match);

	// No occurence found
	if (!match.hasMatch())
	{
		// We set the cursor position to the start of the document
		c.setPosition(0);
		setTextCursor(c);

		return false;
	}

	c.beginEditBlock();

	// Select the target
	c.setPosition(match.capturedStart());
	c.movePosition(QTextCursor::MoveOperation::Right, QTextCursor::MoveMode::KeepAnchor, match.capturedLength());

	// Replace
	c.insertText(CONTENT);

	c.endEditBlock();

	setTextCursor(c);

	// Focus
	activateWindow();
	setFocus();

	return true;
}

void Editor::replaceAll(const QString& TARGET, const QString& CONTENT, const bool CASE_SENSITIVE)
{
	const QString DATA = toPlainText();
	QTextCursor c = textCursor();

	// Init the cursor
	c.setPosition(0);
	c.beginEditBlock();

	int result = 0;
	while (true)
	{
		result = DATA.indexOf(TARGET, c.position(), CASE_SENSITIVE ? Qt::CaseSensitivity::CaseSensitive : Qt::CaseSensitivity::CaseInsensitive);

		// No next occurence found
		if (result == -1)
		{
			c.endEditBlock();
			setTextCursor(c);

			// Focus
			activateWindow();
			setFocus();

			return;
		}

		// Select the target
		c.setPosition(result);
		c.movePosition(QTextCursor::MoveOperation::Right, QTextCursor::MoveMode::KeepAnchor, TARGET.size());

		// Replace
		c.insertText(CONTENT);
	}
}

void Editor::replaceRegexAll(const QString& TARGET, const QString& CONTENT, const bool CASE_SENSITIVE)
{
	QString data = toPlainText();
	QTextCursor c = textCursor();

	// Replace all occurences
	data.replace(QRegularExpression(TARGET,
		CASE_SENSITIVE ? QRegularExpression::PatternOption::NoPatternOption :
		QRegularExpression::PatternOption::CaseInsensitiveOption),
		CONTENT);

	c.beginEditBlock();

	// Select
	c.select(QTextCursor::SelectionType::Document);

	// Replace
	c.insertText(data);

	c.endEditBlock();
	setTextCursor(c);

	// Focus
	activateWindow();
	setFocus();
}

void Editor::onTextChanged()
{
	MainWindow::instance->saved = false;
}
