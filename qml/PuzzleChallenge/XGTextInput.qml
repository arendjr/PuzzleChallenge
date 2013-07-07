import QtQuick 2.0


Rectangle {
    property string text: ""

    border {
        color: "#cccc99"
        width: 2
    }
    height: 30; width: 150

    onTextChanged: textInput.text = text

    TextInput {
        id: textInput

        anchors.fill: parent
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter

        onTextChanged: parent.text = text
    }
}
