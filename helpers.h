#ifndef HELPERS_H
#define HELPERS_H

#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>

class Helpers
{
public:
    static void centerWindow(QWidget *window);
    static void sayMessage(const QString &text, const QString &informativeText, const QMessageBox::Icon &icon);
};

#endif // HELPERS_H
