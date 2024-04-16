import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Spreadsheet")

    property var spreadsheet

    HorizontalHeaderView {
        id: horizontalHeader
        anchors.left: tableView.left
        anchors.top: parent.top
        syncView: tableView
        clip: true
    }

    VerticalHeaderView {
        id: verticalHeader
        anchors.top: tableView.top
        anchors.left: parent.left
        syncView: tableView
        clip: true
    }

    TableView {
        id: tableView
        anchors.left: verticalHeader.right
        anchors.top: horizontalHeader.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        clip: true
        columnSpacing: 1
        rowSpacing: 1

        selectionModel: ItemSelectionModel {}

        model: root.spreadsheet

        delegate: Rectangle {
            implicitWidth: txt.implicitWidth
            implicitHeight: 32

            border.width: 1

            Text {
                id: txt
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                leftPadding: 8
                rightPadding: 8
                text: display
                verticalAlignment: Text.AlignVCenter
            }

            TableView.editDelegate: TextField {
                implicitWidth: txt.implicitWidth
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                text: display
                verticalAlignment: Text.AlignVCenter
                Component.onCompleted: selectAll()

                TableView.onCommit: {
                    display = text // Calls setData() function of the underlying model.
                }
            }
        }
    }

    footer: Row {
        Button {
            text: "Hide Last Row"
            onClicked: {
                Spreadsheet.removeRows(tableView.rows - 1, 1);
            }
        }
        Button {
            text: "Show Row At The Bottom"
            onClicked: {
                Spreadsheet.insertRows(tableView.rows, 1);
            }
        }
    }
}
