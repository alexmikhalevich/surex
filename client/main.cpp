#include <qt5/QtGui/QGuiApplication>
#include "cmainwindow.h"

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);
    CMainWindow main_window;
    main_window.show();

    return app.exec();
}
