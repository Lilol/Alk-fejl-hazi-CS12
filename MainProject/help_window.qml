import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {

    id: help_window
    title: qsTr("Help")
    minimumWidth: 500
    minimumHeight: 300
    visible: true

    Text {
        font.pointSize: 42
        text: qsTr("akarmi")
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            help_window.destroy();
        }
    }
}

