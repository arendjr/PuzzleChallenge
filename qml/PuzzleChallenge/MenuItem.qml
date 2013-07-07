import QtQuick 2.0


Rectangle {
    property string text

    signal activated

    anchors {
        top: parent.verticalCenter
        horizontalCenter: parent.horizontalCenter
    }
    border {
        color: "#0000ff"
        width: 2
    }
    color: "#3333ff"
    height: 40
    width: parent.width / 2

    MouseArea {
        anchors.fill: parent

        onClicked: {
            parent.anchors.leftMargin = -parent.parent.width
            parent.anchors.rightMargin = parent.parent.width
            parent.activated()
        }
    }

    Behavior on anchors.leftMargin {
        SequentialAnimation {
            NumberAnimation { easing.type: Easing.InQuint; duration: 300 }
            PauseAnimation { duration: 100 }
            PropertyAnimation { to: parent.parent.parent.width / 4 }
        }
    }
    Behavior on anchors.rightMargin {
        SequentialAnimation {
            NumberAnimation { easing.type: Easing.InQuint; duration: 300 }
            PauseAnimation { duration: 100 }
            PropertyAnimation { to: parent.parent.parent.width / 4 }
        }
    }

    Text {
        anchors.centerIn: parent
        color: "#ff8800"
        font {
            bold: true
            family: "Ubuntu"
            pointSize: 18
        }
        text: parent.text
    }
}
