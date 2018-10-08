import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.5
import QtQuick.Controls 1.6 as ControlsOld
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Styles 1.2
import FiltersListModel 1.0

//http://doc.qt.io/qt-5/qml-qtquick-item.html#childrenRect.height-prop
//https://www.qtcentre.org/threads/65419-Custom-editable-TableView
//https://stackoverflow.com/questions/36458795/qml-retrieve-value-of-a-spinbox-used-in-a-tableview-cell
//https://stackoverflow.com/questions/39287426/how-to-set-qml-tableviewcolumn-height

ApplicationWindow {
    id: window
    width: 800
    height: 600
    visible: true
    title: "Table View Example"
    property var colors1: ["black"];

    property variant items: ["green", "orange", "blue", "yellow", "red"]
    property variant attributes: { 'color': 'red', 'width': 100 }


    header: ToolBar
    {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "Open"
                onClicked:
                {
                    //window.colors.push("black")
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

            ToolButton {
                text: "Refresh"
                onClicked:
                {

                }
            }
        }
    }

    property string ccc: "pink"
    property int count1: 0

    function getColor(patternId)
    {
        //window.colors1.
        console.log("Daniel", window.colors1.length, window.colors1[0]);
        return items[patternId]
        //return window.colors[0]
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
                id: rowLog
                property int patternId: 0
                //            color: "transparent"
                color: {
                    if (styleData.column === 0)
                    {
                        return styleData.selected ? "#ff0" : "#aaa"
                    }

                    return getColor(patternId)
                }
                Text {
                    //        width: parent.width
                    //        wrapMode: Text.WordWrap
                    text: styleData.value
                    font.family: "Inconsolata"
                    //font.pointSize: styleData.selected ? 15 : 10
                    color: styleData.selected ? "black" : "black"
                }

                Component.onCompleted: {
                    count1 = (count1 + 1) % items.length;
                    patternId = count1
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

        ControlsOld.TableView {
            id: table
            Layout.maximumHeight: 200
            Layout.minimumHeight: 200
            Layout.preferredHeight: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            signal checked(int row, int col, bool isChecked)



            ControlsOld.TableViewColumn {
                role: "Role_Active";
                title: "Active";
                width: 100

                delegate: Item {
                    Rectangle {
                        width: parent.width
                        height: parent.height
                        color: "orange"
                    }

                    CheckBox {
                        anchors.centerIn: parent
                        checked: styleData.value
                        onClicked: {
                            /* table.selection.clear();
                            table.selection.select(styleData.row);
                            table.currentRow = styleData.row;
                            table.checked(styleData.row, styleData.column, checked);
                            */
                        }
                    }
                }
            }

            ControlsOld.TableViewColumn {
                role: "Role_FontColor"
                title: "Font Color"
                width: 70

                delegate: Item {
                    Rectangle {
                        width: parent.width
                        height: parent.height
                        color: styleData.value
                    }
                }
            }

            ControlsOld.TableViewColumn {
                role: "Role_BgColor"
                title: "BG Color"
                width: 70

                delegate: ItemDelegate {
                    Rectangle {
                        id: ttt1
                        width: parent.width
                        height: parent.height
                        color: styleData.value

                    }
                    onClicked: {
                        ttt1.color = "black"
                        window.ccc = "green"
                    }
                }
            }

            ControlsOld.TableViewColumn {
                role: "Role_Pattern"
                title: "Pattern"
                width: 400

                delegate: Item {
                    Rectangle {
                        width: parent.width
                        height: parent.height
                        color: table.model.data(table.model.index(styleData.row, 0), 258)
                    }
                    Text {
                        anchors.fill: parent
                        //        width: parent.width
                        //        wrapMode: Text.WordWrap
                        text:
                        {
                            if (filtersModel !== null)
                            {
                                var index = table.model.index(styleData.row, 0)
                                var fontColor = table.model.data(index, 257)
                                var bgColor = table.model.data(table.model.index(styleData.row, 0), 258)
                                if (fontColor !== null || bgColor !== null)
                                {
                                    return "%1 ('%2' on '%3')".arg(styleData.value).arg(fontColor).arg(bgColor)
                                }
                            }
                            return "EMPTY EMPTY!!!"
                        }
                        font.family: "Inconsolata"
                        //font.pointSize: styleData.selected ? 15 : 10
                        color: table.model.data(table.model.index(styleData.row, 0), 257)

                    }
                }
            }

            ControlsOld.TableViewColumn {
                role: "Role_Hits"
                title: "Columnt3"

                delegate: Item {
                    anchors.fill: parent
                    Text{
                        anchors.fill: parent
                        id: propValue
                        text: styleData.value
                    }
                }
            }

            rowDelegate: Rectangle
            {
                height: 100
            }

            model: FiltersListModel {}


            onChecked: console.log(row, col, isChecked);
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
