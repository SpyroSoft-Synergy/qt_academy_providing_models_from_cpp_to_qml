import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("SQLModel")

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

        model: SQLModel

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

                text: displayText
                verticalAlignment: Text.AlignVCenter
                Component.onCompleted: selectAll()

                TableView.onCommit: {
                    let index = TableView.view.index(row, column)
                    TableView.view.model.setData(index, text, Qt.EditRole)
                }
            }
        }
    }
}
