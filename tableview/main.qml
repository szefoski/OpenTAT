import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.5
import QtQuick.Controls 1.6 as C
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
                    //fileDialog.open();
                    var longestLog = theModel.getLongestLog();
                    var aaa = 0;

                    //tableView.childAt(1, 0) = longestLog;
                    var t1 = tableView.currentRow;
                    var lastRow = theModel.rowCount() - 1;
                    var inde = theModel.index(lastRow, 0);
                    var tempVal = theModel.data(inde, 257);
                    theModel.setData(inde,longestLog, 257);
                    tableView.currentRow = lastRow;
                    tableView.resizeColumnsToContents();
                    theModel.setData(inde, tempVal, 257);
                    tableView.currentRow.t1;
                    var listview = authorColumn.__view.__listView;
                    var ads = 0;
                }

            }
        }
    }

    function resizeToContents() {
        var minWidth = 0
        var listdata = authorColumn.__view.__listView.children[0]
        for (var i = 0; authorColumn.__index === -1 && i < authorColumn.__view.__columns.length; ++i) {
            if (authorColumn.__view.__columns[i] === this)
                authorColumn.__index = i
        }
        // ### HACK We don't have direct access to the instantiated item,
        // so we go spelunking. Each 'item' variable check is annotated
        // with the expected object it should point to in BasicTableView.
        for (var row = 0 ; row < listdata.children.length ; ++row) {
            var item = listdata.children[row] ? listdata.children[row].rowItem : undefined
            if (item) { // FocusScope { id: rowitem }
                item = item.children[1]
                if (item) { // Row { id: itemrow }
                    item = item.children[authorColumn.__index]
                    if (item) { // Repeater.delegate a.k.a. __view.__itemDelegateLoader
                        var indent = authorColumn.__view.__isTreeView && authorColumn.__index === 0 ? item.__itemIndentation : 0
                        item  = item.item
                        if (item && item.hasOwnProperty("implicitWidth")) {
                            minWidth = Math.max(minWidth, item.implicitWidth + indent)
                        }
                    }
                }
            }
        }

        authorColumn.width = 400
        if (minWidth)
            authorColumn.width = minWidth
    }

    function resizeTableViewToContent(tableViewTarget)
    {
        for (var i = 0; i < tableViewTarget.columnCount; ++i) {
            var col = tableViewTarget.getColumn(i)
            var header = tableViewTarget.__listView.headerItem.headerRepeater.itemAt(i)
            if (col) {
                col.__index = i
                col.resizeToContents()
                if (col.width < header.implicitWidth)
                    col.width = header.implicitWidth
            }
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        C.TableView {
            id: tableView
            Layout.fillHeight: true
            Layout.fillWidth: true
            frameVisible: true
            sortIndicatorVisible: true
            selectionMode: C.SelectionMode.ExtendedSelection

            /*rowDelegate: Rectangle {
                SystemPalette {
                    id: systemPalette
                    colorGroup: SystemPalette.Active
                }
                color: {
                    //var baseColor = styleData.alternate ? systemPalette.alternateBase : systemPalette.base
                    //return styleData.selected ? "#f00" : baseColor
                    var col1 = styleData.column === 0 ? "#ff0" : "#f0f"
                    return styleData.selected ? col1 : "#0f0"
                }
            }*/
            /*
            itemDelegate: Text {
                property variant value: styleData.value
                text: styleData.value
                color: "yellow"
            }

            itemDelegate: Item {
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    color: styleData.textColor
                    elide: styleData.elideMode
                    text: styleData.value
                }
                implicitWidth: childrenRect.width;
                width: 1000;
            }
*/
            itemDelegate: Rectangle {
                //            color: "transparent"
                color: {
                    var col1 = styleData.column === 0 ? "#ff0" : "#0f0"
                    return styleData.selected ? col1 : "#0f0"
                }
                /*gradient: Gradient {
                            GradientStop {
                                position: 0.00;
                                color: styleData.selected ? "yellow" : "green";
                            }
                            GradientStop {
                                position: 0.50;
                                color: styleData.selected ? "yellow" : "green";

                            }
                            GradientStop {
                                position: 1.00;
                                color: "#ffffff";
                            }
                        }*/
                Text {
                    text: styleData.value
                    color: styleData.selected ? "blue" : "blue"
                }
                implicitWidth: childrenRect.width;
                width: 1000;
            }

            C.TableViewColumn {
                id: titleColumn
                title: "Line"
                role: "line"
                movable: false
                resizable: false
                width: 50
            }

            C.TableViewColumn {
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
