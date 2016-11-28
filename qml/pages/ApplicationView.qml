import QtQuick 2.2
import Sailfish.Silica 1.0

Page {
    property var app_info
    property string app_str_running: "Off"
    property bool havecache: false
    property bool haveconfig: false
    property bool app_running: false


    function updateValues() {
        console.log("QML_UPDATE_VALUES START")
        app_running = h_cleaner.checkRunApp(app_info.Path)
        if (app_running == true)
            app_str_running = "ON"
        else app_str_running = "OFF"


        haveconfig = h_cleaner.checkConfig(app_info.Path)


        if (app_info.CacheSize <= 0) havecache = false
        else havecache = true;
        // Пока костыль
        label_cache.text = app_info.CacheSize

        console.log("QML_UPDATE_VALUES STOP. Value: " + app_info.CacheSize)
    }

    Component.onCompleted: {
        updateValues();
    }
    Column {
        width: parent.width - Theme.itemSizeMedium
        spacing: Theme.paddingLarge
        anchors.horizontalCenter: parent.horizontalCenter
        PageHeader { title: app_info.Name}

        Image {
            id: app_big_icon
            anchors.horizontalCenter: parent.horizontalCenter
            width: Theme.iconSizeExtraLarge
            height: Theme.iconSizeExtraLarge
            source: app_info.IconPath
        }

        Separator {
            width: parent.width
            anchors.margins: Theme.paddingLarge
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            color: Theme.secondaryHighlightColor
        }
        Row {
            width: parent.width
            spacing: Theme.paddingSmall

            Label {
                width: parent.width * 0.7
                text: "STATUS:"
            }
            Label {
                width: parent.width * 0.3
                text: app_str_running
            }
        }
        Row {
            width: parent.width
            spacing: Theme.paddingSmall

            Label {
                width: parent.width * 0.7
                text: "Modify: "
            }
            Label {
                width: parent.width * 0.3
                text: app_info.DateCreate
            }
        }

        Row {
            width: parent.width
            spacing: Theme.paddingSmall

            Label {
                width: parent.width * 0.7
                text: "Cache size: "
            }
            Label {
                id: label_cache
                width: parent.width * 0.3
                text: app_info.CacheSize
            }
        }

        Row {
            width: parent.width
            spacing: Theme.paddingSmall

            Label {
                width: parent.width * 0.7
                text: "App size:"
            }
            Label {
                width: parent.width * 0.3
                text: app_info.AppSize
            }
        }

        Separator {
            width: parent.width
            anchors.margins: Theme.paddingLarge
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            color: Theme.secondaryHighlightColor
        }


        Button {

            width: parent.width * 0.7
            text: qsTr("Force stop")
            enabled: app_running
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                onClicked: pageStack.pop(undefined, PageStackAction.Animated)
                h_cleaner.stopApp(app_info.Path)
                //updateValues()
            }
        }
        Button {
            width: parent.width * 0.7
            text: qsTr("Clear cache")
            anchors.horizontalCenter: parent.horizontalCenter
            enabled: havecache
            onClicked: {
                onClicked: pageStack.pop(undefined, PageStackAction.Animated)
                h_cleaner.removeCache(app_info.Path)
                //updateValues()
            }
        }
        Button {
            width: parent.width * 0.7
            text: qsTr("Clear settings")
            enabled: haveconfig;
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                onClicked: pageStack.pop(undefined, PageStackAction.Animated)
                h_cleaner.removeConfig(app_info.Path)
            }
        }

    }
}
