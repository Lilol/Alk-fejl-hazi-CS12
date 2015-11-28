import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Shows the actual properties of the robot.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

ScrollView {
    horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
    Column {
        spacing: loglist_outer_rectangle.height / 20

        Text { text: "Position X: " + app_window.position_x.toFixed(3) }
        Text { text: "Position Y: " + app_window.position_y.toFixed(3) }
        Text { text: "Speed X: " + app_window.speed_x.toFixed(3) }
        Text { text: "Speed Y: " + app_window.speed_y.toFixed(3) }
        Text { text: "Acceleration X: " + app_window.acceleration_x.toFixed(3) }
        Text { text: "Acceleration Y: " + app_window.acceleration_y.toFixed(3) }
        Text { text: "Reset pressed: " + app_window.reset }
        Text { text: "Lamp on: " + app_window.lamp }
        Text { text: "Calibrated: " + app_window.calibration }
    }
}

