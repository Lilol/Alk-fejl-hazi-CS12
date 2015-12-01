import QtQuick 2.0

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Draws a graph of the speed values. If the robot moves forward the speed value is positive, if it's moving backward
//the values are negative.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

Rectangle{
    property var graphTimestamps;
    property var graphVelocitiesX;
    property var graphVelocitiesY;
    property var graphAccelerationsX;
    property var graphAccelerationsY;

    Canvas {
        anchors.fill: parent
        onPaint: {
            var context = getContext("2d");

            context.fillStyle = "white"
            context.fillRect(0, 0, width, height);

            drawHorizontalLine(context, 0.0, "black", parent.height / 20);
            drawHorizontalLine(context, 5.0, "grey", parent.height / 20);
            drawHorizontalLine(context, -5.0, "grey", parent.height / 20);
            drawHorizontalLine(context, 10.0, "black", parent.height / 20);
            drawHorizontalLine(context, -10.0, "black", parent.height / 20);

            //Insert the printable dataset here
            drawDataset(context, graphVelocitiesX, graphVelocitiesY, "red", parent.height / 20);
            drawDataset(context, graphAccelerationsX, graphAccelerationsY, "rgba(220,110,110,1)", 5.0);
        }

        function drawHorizontalLine(context, dataValue, strokeStyle, verticalScaler)
        {
            var offset = height/2;

            context.beginPath();
            context.lineWidth = 1;
            context.strokeStyle = strokeStyle;
            // Mozgás a vonal elejére.
            context.moveTo(0, offset - verticalScaler * dataValue);
            // Vonal végére mozgás.
            context.lineTo(width, offset - verticalScaler * dataValue);
            context.stroke();
        }

        function drawDataset(context, datarowX, datarowY, strokeStyle, verticalScaler)
        {
            var offset = height/2;

            context.beginPath();
            context.lineWidth = 3;
            context.strokeStyle = strokeStyle;
            context.moveTo(0, offset-Math.sqrt(Math.pow(datarowX[0], 2) + Math.pow(datarowY[0], 2)));
            // A vektoron végigmenve behúzzuk a grafikon szakaszait.
            for(var i=0; i < graphVelocitiesX.length;i++)
            {
                context.lineTo(10*i, offset - verticalScaler * Math.sqrt(Math.pow(datarowX[i], 2) + Math.pow(datarowY[i], 2)));
            }
            context.stroke();
        }
    }
}

