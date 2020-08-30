#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "mymodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
	app.setApplicationName("ListView C++ Integration Dynamic Length from Separate Thread Test");
	app.setOrganizationName("");
	app.setOrganizationDomain("");

	QQmlApplicationEngine engine;
    qmlRegisterType<MyModel>("my.models", 1, 0, "MyModel");
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}