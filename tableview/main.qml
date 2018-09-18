import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.5
import QtQuick.Controls 1.6 as ControlsOld
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Styles 1.2

//http://doc.qt.io/qt-5/qml-qtquick-item.html#childrenRect.height-prop

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
                    //fileDialog.open();
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
                    //        width: parent.width
                    //        wrapMode: Text.WordWrap
                    text: styleData.value
                    font.family: "Inconsolata"
                    color: styleData.selected ? "black" : "black"
                }
                implicitWidth: childrenRect.width;
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

        ListView {
            id: listView
            width: 110
            height: 160
            clip: true
            orientation: ListView.Vertical
            keyNavigationWraps: true
            Layout.maximumHeight: 100
            Layout.minimumHeight: 100
            Layout.preferredHeight: 100
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    spacing: 10
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn
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
