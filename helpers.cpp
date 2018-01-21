#include "helpers.h"

void Helpers::centerWindow(QWidget *window) {
    window->setGeometry(
       QStyle::alignedRect(
           Qt::LeftToRight,
           Qt::AlignCenter,
           window->size(),
           qApp->desktop()->availableGeometry()
       )
    );
}

void Helpers::sayMessage(const QString &text, const QString &informativeText, const QMessageBox::Icon &icon) {
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.setInformativeText(informativeText);
    msgBox.setIcon(icon);

    QSpacerItem *horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

    msgBox.exec();
}
