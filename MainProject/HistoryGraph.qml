import QtQuick 2.0

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Draws a graph of the speed values. If the robot moves forward the speed value is positive, if it's moving backward
//the values are negative.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

Rectangle{
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
            //drawDataset(context, graphVelocities, "red", parent.height / 20);
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

        function drawDataset(context, datarow, strokeStyle, verticalScaler)
        {
            var offset = height/2;

            context.beginPath();
            context.lineWidth = 3;
            context.strokeStyle = strokeStyle;
            context.moveTo(0, offset-datarow[0]);
            // A vektoron végigmenve behúzzuk a grafikon szakaszait.
            for(var i=0; i<graphVelocities.length;i++)
            {
                context.lineTo(10*i, offset - verticalScaler * datarow[i]);
            }
            context.stroke();
        }
    }
}

