import QtQuick
import QtQuick.Controls

import QGroundControl
import QGroundControl.Controls


/// Text control used for displaying text of Maps
QGCLabel {
    property var map

    QGCMapPalette { id: mapPal; lightColors: map.isSatelliteMap }

    color:      mapPal.text
    style:      Text.Outline
    styleColor: mapPal.textOutline
}
