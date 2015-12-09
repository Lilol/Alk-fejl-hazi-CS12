import QtQuick 2.5

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This file manages the visual representation of our modell. The car modell and the background are drawn on the same
//context. The modell orientation is calculated from the speed components. The map size is 800x600.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

Canvas {
    property var position_x;
    property var position_y;
    property var speed_x;
    property var speed_y;
    property var orientation;

    id:canvas
    onPaint: {
        var context = getContext("2d");
        //Refresh the orientation
        canvas.orientation = getAngle(speed_x, speed_y, canvas.orientation);
        //The canvas should be reset as the drawCar function rotates the canvas
        context.reset();
        drawBackground(context);
        drawCar(context, position_x, position_y, 20, 40, orientation);

    }

    //Timer refreshes the whole canvas approximately with 30FPS.
    Timer {
        interval: 35;
        repeat: true;
        running: true;
        onTriggered: {
            //canvas.requestPaint();
        }
    }

    //Draw the canvas on the available space.
    function drawBackground(context)
    {
        context.fillStyle = "mediumblue";
        context.fillRect(0, 0, width, height);

        context.linewidth = 15;
        context.strokeStyle = "black";
        context.strokeRect(0, 0, width, height);
    }

    //Draws the car to the given location on the map with proper scaling
    function drawCar(context, position_x, position_y, width, length, rotation)
    {
        context.fillStyle = "orangered";
        context.translate(position_x * mapimage_outer_rectangle.width / 800, position_y * mapimage_outer_rectangle.height / 600);
        context.rotate(rotation);
        context.rect(0, 0, length * mapimage_outer_rectangle.width / 800, width * mapimage_outer_rectangle.height / 600);
        context.fill();
    }

    //This function gets the angle, and preserves the previous angle value if the car stoppes.
    function getAngle(speed_x, speed_y, previous)
    {
        var angle;

        if((float2int(speed_x) === 0) && (float2int(speed_y) !== 0)) {
            angle = Math.PI/2;
            return angle;
        }
        else if((float2int(speed_x) !== 0) && (float2int(speed_y) !== 0)) {
            angle = Math.atan2(speed_y, speed_x)
            return angle;
        }
        else if((float2int(speed_x) === 0) && (float2int(speed_y) === 0)) {
            return previous;
        }
    }

    //A fucntion to convert float to int instead of using buggy js functions
    function float2int (value) {
        return value | 0;
    }

}

