import QtQuick

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("ToDo List")

    property var todoList

    ListView {
        anchors.fill: parent
        anchors.margins: 8

        spacing: 3

        model: root.todoList

        delegate: Rectangle {
            implicitHeight: 32
            implicitWidth: ListView.view.width

            color: model.state === 2 ? "green" : "grey" // If a task is in done state, change the color of the background to green.

            Text {
                anchors.fill: parent
                anchors.leftMargin: 8
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                text: model.display
            }
        }
    }
}
