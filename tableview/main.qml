import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.5
import QtQuick.Controls 1.6 as ControlsOld
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Styles 1.2

ApplicationWindow {
    id: window
    width: 800
    height: 600
    visible: true
    title: "Table View Example"

    header: ToolBar
    {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "Open"
                onClicked:
                {
                    tableView.model = theModel;
                    fileDialog.open();
                    var longestLog = theModel.getLongestLog();
                    var lastSelectedRow = tableView.currentRow;
                    var lastRow = theModel.rowCount() - 1;
                    var lastRowIndex = theModel.index(lastRow, 0);
                    var tempVal = theModel.data(lastRowIndex, 257);
                    theModel.setData(lastRowIndex, longestLog, 257);
                    tableView.currentRow = lastRow;
                    tableView.resizeColumnsToContents();
                    theModel.setData(lastRowIndex, tempVal, 257);
                    tableView.currentRow = lastSelectedRow;
                }
            }
        }
    }

    ColumnLayout {
        id: columnLayout
        spacing: 0
        anchors.fill: parent

        ControlsOld.TableView {
            id: tableView
            Layout.fillHeight: true
            Layout.fillWidth: true
            frameVisible: true
            sortIndicatorVisible: true
            selectionMode: ControlsOld.SelectionMode.ExtendedSelection

            itemDelegate: Rectangle {
                //            color: "transparent"
                color: {
                    if (styleData.column === 0)
                    {
                       return styleData.selected ? "#ff0" : "#aaa"
                    }
                    return "#fff"
                }
                Text {
                    text: styleData.value
                    font.family: "Inconsolata"
                    color: styleData.selected ? "black" : "black"
                }
                implicitWidth: childrenRect.width;
                width: 1000;
            }

            ControlsOld.TableViewColumn {
                id: titleColumn
                title: "Line"
                role: "line"
                movable: false
                resizable: false
                width: 50
            }

            ControlsOld.TableViewColumn {
                id: authorColumn
                title: "Text"
                role: "text"
                movable: false
                resizable: false
                //width:
            }

        }

        Rectangle {
            id: rectangle
            width: 200
            height: 200
            color: "#19b329"
            Layout.maximumHeight: 50
            Layout.minimumHeight: 50
            Layout.preferredHeight: 50
            Layout.fillHeight: true
            Layout.fillWidth: true

            Button {
                id: button2
                x: 246
                y: 8
                text: qsTr("Button")

                onClicked:
                {
                    //fileDialog.open();
                    var listview = authorColumn.__view.__listView;
                    var row = tableView.currentRow;
                    tableView.currentRow = 0;
                    var ads = 0;
                }
            }
        }


    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            tableView.model = theModel;
            resizeTableViewToContent(tableView);
            //Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            //Qt.quit()
        }
        //Component.onCompleted: visible = true
    }

}
