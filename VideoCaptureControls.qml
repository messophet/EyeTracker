import QtQuick 2.0
import QtMultimedia 5.4

FocusScope {
    property Camera camera
    property int buttonsPanelWidth: buttonPaneShadow.width
    property bool tracking : false
    id : captureControls
    signal trackingOn
    signal trackingOff

    Rectangle {
        id: buttonPaneShadow
        width: bottomColumn.width + 16
        height: parent.height
        anchors.top: parent.top
        anchors.right: parent.right
        color: Qt.rgba(0.08, 0.08, 0.08, 1)

        Column {
            anchors {
                right: parent.right
                top: parent.top
                margins: 8
            }

            id: buttonsColumn
            spacing: 8

            CameraButton {
                id: trackingButton
                text: !tracking ? "Track Eyes" : "Stop Tracking Eyes"
                visible: true
                onClicked: {
                    tracking = !tracking
                    if(tracking)
                        captureControls.trackingOn()
                    else
                        captureControls.trackingOff()
                }
            }
        }

        Column {
            anchors {
                bottom: parent.bottom
                right: parent.right
                margins: 8
            }

            id: bottomColumn
            spacing: 8

            CameraButton {
                id: quitButton
                text: "Quit"
                onClicked: Qt.quit()
            }
        }
    }
}
