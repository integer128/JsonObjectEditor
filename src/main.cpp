#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "jsoneditormodel.h"
#include "textfielddoublevalidator.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    app.setOrganizationName(QStringLiteral("Organization name"));
    app.setApplicationVersion(QStringLiteral("1.0"));

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    JsonEditorModel model;
    engine.rootContext()->setContextProperty("jsonmodel", &model);
    qmlRegisterType<TextFieldDoubleValidator>("TextFieldDoubleValidator", 1, 0, "TextFieldDoubleValidator");
    engine.load(url);

    return app.exec();
}
