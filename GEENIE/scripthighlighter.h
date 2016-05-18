#ifndef SCRIPTHIGHLIGHTER_H
#define SCRIPTHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QString>

namespace Highlighter
{
    enum class Types
    {
        Python,
        Lua
    };
}

class ScriptHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    ScriptHighlighter(QTextDocument* parent, Highlighter::Types type = Highlighter::Types::Python);

    Highlighter::Types currentType();
    void changeType(Highlighter::Types type);

signals:
    void typeChanged(Highlighter::Types);

private:
    Highlighter::Types _currentType;

    struct Rule
    {
            QRegExp pattern;
            QTextCharFormat format;
    };

    QTextCharFormat _keywordFormat;
    QTextCharFormat _singleLineCommentFormat;
    QTextCharFormat _multilineCommentFormat;
    QTextCharFormat _quotationFormat;

    QMultiMap<Highlighter::Types,Rule> _rules;

protected:
    void highlightBlock(const QString& text) Q_DECL_OVERRIDE;
};

#endif // SCRIPTHIGHLIGHTER_H
