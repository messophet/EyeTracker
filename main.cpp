#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCamera>
#include <QQmlContext>
#include <QObject>
#include <QThread>
#include <imagechanger.h>
#include "eyetracking.h"
#include "cameraview.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<ImageChanger>("ImageChanger", 1, 0, "ImageChanger");
    qmlRegisterType<CameraView>("CameraView", 1, 0, "CameraView");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
