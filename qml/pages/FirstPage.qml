
import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page



    SilicaListView {
        id: layout_list_view
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("App Cleaner")
        }




        model: h_cleaner.applicationList
        delegate: BackgroundItem {
            width: parent.width
            height: Theme.itemSizeMedium
            Row {
                id: row_app
                x: Theme.paddingLarge
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                height: app_icon.height
                spacing: Theme.paddingSmall

                Switch {
                    width: Theme.iconSizeExtraSmall
                    height: Theme.iconSizeMedium
                    checked: modelData.isRunning
                    automaticCheck: false
                }

                Image {
                    id: app_icon
                    width: Theme.iconSizeMedium
                    height: Theme.iconSizeMedium
                    source: modelData.IconPath
                }

                Column {
                id: column_app
                height: app_icon.height
                    Label {
                        id: label_app_name
                        wrapMode: Text.WordWrap
                        text: modelData.Name
                    }
                    Label {
                        font.pixelSize: Theme.fontSizeTiny
                        text: qsTr("Cache: ") + modelData.CacheSize
                    }

                }
            }
            function updateAppInfo() {
                app_info = modelData
            }
            onClicked: pageStack.push(Qt.resolvedUrl("ApplicationView.qml"), {app_info: modelData})

        }
        VerticalScrollDecorator {

        }
        PullDownMenu {
            MenuItem {
                text: qsTr("Refresh")
                onClicked: h_cleaner.updateList();

            }
        }

        PushUpMenu {

            MenuItem {
                text: qsTr("About")
                onClicked: pageContainer.push(Qt.resolvedUrl("SecondPage.qml"))
            }
        }
    }

    /*
    Connections {
        target: QMLCleanerClass;
        onBuildModel:{
            layout_list_view.model = data
        }
    }
    */
}
