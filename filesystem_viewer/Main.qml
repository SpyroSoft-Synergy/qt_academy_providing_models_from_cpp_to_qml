import QtQuick
import QtQuick.Controls

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Filesystem Viewer")

    property var fsModel

    TreeView {
        anchors.fill: parent
        anchors.margins: 8

        selectionModel: ItemSelectionModel {}

        model: root.fsModel

        delegate: Item {
            readonly property real indentation: 20
            readonly property real padding: 5

            // Assigned to by TreeView
            required property TreeView treeView
            required property bool isTreeNode
            required property bool expanded
            required property int hasChildren
            required property int depth

            implicitWidth: padding + label.x + label.implicitWidth + padding
            implicitHeight: label.implicitHeight * 1.5

            onExpandedChanged: indicator.rotation = (expanded ? 90 : 0)

            Label {
                id: indicator
                x: padding + (depth * indentation)
                anchors.verticalCenter: parent.verticalCenter
                visible: isTreeNode && hasChildren
                text: "▶"

                TapHandler {
                    onSingleTapped: {
                        let index = treeView.index(row, column)
                        treeView.selectionModel.setCurrentIndex(index, ItemSelectionModel.NoUpdate)
                        treeView.toggleExpanded(row)
                    }
                }
            }

            Label {
                id: label
                x: padding + (isTreeNode ? (depth + 1) * indentation : 0)
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - padding - x
                clip: true
                text: model.display
            }
        }
    }
}
