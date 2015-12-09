#include <mainwindow.h>
#include <QApplication>
#include <Constants.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName(ORG);
    a.setOrganizationDomain(ORG);
    a.setApplicationName(APP);

    MainWindow window;
    window.show();
    window.updateView();
    //TODO: app settings
    return a.exec();
}
