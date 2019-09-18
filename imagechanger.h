#ifndef IMAGECHANGER_H
#define IMAGECHANGER_H

#include <QObject>
#include <QVariant>
#include <QThread>
#include <QCamera>
#include "cameraframegrabber.h"
#include "eyetracking.h"

class ImageChanger : public QObject
{
    Q_OBJECT

public:
    explicit ImageChanger(QObject *parent = nullptr);
    ~ImageChanger();
    void setup();

signals:
    void sendSetup(int device);
    void sendToggleTracking();
    void sendFrame(const QImage& frame);

public slots:
    void receiveFrame(const QImage& frame);
    void receiveToggleTracking();

protected:
    QImage m_image;

private:
    QThread *m_thread;
    QCamera *m_camera;
    CameraFrameGrabber *m_cameraFrameGrabber;
//    EyeTracking *m_worker;
    QSharedPointer<EyeTracking> m_worker;
};

#endif // IMAGECHANGER_H
