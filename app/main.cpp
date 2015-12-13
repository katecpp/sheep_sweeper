#include <mainwindow.h>
#include <Constants.h>
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName(SSw::ORG);
    a.setOrganizationDomain(SSw::ORG);
    a.setApplicationName(SSw::APP);

    QTranslator translator;
    bool result = translator.load("trans_pl");

    if (!result)
    {
        qWarning("Failed to load the translation file");
    }
    else
    {
        //a.installTranslator(&translator);
    }
    //TODO: translator mechanics

    SSw::MainWindow window;
    window.show();
    window.updateView();
    return a.exec();
}
