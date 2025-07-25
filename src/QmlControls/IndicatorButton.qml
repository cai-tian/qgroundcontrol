/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick
import QtQuick.Controls

import QGroundControl
import QGroundControl.Controls

import QGroundControl.ScreenTools

/// Works just like a regular button but it can have a red indicator on the right side displayed
QGCButton {
    property bool indicatorGreen: false ///< true: no indicator shown, false: red indicator shown

    Rectangle {
        anchors.rightMargin:    ScreenTools.defaultFontPixelWidth / 3
        anchors.right:          parent.right
        anchors.verticalCenter: parent.verticalCenter
        width:                  radius * 2
        height:                 width
        radius:                 (ScreenTools.defaultFontPixelHeight * .75) / 2
        color:                  "red"
        visible:                enabled && !indicatorGreen
    }
}
