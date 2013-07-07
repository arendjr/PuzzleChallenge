import QtQuick 2.0


Rectangle {
    id: numberInput

    property int value: 0
    property int min: 0
    property int max: 9999

    border { color: "#cccc99"; width: 2 }
    height: 30; width: 100

    onValueChanged: textInput.text = value

    TextInput {
        id: textInput

        anchors {
            top: parent.top; left: parent.left
            bottom: parent.bottom; right: parent.right; rightMargin: 20
        }

        horizontalAlignment: TextInput.AlignHCenter
        validator: IntValidator { bottom: numberInput.min; top: numberInput.max }
        verticalAlignment: TextInput.AlignVCenter

        onTextChanged: parent.value = parseInt(text, 10)
    }

    Rectangle {
        anchors {
            top: parent.top; topMargin: 2
            bottom: parent.verticalCenter; right: parent.right; rightMargin: 2
        }
        border { color: "#cccc99"; width: 1 }
        width: 20

        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: "+"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (numberInput.value < numberInput.max) {
                    numberInput.value++;
                }
            }
        }
    }

    Rectangle {
        anchors {
            top: parent.verticalCenter
            bottom: parent.bottom; bottomMargin: 2; right: parent.right; rightMargin: 2
        }
        border { color: "#cccc99"; width: 1 }
        width: 20

        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: "-"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (numberInput.value > numberInput.min) {
                    numberInput.value--;
                }
            }
        }
    }
}
