import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This item handles the detection of key pressing and releasing. It updates the properties of the main window
//accordingly.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

Item{
    //TODO: ????
    signal accelerateXCommand;
    signal accelerateYCommand;
    signal slowDownXCommand;
    signal slowDownYCommand;

    id:key_logging
    focus: true

    Keys.onPressed: {
        if (event.key === Qt.Key_Left) {
            app_window.rotation_left = true;
            slowDownXCommand();
        }
        if (event.key === Qt.Key_Right)   {
            app_window.rotation_right = true
            accelerateXCommand();
        }
        if (event.key === Qt.Key_Up)    {
            app_window.move_forward = true
            slowDownYCommand();
        }
        if (event.key === Qt.Key_Down)    {
            app_window.move_backward = true
            accelerateYCommand();
        }
    }

    Keys.onReleased: {
        if (event.key === Qt.Key_Left) { app_window.rotation_left = false; }
        if (event.key === Qt.Key_Right)   { app_window.rotation_right = false }
        if (event.key === Qt.Key_Up)    { app_window.move_forward = false }
        if (event.key === Qt.Key_Down)    { app_window.move_backward = false }
    }
}
