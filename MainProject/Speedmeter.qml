import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//It defines the speedmeter's value and style. The circle in the center has been added and the needle, the tickmarks
//and the tickmark's label have been modified to a standard circular gauge.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

CircularGauge {

    //Positioning and property settings. With the parent fill the speedmeter scales when the window is resized.
    anchors.right: parent.right
    anchors.fill: parent
    anchors.rightMargin: 10
    anchors.bottomMargin: 2
    minimumValue: 0
    maximumValue: 15
    stepSize: 0.1

    //As the modell is moving on a plane the speed is calculated from Pythagoras theorem
    value: Math.sqrt(Math.pow(app_window.speed_x, 2) + Math.pow(app_window.speed_y, 2))

    style: CircularGaugeStyle {
        labelInset: outerRadius * 0.2
        tickmarkStepSize: 1

        //Needle styling
        needle: Rectangle {
            y: outerRadius * 0.15
            implicitWidth: outerRadius * 0.03
            implicitHeight: outerRadius * 0.9
            antialiasing: true
            color: "black"
        }

        //Central round object styling
        foreground: Item {
            Rectangle {
                width: outerRadius * 0.2
                height: width
                radius: width / 2
                color: "mediumblue"
                anchors.centerIn: parent
            }
        }

        //Text style on the whole positions
        tickmarkLabel: Text {
            font.pixelSize: Math.max(6, outerRadius * 0.1)
            text: styleData.value
            color: styleData.value > 10 ? "red" : "gray"
            antialiasing: true
        }

        //Tickmark styles
        tickmark: Rectangle {
            visible: styleData.value < 80 || styleData.value % 1 == 0
            implicitWidth: outerRadius * 0.02
            antialiasing: true
            implicitHeight: outerRadius * 0.06
            color: styleData.value >= 80 ? "white" : "grey"
        }
    }
}
