import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4


/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The main window of the application. It is rescalable, and the content is scaling with it.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

ApplicationWindow {

    id: app_window
    title: qsTr("Simulator GUI")
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    color: "beige"

    //Properties of the robot
    property bool reset: false
    property bool lamp: false
    property bool calibration: false

    property bool rotation_left: false
    property bool rotation_right: false
    property bool move_forward: false
    property bool move_backward: false

    property real position_x: 400
    property real position_y: 300
    property real speed_x: 0
    property real speed_y: 0
    property real acceleration_x: 0
    property real acceleration_y: 0

    //Menubar
    menuBar: MenuBar
    {
        Menu{
            title: qsTr("&Menu")
            MenuItem{
                text: qsTr("&Help")
                onTriggered:{
                    var component = Qt.createComponent("help_window.qml")
                    var window = component.createObject(app_window, {color: app_window.color})
                    window.show()
                }
            }

            MenuItem{
                text: qsTr("&Exit")
                onTriggered: Qt.quit();
            }
        }

        //Style of the menu
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
    //Buttons and speedmeter
    Row{
        height: parent.height * 0.3
        width: parent.width * 0.4
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        layoutDirection: Qt.RightToLeft

        Rectangle {
            id: speed_meter_outer_rectangle
            height: parent.height
            width: parent.width * 0.7
            color: app_window.color
            visible: true

            SpeedMeter {

            }
        }

        Rectangle {
            id: button_outer_rectangle
            height: parent.height
            width: 100
            color: app_window.color
            visible: true

            Buttons {

            }
        }
    }

    //Visual representation of the model and the map
    MapImage {
        id: mapimage_outer_rectangle
        width: parent.width * 0.6
        height: parent.height * 0.65
        anchors.right: parent.right
        anchors.top: parent.top

    }

    //Handling the input keys
    KeyHandler {
        id: keyhandlercontrol
    }

    //Loglist
    Rectangle {
        id: loglist_outer_rectangle
        anchors.left: parent.left
        anchors.right: mapimage_outer_rectangle.left
        height: mapimage_outer_rectangle.height
        color: app_window.color
        LogList {
            anchors.fill: parent
            anchors.topMargin: parent.height * 0.1
            anchors.bottomMargin: parent.height * 0.1
            anchors.leftMargin: parent.width * 0.3
            anchors.rightMargin: parent.width * 0.3
            }
    }

    //Graph
    HistoryGraph {
        width: parent.width * 0.5
        height: parent.height * 0.3
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        //It can be buggy, if the window crashes, delete this line
        anchors.bottomMargin: 3
    }
}

