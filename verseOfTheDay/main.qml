import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Window {
    property var verseData
    visible: true
    title: qsTr("verse of the day")

    Image {
        anchors.fill: parent
        source: verseData.backgroundImage
    }

    Image {
        id: image
        anchors.fill: parent
        source: verseData.foregroundImage
    }

    Button {
        visible: verseData.canGoBack
        text: qsTr("<--")
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 24
        anchors.bottomMargin: 16
        onClicked: {
            verseData.selectedDay++;
        }
    }

    Button {
        visible: verseData.canGoForward
        text: qsTr("-->")
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 24
        anchors.bottomMargin: 16
        onClicked: {
            verseData.selectedDay--;
        }
    }



}
