#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>
#include <QQuickItem>
#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGSimpleTextureNode>

class CameraView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)

public:
    explicit CameraView(QQuickItem *parent = nullptr);
    Q_INVOKABLE void setImage(const QImage &image);
    void paint(QPainter *painter) override;
    QImage image() const;

signals:
    void imageChanged();

protected:
    QImage m_image;
};

#endif // CAMERAVIEW_H
