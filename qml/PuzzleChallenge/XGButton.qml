import QtQuick 2.0


Rectangle {
    property string label: ""
    property string textColor: "#000000"
    signal clicked

    border { color: "#cccc99"; width: 2 }
    color: "#ffffcc"
    height: 30
    radius: 5

    Text {
        anchors.centerIn: parent
        text: parent.label
        color: parent.textColor
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
