import QtQuick 2.0
import nl.xiaogame.components 1.0


MainViewController {
    id: mainViewController
    width: 1024
    height: 768

    states: [
        State { name: "Start"; PropertyChanges { target: startMenu; opacity: 1.0 } },
        State { name: "Game"; PropertyChanges { target: gameView; opacity: 1.0 } },
        State { name: "Menu"; PropertyChanges { target: gameMenu; opacity: 1.0 } },
        State { name: "LevelSelection"; PropertyChanges { target: selectLevel; opacity: 1.0 } },
        State { name: "Completed"; PropertyChanges { target: gameView; opacity: 1.0 } },
        State { name: "Dead"; PropertyChanges { target: gameView; opacity: 1.0 } },
        State { name: "AllCompleted"; PropertyChanges { target: allCompletedView; opacity: 1.0 } },
        State { name: "Quit" }
    ]
    state: "Start"

    transitions: [
        Transition {
            to: "Quit"
            SequentialAnimation {
                PauseAnimation { duration: 400 }
                ScriptAction { script: Qt.quit() }
            }
        },
        Transition {
            to: "Start"
            ScriptAction { script: gameView.state = "Play"; }
        },
        Transition {
            to: "Game,Menu"
            ScriptAction { script: finishedText.hide() }
        },
        Transition {
            to: "Game"
            ScriptAction {
                script: {
                    if (gameView.state !== "Edit") {
                        mainViewController.resume();
                    }
                }
            }
        },
        Transition {
            to: "Menu"
            ScriptAction { script: mainViewController.pause(); }
        }
    ]

    Rectangle {
        id: mainView
        anchors.fill: parent
        color: "#000000"
        focus: true

        Screen {
            id: startMenu
            anchors.fill: parent
            color: "#ccccff"
            visible: true

            preTitle: qsTr("Xiao Game")
            title: qsTr("Puzzle Challenge")

            MenuItem {
                anchors.topMargin: 0
                text: qsTr("Continue Game")
                visible: mainViewController.canContinue

                onActivated: {
                    mainViewController.state = "Game";
                    mainViewController.continueGame();
                }
            }

            MenuItem {
                id: startNewGameButton
                anchors.topMargin: mainViewController.canContinue ? 60 : 0
                text: mainViewController.canContinue ? qsTr("Start New Game") : qsTr("Start Game")

                onActivated: {
                    mainViewController.state = "Game";
                    mainViewController.startNewGame();
                }
            }

            MenuItem {
                id: selectLevelButton
                anchors.topMargin: startNewGameButton.anchors.topMargin + 60
                text: qsTr("Select Level")

                onActivated: {
                    mainViewController.state = "LevelSelection"
                }
            }

            MenuItem {
                anchors.topMargin: selectLevelButton.anchors.topMargin + 60
                text: qsTr("Quit")

                onActivated: mainViewController.state = "Quit"
            }
        }

        Screen {
            id: selectLevel
            anchors.fill: parent
            color: "#ff6600"

            title: qsTr("Select Level")

            ListView {
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.verticalCenter
                    bottom: parent.bottom
                    bottomMargin: 80
                }
                clip: true

                model: mainViewController.levels
                delegate: MenuItem {
                    anchors {
                        top: parent.top
                        topMargin: index * 60
                    }
                    text: qsTr("Level ") + parseInt(modelData.substr(5, 8), 10)

                    onActivated: {
                        mainViewController.state = "Game";
                        mainViewController.startNewGame(modelData);
                    }
                }
            }

            MenuItem {
                anchors {
                    top: parent.bottom
                    topMargin: -60
                }
                text: qsTr("Cancel")

                onActivated: {
                    mainViewController.state = "Start"
                }
            }
        }

        Screen {
            id: gameMenu
            anchors.fill: parent
            color: "#ffcccc"

            title: qsTr("Paused")


            MenuItem {
                anchors.topMargin: 0
                text: qsTr("Continue Game")

                onActivated: {
                    mainViewController.state = "Game";
                }
            }

            MenuItem {
                anchors.topMargin: 60
                text: qsTr("Restart Level")

                onActivated: {
                    mainViewController.state = "Game";
                    mainViewController.restartLevel();
                }
            }

            MenuItem {
                anchors.topMargin: 120
                text: qsTr("Stop Game")

                onActivated: {
                    mainViewController.state = "Start";
                    mainViewController.stopGame();
                }
            }

            MenuItem {
                anchors.topMargin: 180
                text: qsTr("Quit")

                onActivated: mainViewController.state = "Quit"
            }
        }

        Screen {
            id: gameView

            anchors.fill: parent
            color: "#888888"

            states: [
                State {
                    name: "Play"
                    PropertyChanges { target: editView; anchors.rightMargin: -editView.width }
                },
                State {
                    name: "Edit"
                    PropertyChanges { target: editView; anchors.rightMargin: 0 }
                }
            ]
            state: "Play"

            Flickable {
                id: gameFlickable

                anchors {
                    top: parent.top; left: parent.left
                    bottom: parent.bottom; right: editView.left
                }

                contentWidth: realmView.currentAreaSize.width * realmView.gridSize
                contentHeight: realmView.currentAreaSize.height * realmView.gridSize

                Behavior on contentX {
                    NumberAnimation { easing.type: Easing.Linear; duration: 200 }
                }
                Behavior on contentY {
                    NumberAnimation { easing.type: Easing.Linear; duration: 200 }
                }

                RealmView {
                    id: realmView

                    anchors.fill: parent

                    transform: [
                        Scale {
                            id: realmViewScale
                            xScale: 1.0; yScale: 1.0

                            Behavior on xScale {
                                id: realmViewScaleXBehavior
                                NumberAnimation { easing.type: Easing.InQuart; duration: 600 }
                            }
                            Behavior on yScale {
                                id: realmViewScaleYBehavior
                                NumberAnimation { easing.type: Easing.InQuart; duration: 600 }
                            }
                        },
                        Translate {
                            id: realmViewTranslate
                            x: 0; y: 0

                            Behavior on x {
                                id: realmViewTranslateXBehavior
                                NumberAnimation { easing.type: Easing.InQuart; duration: 600 }
                            }
                            Behavior on y {
                                id: realmViewTranslateYBehavior
                                NumberAnimation { easing.type: Easing.InQuart; duration: 600 }
                            }
                        }
                    ]

                    MouseArea {
                        id: realmMouseView
                        anchors.fill: parent
                        hoverEnabled: (gameView.state === "Edit")

                        onPressed: {
                            if (gameView.state === "Edit") {
                                var gridSize = realmView.gridSize;
                                var x = Math.floor(selectionField.anchors.leftMargin / gridSize);
                                var y = Math.floor(selectionField.anchors.topMargin / gridSize);
                                if (editView.mode === "place") {
                                    realmView.placeObject(editView.selectedObject, x, y);
                                    editView.enableSaveButton();
                                } else if (editView.mode === "erase") {
                                    realmView.eraseObjects(x, y);
                                    editView.enableSaveButton();
                                }

                                gameFlickable.interactive = false;
                            }
                        }

                        onReleased: {
                            if (gameView.state === "Edit") {
                                gameFlickable.interactive = true;
                            }
                        }

                        onPositionChanged: {
                            var previousLeftMargin = selectionField.anchors.leftMargin;
                            var previousTopMargin = selectionField.anchors.topMargin;

                            var gridSize = realmView.gridSize;
                            var playerX = realmView.playerTopLeft.x;
                            var playerY = realmView.playerTopLeft.y;
                            selectionField.anchors.leftMargin =
                                    playerX + Math.floor((mouse.x - playerX) / gridSize) * gridSize;
                            selectionField.anchors.topMargin =
                                    playerY + Math.floor((mouse.y - playerY) / gridSize) * gridSize;

                            if ((mouse.buttons & Qt.LeftButton) &&
                                (previousLeftMargin !== selectionField.anchors.leftMargin ||
                                 previousTopMargin !== selectionField.anchors.topMargin)) {
                                realmMouseView.onPressed(mouse);
                            }
                        }
                    }

                    Rectangle {
                        id: selectionField
                        anchors {
                            left: parent.left
                            top: parent.top
                        }
                        border {
                            color: "#ff0000"
                            width: 2
                        }
                        color: "#20ff0000"
                        visible: gameView.state === "Edit" &&
                                 (editView.selectedObject || editView.mode === "erase")
                        width: realmView.gridSize
                        height: realmView.gridSize
                    }

                    onPlayerTopLeftChanged: {
                        positionArea();
                    }

                    function positionArea() {
                        var gridSize = realmView.gridSize;
                        var margin = 3 * gridSize;

                        if (!gameFlickable.contentWidth || !gameFlickable.contentHeight) {
                            return;
                        }

                        var newContentX = gameFlickable.contentX;
                        var width = gameFlickable.width;
                        var contentWidth = gameFlickable.contentWidth;
                        if (contentWidth < width) {
                            newContentX = -(width - contentWidth) / 2;
                        } else {
                            var playerX = playerTopLeft.x;
                            var screenX = playerX - gameFlickable.contentX;
                            if (screenX < margin) {
                                newContentX = Math.max(playerX - margin, 0);
                            } else if (screenX + gridSize > width - margin) {
                                newContentX = Math.min(playerX - width + margin + gridSize,
                                                       contentWidth - width);
                            }
                        }

                        var newContentY = gameFlickable.contentY;
                        var height = gameFlickable.height;
                        var contentHeight = gameFlickable.contentHeight;
                        if (contentHeight < height) {
                            newContentY = -(height - contentHeight) / 2;
                        } else {
                            var playerY = playerTopLeft.y;
                            var screenY = playerY - gameFlickable.contentY;
                            if (screenY < margin) {
                                newContentY = Math.max(playerY - margin, 0);
                            } else if (screenY + gridSize > height - margin) {
                                newContentY = Math.min(playerY - height + margin + gridSize,
                                                       contentHeight - height);
                            }
                        }

                        gameFlickable.contentX = newContentX;
                        gameFlickable.contentY = newContentY;
                    }
                }

                onContentWidthChanged: {
                    realmView.positionArea();
                }

                onContentHeightChanged: {
                    realmView.positionArea();
                }
            }

            Sidebar {
                id: editView
                anchors {
                    top: parent.top
                    right: parent.right
                    bottom: parent.bottom
                }
                width: 300

                Behavior on anchors.rightMargin {
                    NumberAnimation { easing.type: Easing.InQuint; duration: 400 }
                }
            }
        }

        Screen {
            id: allCompletedView
            anchors.fill: parent
            color: "#ff00ff"

            title: qsTr("Congratulations!")
            subTitle: qsTr("You have completed the final level of<br>" +
                           "<b>Xiao Game: Puzzle Challenge</b><br>" +
                           "We hope you enjoyed our puzzles!<br>" +
                           "Cheers! - Xiao Xuxu &amp; Xiao Arend")

            MenuItem {
                anchors.topMargin: 60
                text: qsTr("Back to Main Menu")

                onActivated: {
                    mainViewController.state = "Start"
                }
            }
        }

        Keys.onPressed: {
            if (event.isAutoRepeat) {
                return;
            }

            if (mainViewController.state === "Game") {
                if (event.key === Qt.Key_Up) {
                    realmView.startMove(0, -1);
                } else if (event.key === Qt.Key_Right) {
                    realmView.startMove(1, 0);
                } else if (event.key === Qt.Key_Down) {
                    realmView.startMove(0, 1);
                } else if (event.key === Qt.Key_Left) {
                    realmView.startMove(-1, 0);
                } else {
                    realmView.stopMove(0, 0);
                }

                if (event.key === Qt.Key_E && (event.modifiers & Qt.ControlModifier)) {
                    gameView.state = (gameView.state === "Play" ? "Edit" : "Play");

                    if (gameView.state === "Edit") {
                        mainViewController.pause();
                    } else {
                        mainViewController.resume();
                    }
                }

                if ((event.key === Qt.Key_R && (event.modifiers & Qt.ControlModifier)) ||
                    (event.key === Qt.Key_F5)) {
                    mainViewController.restartLevel();
                }
            } else if (mainViewController.state === "Completed") {
                mainViewController.state = "Game";
                mainViewController.startNextLevel();
                return;
            } else if (mainViewController.state === "Dead") {
                mainViewController.state = "Game";
                mainViewController.restartLevel();
                return;
            }

            if ((event.key === Qt.Key_F) &&
                (event.modifiers & Qt.ControlModifier) && (event.modifiers & Qt.ShiftModifier)) {
                mainViewController.switchFullScreen();
            }

            if (event.key === Qt.Key_Escape) {
                if (mainViewController.state === "Start") {
                    mainViewController.state = "Quit";
                } else if (mainViewController.state === "Menu") {
                    mainViewController.state = "Game";
                } else {
                    mainViewController.state = "Menu";
                }
            }
        }

        Keys.onReleased: {
            if (event.isAutoRepeat) {
                return;
            }

            if (mainViewController.state === "Game") {
                if (event.key === Qt.Key_Up) {
                    realmView.stopMove(0, -1);
                } else if (event.key === Qt.Key_Right) {
                    realmView.stopMove(1, 0);
                } else if (event.key === Qt.Key_Down) {
                    realmView.stopMove(0, 1);
                } else if (event.key === Qt.Key_Left) {
                    realmView.stopMove(-1, 0);
                }
            }
        }
    }

    Text {
        id: finishedText
        anchors.centerIn: parent
        font { family: "Ubuntu"; bold: true; pointSize: 116 }
        scale: 0.0

        Behavior on scale {
            NumberAnimation { easing.type: Easing.InQuart; duration: 600 }
        }

        function show(text, color) {
            var scale = Math.max(realmView.width / realmView.gridSize,
                                 realmView.height / realmView.gridSize) / 2;

            realmViewScale.origin.x = realmView.playerTopLeft.x;
            realmViewScale.origin.y = realmView.playerTopLeft.y;
            realmViewScale.xScale = scale;
            realmViewScale.yScale = scale;
            realmViewTranslate.x = -realmView.playerTopLeft.x / 2;
            realmViewTranslate.y = -realmView.playerTopLeft.y / 2;

            this.color = color;
            this.scale = 1.0;
            this.text = text;
        }

        function hide() {

            realmViewScale.xScale = 1.0;
            realmViewScale.yScale = 1.0;
            realmViewTranslate.x = 0;
            realmViewTranslate.y = 0;

            this.scale = 0.0;
        }
    }

    onLevelLoaded: {
        editView.onLevelLoaded()
    }

    onLevelUnloaded: {
        editView.onLevelUnloaded()
    }

    onLevelCompleted: {
        finishedText.show(qsTr("Awesome!"), "#ff00ff");

        mainViewController.state = "Completed";
    }

    onPlayerDied: {
        finishedText.show(qsTr("You died!"), "#ff0000");

        mainViewController.state = "Dead";
    }

    onPlayerDrowned: {
        finishedText.show(qsTr("You drowned!"), "#0000ff");

        mainViewController.state = "Dead";
    }

    onAllLevelsCompleted: {
        mainViewController.state = "AllCompleted"
    }
}
