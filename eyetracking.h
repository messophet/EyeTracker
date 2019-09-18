#ifndef EYETRACKING_H
#define EYETRACKING_H

#include <QObject>
#include <QImage>
#include <QCamera>

#include <opencv2/objdetect.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class EyeTracking : public QObject
{
    Q_OBJECT

private:
    cv::Mat m_frameOriginal;
    cv::Mat m_frameProcessed;
    cv::CascadeClassifier m_eyesCascade;
    cv::CascadeClassifier m_faceCascade;
    QCamera m_camera;

    bool status;
    bool toggleTracking;

    const cv::String EYES_CASCADE_FILE = "haarcascade_eye.xml";
    const cv::String FACE_CASCADE_FILE = "haarcascade_face.xml";

    void checkIfDeviceAlreadyOpened(const int device);
    void process();

public:
    explicit EyeTracking(QObject *parent = nullptr);
    ~EyeTracking();

signals:
    void sendFrame(const QImage& frameProcessed);

public slots:
    void receiveGrabFrame(const QImage& image);
    void receiveSetup(const int device);
    void receiveToggleTracking();
};

#endif // EYETRACKING_H
