#include <mainwindow.h>
#include <QApplication>
#include <Constants.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName(SSw::ORG);
    a.setOrganizationDomain(SSw::ORG);
    a.setApplicationName(SSw::APP);

    SSw::MainWindow window;
    window.show();
    window.updateView();
    return a.exec();
}
