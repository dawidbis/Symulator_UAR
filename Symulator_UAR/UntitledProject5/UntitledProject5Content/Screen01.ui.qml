

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.5
import QtQuick.Controls 6.5
import UntitledProject5

Rectangle {
    width: Constants.width
    height: Constants.height
    color: "#212121"

    Grid {
        id: grid
        x: 320
        y: 0
        width: 960
        height: 960
        columns: 2
        rows: 2

        Rectangle {
            id: rectangle
            width: 480
            height: 480
            color: "#000000"
        }

        Rectangle {
            id: rectangle1
            width: 480
            height: 480
            color: "#000000"
        }

        Rectangle {
            id: rectangle2
            width: 480
            height: 480
            color: "#000000"
        }

        Rectangle {
            id: rectangle3
            width: 480
            height: 480
            color: "#000000"
        }
    }

    Grid {
        id: grid1
        x: 0
        y: 0
        width: 320
        height: 960
        columns: 1
        rows: 4

        Rectangle {
            id: rectangle4
            width: 320
            height: 240
            color: "#00a33737"
            border.color: "#013d00"
            border.width: 2

            Text {
                id: text1
                x: 114
                y: 8
                width: 92
                height: 16
                color: "#ffffff"
                text: qsTr("GENERATOR")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true
            }

            Rectangle {
                id: rectangle7
                x: 68
                y: 30
                width: 185
                height: 49
                color: "#00ffffff"

                RoundButton {
                    id: roundButton1
                    x: 0
                    y: 0
                    width: 49
                    height: 49
                    icon.height: 512
                    icon.width: 512
                    icon.color: "#00ffffff"
                    icon.source: "../../../../Desktop/1_zadanie-cropped.png"
                }

                RoundButton {
                    id: roundButton
                    x: 136
                    y: 0
                    width: 49
                    height: 49
                    text: ""
                    icon.height: 512
                    icon.width: 512
                    icon.color: "#00ffffff"
                    icon.source: "../../../../Desktop/symbol-ac-source-sinusoid-icon-stock-vector-30029329.jpg"
                    layer.enabled: false
                }

                RoundButton {
                    id: roundButton2
                    x: 68
                    y: 0
                    width: 49
                    height: 49
                    icon.height: 512
                    icon.width: 512
                    icon.color: "#00ffffff"
                    icon.source: "../../../../Desktop/prosto.png"
                }
            }
        }

        Rectangle {
            id: rectangle5
            width: 320
            height: 240
            color: "#002a0101"
            border.color: "#013d00"
            border.width: 2

            Text {
                id: text2
                x: 96
                y: 8
                width: 128
                height: 16
                color: "#ffffff"
                text: qsTr("REGULATOR PID")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true
            }
        }

        Rectangle {
            id: rectangle6
            width: 320
            height: 240
            color: "#002a0101"
            border.color: "#013d00"
            border.width: 2

            Text {
                id: text3
                x: 109
                y: 8
                width: 103
                height: 16
                color: "#ffffff"
                text: qsTr("MODEL ARX")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true
            }
        }

        Rectangle {
            id: rectangle10
            width: 320
            height: 240
            color: "#002a0101"
            border.color: "#013d00"
            border.width: 2

            Text {
                id: text4
                x: 77
                y: 8
                width: 167
                height: 16
                color: "#ffffff"
                text: qsTr("USTAWIENIA SYMULACJI")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true
            }
        }
    }
}
