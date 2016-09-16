#include <QApplication>
#include "frontcameradialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FRONT_CAMERA *dialog = new FRONT_CAMERA;
    dialog->show();

    return a.exec();
}

