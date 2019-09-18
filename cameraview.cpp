#include "cameraview.h"

CameraView::CameraView(QQuickItem *parent)
{
    this->m_image = QImage(":/images/kenny.png");
}

void CameraView::paint(QPainter *painter)
{
    QRectF bounding_rect = boundingRect();
    QImage scaled = this->m_image.scaledToHeight(bounding_rect.height());
    QPointF center = bounding_rect.center() - scaled.rect().center();

    if(center.x() < 0)
        center.setX(0);
    if(center.y() < 0)
        center.setY(0);
    painter->drawImage(center, scaled);
}

QImage CameraView::image() const
{
    return this->m_image;
}

void CameraView::setImage(const QImage &image)
{
    this->m_image = image;
    update();
}
