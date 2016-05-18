#include "scripthighlighter.h"

ScriptHighlighter::ScriptHighlighter(QTextDocument* parent, Highlighter::Types type) :
    QSyntaxHighlighter(parent)
{
    _currentType = type;
    Rule rule;
    _keywordFormat.setForeground(Qt::darkMagenta);
    _keywordFormat.setFontWeight(QFont::ExtraBold);

    QStringList pythonKeywords;
    pythonKeywords << "\\band\\b" << "\\bas\\b" << "\\bassert\\b"
                   << "\\bbreak\\b" << "\\bclass\\b" << "\\bcontinue\\b"
                   << "\\bdef\\b" << "\\bdel\\b" << "\\belif\\b"
                   << "\\bexcept\\b" << "\\bexec\\b" << "\\bfinally\\b"
                   << "\\bfor\\b" << "\\bfrom\\b" << "\\bglobal\\b"
                   << "\\bif\\b" << "\\bimport\\b" << "\\bin\\b"
                   << "\\bis\\b" << "\\blambda\\b" << "\\bnot\\b"
                   << "\\bor\\b" << "\\bpass\\b" << "\\bprint\\b"
                   << "\\braise\\b" << "\\breturn\\b" << "\\btry\\b"
                   << "\\bwhile\\b" << "\\bwith\\b" << "\\byield\\b";

    QStringList luaKeywords;
    luaKeywords << "\\band\\b" << "\\bbreak\\b" << "\\bdo\\b"
                << "\\belse\\b" << "\\belseif\\b" << "\\bend\\b"
                << "\\bend\\b" << "\\bfalse\\b" << "\\bfor\\b"
                << "\\bfunction\\b" << "\\bif\\b" << "\\bin\\b"
                << "\\blocal\\b" << "\\bnil\\b" << "\\bnot\\b"
                << "\\bor\\b" << "\\brepeat\\b" << "\\breturn\\b"
                << "\\bthen\\b" << "\\btrue\\b" << "\\buntil\\b"
                << "\\bwhile\\b";

    foreach(const QString &pattern, pythonKeywords)
    {
        rule.pattern  = QRegExp(pattern);
        rule.format = _keywordFormat;
        _rules.insert(Highlighter::Types::Python, rule);
    }
    foreach(const QString &pattern, luaKeywords)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = _keywordFormat;
        _rules.insert(Highlighter::Types::Lua, rule);
    }
    emit typeChanged(Highlighter::Types::Python);
}

Highlighter::Types ScriptHighlighter::currentType()
{
    return _currentType;
}

void ScriptHighlighter::changeType(Highlighter::Types type)
{
    _currentType = type;
    rehighlight();
    emit typeChanged(type);
}

void ScriptHighlighter::highlightBlock(const QString &text)
{
    QMultiMap<Highlighter::Types,Rule>::iterator it = _rules.find(_currentType);
    while(it != _rules.end())
    {
        if(it.key() == _currentType)
        {
            QRegExp expression(it.value().pattern);
            int index = expression.indexIn(text);
            while(index >= 0)
            {
                int length = expression.matchedLength();
                setFormat(index,length,it.value().format);
                index = expression.indexIn(text,index + length);
            }
        }
        ++it;
    }
    setCurrentBlockState(0);
}
