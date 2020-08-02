import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 500
    height: 500
    title: qsTr("Hello World")
   Rectangle {
       id: rect
       width:100; height:100
       color: "#000000"

       NumberAnimation on x {
           from: 0; to: 400
           duration: 3000
       }
       NumberAnimation on y{
           from: 0; to: 400
           duration: 3000
       }

       MouseArea
       {
           id: mar
           anchors.fill: parent
           onClicked: {
               if(parent.color == 'red')
                   parent.color = "#0000FF";
               else
                   parent.color = "red";
           }
       }
   }
}
