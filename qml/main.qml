import QtQuick 2.13
import QtQuick.Controls  2.13

Item {
    id: mainWindow
    width: 1000
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
        anchors.top: parent.top
        Row {
            height: rowHeight
            Text {
                id: urlLabel
                width: labelWidth
                height: rowHeight
                topPadding: textTopPadding
                anchors.top: parent.top
                text: qsTr("URL")
            }

            TextField {
                id: urlText
                width: textFieldWidth
                text: "https://ru.wikipedia.org/wiki/C%2B%2B"
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
                text: "15"
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
                text: "class"
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
                    controller.start(urlText.text, searchText.text, threadsText.value, maxPagesText.text)
                }
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
        width: 3 * textFieldWidth;
        height: 800
        anchors.left: column.right
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.leftMargin: 20

    ScrollView {
        anchors.fill: parent


        ListView {
            model: controller.searchResult
            anchors.fill: parent
            clip: true
            delegate: Rectangle {
                    width: 3 * textFieldWidth;
                    height: rowHeight
                    color: index % 2 == 0 ? "white" : "#d3d3d3"
                    border.color: "grey"

                    Row {
                        spacing: 1
                        TextArea {
                            text: model.url
                            width: 2 * textFieldWidth;
                            height: rowHeight
                        }

                        TextArea {
                            text: model.searchResult
                            width: textFieldWidth;
                            height: rowHeight
                        }
                    }
                }
            }
        }
    }
}

