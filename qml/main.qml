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
                text: qsTr("URL:")
            }

            TextField {
                id: urlText
                width: textFieldWidth;
                height: rowHeight
                selectByMouse: true
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

            TextField {
                id: threadsText
                width: textFieldWidth;
                height: rowHeight
                selectByMouse: true
                placeholderText: qsTr("4")
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
                id: searchLabelText
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
            }
        }
    }

    ScrollView {
        id: scrollViewResult
        width: 400
        height: 800
        anchors.right: parent.right
    }
}

