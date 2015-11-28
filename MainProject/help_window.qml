import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This window appears after the Help was pressed from the Menu in the toolbar. It contains a minimal description on
//the GUI usage. The window closes itself uppon clicking on it's area.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

ApplicationWindow {

    id: help_window
    title: qsTr("Help")
    minimumWidth: 600
    minimumHeight: 300
    maximumHeight: minimumHeight
    maximumWidth: minimumWidth
    visible: true

    Text {
        textFormat: Text.RichText
        anchors.centerIn: parent
        text: "<p style='text-align: center;'><span style='font-size:20px;'><strong>Help Window</strong></span></p>"+
          "<ul>"+
          "<ul>"+
          "<li style='text-align: justify;'>If you click on this window it will collapse itself.&nbsp;</li>"+
          "<li style='text-align: justify;'>In the menu you can reach the help window or exit the application. <br> You can reach it with alt + the underlined character from the wished function.</li>"+
          "<li style='text-align: justify;'>On the left size of the window you can see the most important parameters of the robot.</li>"+
          "<li style='text-align: justify;'>On the right side of the application you can see the visual representation of a map with a car on it.<br> You can control it with the arrow keys.</li>"+
          "<li style='text-align: justify;'>Below the parameter list, you can see the histogram of the most recent speed values.</li>"+
          "<li style='text-align: justify;'>Below the map the speedmeter shows the car&#39;s speed value</li>"+
          "<li style='text-align: justify;'>Next to the speedmeter there are 3 buttons: &nbsp;the top one turns on the lamp,<br> the second one resets the modell to the center of the map and sets every value to the default, <br> and the third one initiates the calibration.</li>"+
          "</ul>"

    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            help_window.destroy();
        }
    }
}
