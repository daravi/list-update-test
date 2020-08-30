import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1000
    height: 480
    title: qsTr("List Update Test")

    MyView
    {
        anchors.fill: parent
    }
}