import QtQuick 2.0


Rectangle {
    id: screen

    property string preTitle: ""
    property string title: ""
    property string subTitle: ""

    anchors.fill: parent
    opacity: 0.0
    visible: false

    Behavior on opacity {
        SequentialAnimation {
            PropertyAnimation { target: screen; property: "visible"; to: "true" }
            NumberAnimation { easing.type: Easing.InQuint; duration: 400 }
            ScriptAction { script: screen.visible = (screen.opacity > 0.0) }
        }
    }

    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: title.top
        }
        font { family: title.font.family; pointSize: 26 }
        text: screen.preTitle
        visible: screen.preTitle.length > 0
    }

    Text {
        id: title

        anchors {
            top: parent.top
            topMargin: (parent.height / 2 - height) / 2
            horizontalCenter: parent.horizontalCenter
        }
        font { family: "Ubuntu"; pointSize: 42 }
        text: screen.title
        visible: screen.title.length > 0
    }

    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: title.bottom
        }
        font { family: title.font.family; pointSize: 22 }
        horizontalAlignment: Text.AlignHCenter
        lineHeight: 1.1
        text: screen.subTitle
        visible: screen.subTitle.length > 0
    }
}
