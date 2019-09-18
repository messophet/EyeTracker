#include "eyetracking.h"
#include <QDebug>
#include <QCoreApplication>

EyeTracking::EyeTracking(QObject *parent) : QObject(parent)
{
    std::string currentPath = (QCoreApplication::applicationDirPath()).toStdString() + "/xml/";
    if (!m_faceCascade.load(currentPath+FACE_CASCADE_FILE))
        qInfo() << "[-] Face model failed";
    if (!m_eyesCascade.load(currentPath+EYES_CASCADE_FILE))
        qInfo() << "[-] Eye model failed";
}

EyeTracking::~EyeTracking()
{
}

void EyeTracking::checkIfDeviceAlreadyOpened(const int device)
{
}

void EyeTracking::process()
{
    m_frameProcessed = m_frameOriginal;
    // don't process the image if eye tracking is turned off
    if (!toggleTracking)
        return;

    cv::equalizeHist(m_frameOriginal, m_frameOriginal); // enhance image contrast
    std::vector<cv::Rect> faces;
    m_faceCascade.detectMultiScale(m_frameOriginal, faces, 1.1, 2, 0, cv::Size(150, 150));

    if (faces.size() == 0) return; // no face was detected
    cv::Mat face = m_frameOriginal(faces[0]); // crop the face
    std::vector<cv::Rect> eyes;
    m_eyesCascade.detectMultiScale(face, eyes, 1.1, 2, 0, cv::Size(150, 150));

    rectangle(m_frameOriginal, faces[0].tl(), faces[0].br(), cv::Scalar(255, 0, 0), 2);
    if (!eyes.size()) return; // both eyes were not detected
    for (cv::Rect &eye : eyes)
    {
      rectangle(m_frameOriginal, faces[0].tl() + eye.tl(), faces[0].tl() + eye.br(), cv::Scalar(0, 255, 0), 2);
    }

    m_frameProcessed = m_frameOriginal;
}

void EyeTracking::receiveGrabFrame(const QImage& image)
{
    //convert QImage to cv::Mat
    cv::Mat tmp(image.height(),image.width(),CV_8UC3,(uchar*)image.bits(),image.bytesPerLine());
    cv::Mat mat;
    cv::cvtColor(tmp, mat, cv::COLORMAP_HOT);

    m_frameOriginal = mat;
    if(m_frameOriginal.empty()) return;

    //detect eyes and face
    process();

    //convert cv::Mat to QImage
    cv::Mat temp; // make the same cv::Mat
    cvtColor(m_frameOriginal, temp, cv::COLOR_BGR2RGB);
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits();

    emit sendFrame(dest);
}

void EyeTracking::receiveSetup(const int device)
{
}

void EyeTracking::receiveToggleTracking() {
    toggleTracking = !toggleTracking;
}



