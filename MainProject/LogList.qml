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
    property var acceleration_X;
    property var position_X;
    property var position_y;

    horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
    Column {
        spacing: loglist_outer_rectangle.height / 20

        Text { text: "Position X: " + position_x.toFixed(3) }
        Text { text: "Position Y: " + position_y.toFixed(3) }
        Text { text: "Speed X: " + speed_x.toFixed(3) }
        Text { text: "Speed Y: " + speed_y.toFixed(3) }
        Text { text: "Acceleration X: " + acceleration_x.toFixed(3) }
        Text { text: "Acceleration Y: " + acceleration_y.toFixed(3) }
        Text { text: "Reset pressed: " + app_window.reset }
        Text { text: "Lamp on: " + app_window.lamp }
        Text { text: "Calibrated: " + app_window.calibration }
    }
}

