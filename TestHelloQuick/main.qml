import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.14

Window {
    id:root
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")
    onWidthChanged: {

    }

    Grid {
        id: gridlay
        rows: 8
        columns: 12
        columnSpacing: 10
        rowSpacing: 10
        Repeater {
            model: 96
            delegate: Circle{


            }
            onItemAdded: {
                var c = Math.floor(index / gridlay.columns);
                var r = index % gridlay.columns;
                var hspace = (root.width - 2*item.gap-(gridlay.columns-1)*item.space) / gridlay.columns
                var vspace = (root.height - 2*item.gap-(gridlay.rows-1)*item.space) / gridlay.rows
                var radius = hspace<=vspace?hspace/2:vspace/2;
                //item.width = radius * 2
                item.coordinate_x = c
                item.coordinate_y = r
                item.x = item.gap+r * (hspace+item.space)
                item.y = item.gap+c *(vspace+item.space)

                console.log(item.coordinate_x,item.coordinate_y);

            }
        }
    }
}
