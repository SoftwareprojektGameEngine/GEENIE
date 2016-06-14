#ifndef LAYOUTFORM_H
#define LAYOUTFORM_H

#include <QWidget>

namespace Ui {
class LayoutForm;
}

/*!
 * \class LayoutForm layoutform.h
 * \brief The LayoutForm class.
 */

class LayoutForm : public QWidget
{
    Q_OBJECT

public:

    //! Constructor.
    /*!
     * Creates a new layoutform.
     * \param parent The parent widget.
     */

    explicit LayoutForm(QWidget *parent = 0);

    //! Deconstructor.
    /*!
     * Destroys the ui.
     */

    ~LayoutForm();

private:

    //! Private value stores the current layoutform ui.

    Ui::LayoutForm *ui;
};

#endif // LAYOUTFORM_H
