#include "scripthighlighter.h"

ScriptHighlighter::ScriptHighlighter(QTextDocument* parent, Highlighter::Types type) :
    QSyntaxHighlighter(parent)
{
    _currentType = type;
}

Highlighter::Types ScriptHighlighter::currentType()
{
    return _currentType;
}

void ScriptHighlighter::changeType(Highlighter::Types type)
{
    _currentType = type;
}

void ScriptHighlighter::highlightBlock(const QString &text)
{

}
