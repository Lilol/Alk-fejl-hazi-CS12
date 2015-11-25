import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4


/**
* Main window of the application
*
*/
ApplicationWindow {

    id: app_window
    title: qsTr("Simulator GUI")
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    color: "beige"

    /*Global variables*/
    property real speed
    property var guiState: { "rotation_left": false,
                             "rotation_right": false,
                             "move_forward": false,
                             "move_backward": false,
                             "reset": false,
                             "lamp": false,
                             "calibration": false,
                             "position_x": 0.0,
                             "position_y": 0.0,
                             "speed_x": 0.0,
                             "speed_y": 0.0,
                             "acceleration_x": 0.0,
                             "acceleration_y": 0.0};

    menuBar: MenuBar
    {
        Menu{
            title: qsTr("&Menu")
            MenuItem{
                text: qsTr("&Help")
                onTriggered:{
                    var component = Qt.createComponent("help_window.qml")
                    var window = component.createObject(app_window, {color: "beige"})
                    window.show()
                }
            }

            MenuItem{
                text: qsTr("&Exit")
                onTriggered: Qt.quit();
            }
        }

        //szinezős móka
        style: MenuBarStyle{
            background: Rectangle{
                color: "springgreen"
            }
            menuStyle: MenuStyle {
                frame: Rectangle {
                    color: "springgreen"
                }
            }
        }
    }

    Rectangle {
        id: speed_meter_outer_rectangle
        height: parent.height / 3
        width: parent.height / 3
        anchors{
            bottom: parent.bottom
            right: parent.right
        }
        color: "beige"
        visible: true

        SpeedMeter {

        }
    }
    Rectangle {
        id: button_outer_rectangle
        height: parent.height / 3
        width: parent.height / 3
        anchors{

        }
        color: "beige"
        visible: true

        Buttons {

        }
    }

    Text {
        text: qsTr("asd")
        anchors.centerIn: parent
    }

    KeyHandler {
        id: keyhandlercontrol
    }
}



