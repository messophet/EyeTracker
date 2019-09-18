import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.4

import ImageChanger 1.0
import CameraView 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    id: rootWindow

    Rectangle {
        id: cameraUI

        width: parent.width
        height: parent.height

        color: "black"

        ImageChanger {
            id: imgChanger
            objectName: "imageChanger"
        }

        VideoCaptureControls {
            id: videoControls
            anchors.fill: parent
            visible: true
            onTrackingOn: { imgChanger.receiveToggleTracking() }
            onTrackingOff: { imgChanger.receiveToggleTracking() }
        }

        Connections {
            target: imgChanger
            onSendFrame: cameraView.setImage(frame)
        }

        CameraView
        {
            id: cameraView
            objectName: "cameraView"
            height: parent.height
            width: parent.width - 160
        }
    }
}
