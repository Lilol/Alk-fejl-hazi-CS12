import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Shows the actual properties of the robot.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

ScrollView {
    property var speed_x;
    property var speed_y;
    property var acceleration_y;
    property var acceleration_x;
    property var position_x;
    property var position_y;
    property var list_s;
    property var lamp;

    horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
    Column {
        spacing: loglist_outer_rectangle.height / 20

        Text { text: "State: " +  ( currentState!=null ? currentState.statusName : "?")  }
        Text { text: "Position X: " +  ( currentState!=null ? position_x.toFixed(3) : "?")  }
        Text { text: "Position Y: " + ( currentState!=null ? position_y.toFixed(3) : "?") }
        Text { text: "Speed X: " + ( currentState!=null ? speed_x.toFixed(3) : "?") }
        Text { text: "Speed Y: " + ( currentState!=null ? speed_y.toFixed(3) : "?") }
        Text { text: "Acceleration X: " + ( currentState!=null ? acceleration_x.toFixed(3) : "?") }
        Text { text: "Acceleration Y: " + ( currentState!=null ? acceleration_y.toFixed(3) : "?") }
        Text { text: "Reset pressed: " + app_window.reset }
        Text { text: "Lamp on: " + ( currentState!=null ? lamp : "?") }
        Text { text: "Calibrated: " + app_window.calibration }
        Text { text: "Top wall distance: " + ( currentState!=null ? list_s[0].toFixed(3) : "?") }
        Text { text: "Bottom wall distance: " + ( currentState!=null ? list_s[2].toFixed(3) : "?") }
        Text { text: "Left wall distance: " + ( currentState!=null ? list_s[3].toFixed(3) : "?") }
        Text { text: "Right wall distance: " + ( currentState!=null ? list_s[1].toFixed(3) : "?") }
    }
}

