import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color:"white"

    Rectangle {
        width: 100
        height: width
        x:100
        y:100
        id:rect1
        z:1
        color: "blue"
    }
    Rectangle {
        width: 100
        height: width
//        x:rect1.width+50
        y:150
        anchors.right: rect1.left // 和rect1的左侧对其
        anchors.rightMargin: -50 // 到别的控件的右侧距离-50
        id:rect2
        z:0
        color: "red"
    }

    Rectangle {
        width: 100
        height: width

        x:50
        anchors.top: rect2.bottom// 和rect2的底部对其
        anchors.topMargin: 50 // 到别的控件的顶部距离50
        id:rect3
        z:3
        color: "green"
        //y:250 // y的作用被anchors覆盖了
    }

    Rectangle {
        width: 100
        height: width
        id:rect4
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        //anchors.centerIn: parent.centerIn

        border.color: "black"
        radius: width/2
        gradient: Gradient {
            GradientStop {position: 0.0;  color: "#FFFE91"}
            GradientStop {position: 1.0;  color: "#34FFA0"}
        }
         //color:"yellow" // 使用渐变会把color的颜色作用覆盖
//        gradient: Gradient {
//            GradientStop { position: 0.0; color: "red" }
//            GradientStop { position: 0.33; color: "yellow" }
//            GradientStop { position: 1.0; color: "green" }
//        }
        scale: 2
        rotation: 90
        antialiasing: true
    }
}
