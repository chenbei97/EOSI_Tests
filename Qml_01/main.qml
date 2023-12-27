import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    onWidthChanged: {
        titleChanged(width)
    }

    signal titleChanged(var abc); // 1.定义自己的信号
    onTitleChanged: {
        console.log("width is changed: ",abc)
    }

    // 2. 定义自己的性质
    property string mName: "" // 会自动给性质生成信号和槽函数
    onMNameChanged: {

    }

    Button {
        id: btn1
        width: 100
        height: 40
        x:100
        y: 100
        objectName: "btn1"
        background: Rectangle{
            border.color: btn1.focus? "blue":"black"; //有焦点就是蓝色
        }
        Keys.onRightPressed: {
            btn2.focus = true;
        }
    }
    Button {
        id: btn2
        width: 100
        height: 40
        x:300
        y: 100
        objectName: "btn2"
        background: Rectangle{
            border.color: btn2.focus? "blue":"black"; //有焦点就是蓝色
        }
        Keys.onLeftPressed: {
            btn1.focus = true;
        }
    }

    onActiveFocusItemChanged: {
        // 可以找到当前的焦点控件
        if (activeFocusItem)
        console.log("current focus item: ",activeFocusItem.objectName)
    }
}
