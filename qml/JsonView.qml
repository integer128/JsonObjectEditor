import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.15
//import TextFieldDoubleValidator 1.0

ScrollView {
    id: scrollview
    anchors.fill: parent
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    ListView {
        id: listView
        width: root.width
        model: jsonmodel

        delegate: ItemDelegate {
            height: 60
            width: root.width

            RowLayout {
                anchors.fill: parent

                Label {
                    id: key_field
                    Layout.preferredWidth: parent.width / 2
                    Layout.preferredHeight: parent.height

                    background: RowLayout {
                        anchors.fill: parent

                        Label {
                            Layout.alignment: Qt.AlignCenter
                            text: key
                        }
                    }
                }

                Control {
                    id: value_field

                    //для предотвращения зацикливания при биндинге
                    property string valueBind: type == 1 ? value_chb.checked : value_tf.text

                    Layout.preferredWidth: parent.width / 2
                    Layout.alignment: Qt.AlignCenter

                    background: RowLayout {
                        anchors.fill: parent

                        CheckBox {
                            id: value_chb
                            Layout.alignment: Qt.AlignCenter
                            visible: type == 1 ? true : false
                            checked: value == 1 ? true : false
                            Material.accent: Material.Green
                        }

                        TextField {
                            id: value_tf
                            Layout.alignment: Qt.AlignCenter
                            text: value
                            visible: type == 2 || type == 3 ||
                                     type == 6 || type == 10 ? true : false

                            Material.accent: acceptableInput ? Material.Green : Material.Red
                            Material.foreground: acceptableInput ? Material.Green : Material.Red

                            validator: {
                                if (type == 2 || type == 3) {
                                    intValidator
                                } else if (type == 6) {
                                    doubleValidator
                                } else {
                                    regExpValidator
                                }
                            }
                        }

                        IntValidator {
                            id: intValidator
                        }

                        /* DoubleValidator и кастомизированные валидаторы (TextFieldDoubleValidator)
                            зависимы от языкового пакета установленной ОС. На английской версии
                            проблем с валидацией не целочисленных типов нет. На русской версии ОС
                            валидацию проходят только числа с ','. Из-за этого в следствии могут возникнуть проблемы
                            с приведением типов. Тоже самое и с Linux (проверял на kubuntu 18)
                            Для корректной работы программы решил использовать регулярные выражения
                        */

                        /*TextFieldDoubleValidator {
                            id: doubleValidator
                            notation: DoubleValidator.StandardNotation
                        }*/

                        RegularExpressionValidator {
                            id: doubleValidator
                            regularExpression:  /^[-+]?\d*\.?\d*$/
                        }

                        RegularExpressionValidator {
                            id: regExpValidator
                            regularExpression: /^[a-zA-Z0-9а-яА-Я_ ]*$/
                        }
                    }

                    onValueBindChanged: {
                        value = type == 1 ? value_chb.checked : value_tf.text
                    }
                }
            }
        }
    }
}
