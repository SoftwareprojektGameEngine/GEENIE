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

/*!
 * \brief The ScriptHighlighter class is a subclass of QSyntaxHighlighter. Highlights script keywords depending on the script type.
 */

class ScriptHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    /*!
     * \brief ScriptHighlighter constructor
     * \param parent
     * \param type
     */
    ScriptHighlighter(QTextDocument* parent, Highlighter::Types type = Highlighter::Types::Python);

    /*!
     * \brief Returns the current script highlighting type
     * \return type
     */
    Highlighter::Types currentType();

    /*!
     * \brief Changes the script type
     * \param type
     */
    void changeType(Highlighter::Types type);

signals:
    /*!
     * \brief Signals if script type has changed
     */
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
