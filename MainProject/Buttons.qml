import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This file contains the pressbuttons. Each button change their appererance when pressed. Upon clicking they trigger
// the proper signal.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

Column {
    signal resetCommand;
    signal stopCommand;
    signal testCommand;
    //signal lampCommand;

    anchors.right: parent.right
    anchors.verticalCenter: parent.verticalCenter
    spacing: parent.parent.height/30
    Button {
        text: "Lamp"
        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                }
            }
        }
        //onClicked: lampCommand();
    }
    Button {
        text: "Reset"
        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                }
            }
        }
        onClicked: resetCommand();
    }
    Button {
        text: "Test"
        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                }
            }
        }
        onClicked: testCommand();
    }
}

