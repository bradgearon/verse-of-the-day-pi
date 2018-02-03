import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    property var verseData
    visible: true
    title: qsTr("Hello World")

    Flow {
        id: flow1
        anchors.fill: parent

        Image {
            anchors.fill: parent
            objectName: "backImage"
        }

        Image {
            anchors.fill: parent
            objectName: "foreImage"
        }
    }

}
