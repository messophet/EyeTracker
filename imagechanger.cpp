#include "imagechanger.h"
#include <QTimer>
#include <QDebug>

ImageChanger::~ImageChanger()
{
    m_thread->quit();
    while(!m_thread->isFinished());

    delete m_thread;
}

ImageChanger::ImageChanger(QObject* parent) : QObject(parent)
{
    this->setup();
}

void ImageChanger::setup()
{
    // the middleman between all things good
    m_thread = new QThread();

    m_camera = new QCamera();
    m_cameraFrameGrabber = new CameraFrameGrabber();
    m_camera->setViewfinder(m_cameraFrameGrabber);

    m_worker = new EyeTracking();

    connect(m_cameraFrameGrabber, SIGNAL(frameAvailable(QImage)), m_worker, SLOT(receiveGrabFrame(QImage)));
    connect(m_worker, SIGNAL(sendFrame(QImage)), this, SLOT(receiveFrame(QImage)));

    connect(this, SIGNAL(sendSetup(int)), m_worker, SLOT(receiveSetup(int)));
    connect(this, SIGNAL(sendToggleTracking()), m_worker, SLOT(receiveToggleTracking()));

    connect(m_thread, SIGNAL(finished()), m_worker, SLOT(deleteLater()));
    connect(m_thread, SIGNAL(finished()), m_worker, SLOT(deleteLater()));

    m_worker->moveToThread(m_thread);

    m_thread->start();
    m_camera->start();

    emit sendSetup(0);
}

void ImageChanger::receiveFrame(const QImage& frame)
{
    m_image = frame;

    emit sendFrame(m_image);
}

void ImageChanger::receiveToggleTracking()
{
    emit sendToggleTracking();
}
