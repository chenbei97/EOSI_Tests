import QtQuick 2.0

Item {
    id:root
    signal mouseClicked
    signal mouseReleased

    property int coordinate_x: -1
    property int coordinate_y: -1

    property int radius : circle.width
    property int gap: 20
    property int space: 20

    Rectangle {
        id: circle
        width: 50
        height: width
        color: "white"
        border.color: "black"
        opacity: 0.5
        x:0
        y:0
        clip: true
        radius: width/2
//        onWidthChanged: {
//            radius = width/2
//            height = width
//        }

        MouseArea {
            anchors.fill : parent
            onPressed: {
                root.mouseClicked()
                circle.color = "green"
            }

            onReleased: {
                root.mouseReleased()
                circle.color = "white"
            }
        }
    }
}
