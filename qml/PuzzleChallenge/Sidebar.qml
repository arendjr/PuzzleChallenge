import QtQuick 2.0


Rectangle {
    id: sidebar

    property string mode: "erase"
    property var selectedObject: null

    function enableSaveButton() {
        saveButton.textColor = "#000000"
    }

    function onLevelLoaded() {
    }

    function onLevelUnloaded() {
        selectPopup.hide();
        templateObjectList.model = null;
    }

    color: "#ccccff"

    Rectangle {
        id: selectBox

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 20
        }
        border {
            color: "#cccc99"
            width: 2
        }
        color: "#ffffcc"
        height: 30
        radius: 5

        Text {
            anchors.centerIn: parent
            text: selectedObject ? selectedObject.name : qsTr("Select object...")
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (selectPopup.visible) {
                    selectPopup.hide();
                } else {
                    selectPopup.show();
                }
            }
        }
    }

    Rectangle {
        id: preview
        anchors {
            top: selectBox.bottom
            topMargin: 20
            left: selectBox.left
        }
        width: selectedObject ? realmView.gridSize * (selectedObject.width || 1) : 0
        height: selectedObject ? realmView.gridSize * (selectedObject.height || 1) : 0
        Image {
            anchors.fill: parent
            source: selectedObject ? realmView.imageDir() + "/" + selectedObject.sprite : ""
        }
        MouseArea {
            anchors.fill: parent
            onClicked: sidebar.mode = "place"
        }
    }

    Rectangle {
        id: eraser
        anchors {
            top: selectBox.bottom
            topMargin: 20
            left: preview.right
            leftMargin: 20
        }
        width: realmView.gridSize
        height: realmView.gridSize
        Image {
            anchors.fill: parent
            source: realmView.imageDir() + "/eraser.png"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: sidebar.mode = "erase"
        }
    }

    Rectangle {
        anchors {
            left: sidebar.mode === "place" ? preview.left : eraser.left
            top: preview.top
        }
        border {
            color: "#ff0000"
            width: 2
        }
        color: "#20ff0000"
        width: realmView.gridSize
        height: realmView.gridSize
    }

    XGNumberInput {
        id: widthInput
        anchors {
            top: eraser.bottom; topMargin: 20; left: preview.left
        }
        min: 1; max: 256
        value: realmView.currentAreaSize.width

        onValueChanged: realmView.setWidth(value)
    }

    XGNumberInput {
        id: heightInput
        anchors {
            top: widthInput.top; left: widthInput.right; leftMargin: 20
        }
        min: 1; max: 256
        value: realmView.currentAreaSize.height

        onValueChanged: realmView.setHeight(value)
    }

    XGTextInput {
        id: levelInput
        anchors {
            top: widthInput.bottom; topMargin: 20; left: widthInput.left
        }
        text: mainViewController.currentLevel
    }

    XGButton {
        id: saveButton

        anchors {
            top: levelInput.top; left: levelInput.right; leftMargin: 20
            right: parent.right; rightMargin: 20
        }
        label: qsTr("Save")
        textColor: "#777777"
        onClicked: {
            mainViewController.save(levelInput.text)
            mainView.forceActiveFocus()
            saveButton.textColor = "#777777"
        }
    }

    Rectangle {
        id: selectPopup

        anchors {
            top: selectBox.bottom; left: selectBox.left
            right: selectBox.right
        }
        border { color: "#cccc99"; width: 1 }
        color: "#ffffcc"
        height: 210
        opacity: 0.9
        radius: 5
        visible: false

        function show() {
            if (!templateObjectList.model) {
                templateObjectList.model = mainViewController.templateObjects();
            }

            this.visible = true;
        }

        function hide() {
            this.visible = false;
        }

        ListView {
            id: templateObjectList
            anchors.fill: selectPopup
            clip: true
            delegate: Text {
                anchors {
                    topMargin: index * 30
                    horizontalCenter: parent.horizontalCenter
                }
                width: selectPopup.width; height: 30
                text: modelData.name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        sidebar.selectedObject = templateObjectList.model[index]
                        sidebar.mode = "place"
                        selectPopup.hide()
                    }
                }
            }
        }
    }
}
