#include "imagechanger.h"
#include <QDebug>

ImageChanger::~ImageChanger()
{
    m_thread->quit();
    m_thread->wait();

    delete m_thread;
}

ImageChanger::ImageChanger(QObject* parent) : QObject(parent)
{
    this->setup();
}

void ImageChanger::setup()
{
    // the middleman between all things good
    m_thread = new QThread(this);
    m_camera = new QCamera(this);
    m_cameraFrameGrabber = new CameraFrameGrabber(this);
    m_camera->setViewfinder(m_cameraFrameGrabber);

    m_worker = QSharedPointer<EyeTracking>(new EyeTracking, &QObject::deleteLater);
//    m_worker = new EyeTracking();

    connect(m_cameraFrameGrabber, SIGNAL(frameAvailable(QImage)), m_worker.data(), SLOT(receiveGrabFrame(QImage)));
    connect(m_worker.data(), SIGNAL(sendFrame(QImage)), this, SLOT(receiveFrame(QImage)));
    connect(this, SIGNAL(sendSetup(int)), m_worker.data(), SLOT(receiveSetup(int)));
    connect(this, SIGNAL(sendToggleTracking()), m_worker.data(), SLOT(receiveToggleTracking()));
//    connect(m_thread, SIGNAL(finished()), m_worker.data(), SLOT(deleteLater()));

    m_worker->moveToThread(m_thread);
    m_camera->start();
    m_thread->start();

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
