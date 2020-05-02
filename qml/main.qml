import QtQuick 2.13
import QtQuick.Controls  2.13

Item {
    id: mainWindow
    width: 800
    height: 800

    property int labelWidth: 90;
    property int textFieldWidth: 200
    property int rowHeight: 50
    property int textTopPadding: 20
    property int parentPadding: 20
    property int buttonWidth: 90

    Column {
        id: column
        spacing: 10
        topPadding: parentPadding
        leftPadding: parentPadding

        anchors.left: parent.left
        Row {
            height: rowHeight
            Text {
                id: urlLabel
                width: labelWidth
                height: rowHeight
                topPadding: textTopPadding
                anchors.top: parent.top
                text: "url"
            }

            TextField {
                id: urlText
                width: textFieldWidth
                text: "https://dou.ua"
                height: rowHeight
                selectByMouse: true
                validator: RegExpValidator { regExp: /(https?:\/\/(?:www\.|(?!www))[a-zA-Z0-9][a-zA-Z0-9-]+[a-zA-Z0-9]\.[^\s]{2,}|www\.[a-zA-Z0-9][a-zA-Z0-9-]+[a-zA-Z0-9]\.[^\s]{2,}|https?:\/\/(?:www\.|(?!www))[a-zA-Z0-9]+\.[^\s]{2,}|www\.[a-zA-Z0-9]+\.[^\s]{2,})/ }
                placeholderText: qsTr("https://en.cppreference.com/w/")
            }
        }

        Row {
            height: rowHeight
            Text {
                id: threadsLabel
                width: labelWidth
                height: rowHeight
                topPadding: textTopPadding
                anchors.top: parent.top
                text: qsTr("Threads:")
            }

            SpinBox {
                id: threadsText
                width: textFieldWidth;
                height: rowHeight
                value: 4
            }
        }

        Row {
            height: rowHeight
            Text {
                id: maxPages
                width: labelWidth
                height: rowHeight
                topPadding: textTopPadding
                anchors.top: parent.top
                text: qsTr("Max pages:")
            }

            TextField {
                id: maxPagesText
                width: textFieldWidth;
                height: rowHeight
                selectByMouse: true
                validator: IntValidator {bottom: 1; top: 1000}
                placeholderText: qsTr("100")
            }
        }

        Row {
            height: rowHeight
            Text {
                id: searchLabel
                width: labelWidth
                height: rowHeight
                topPadding: textTopPadding
                anchors.top: parent.top
                text: qsTr("Search string:")
            }

            TextField {
                id: searchText
                width: textFieldWidth;
                height: rowHeight
                selectByMouse: true
                placeholderText: qsTr("C++")
            }
        }

        Row {
            spacing: 10
            height: rowHeight

            Button {
                id: startButton
                width: buttonWidth
                text: qsTr("Start")
                onClicked: {
                    controller.search(urlText.text, searchText.text, threadsText.value, maxPagesText.text)
                    //console.log("prived")
                }
            }

            Button {
                id: pauseButton
                width: buttonWidth
                text: qsTr("Pause")
            }

            Button {
                id: stopButton
                width: buttonWidth
                text: qsTr("Stop")

                onClicked: {
                    controller.stop()
                }
            }
        }
    }

    Rectangle {
        width: 400
        height: 800
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.leftMargin: 20

    ScrollView {
        anchors.fill: parent
        width: 200
        height: 200

        ListView {
            model: controller.searchResult
            anchors.fill: parent
            clip: true
            delegate: Row {
                Text {
                    height: rowHeight
                    topPadding: textTopPadding
                    text: model.url
                    width: 300
                }
                Text {
                    height: rowHeight
                    topPadding: textTopPadding
                    text: model.searchResult
                }
            }

            Component.onCompleted: {
                console.log(controller.searchResult.rowCount())
            }

        }
    }
    }
}

