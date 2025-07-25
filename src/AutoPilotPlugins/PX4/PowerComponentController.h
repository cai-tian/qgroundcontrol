/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @author Don Gagne <don@thegagnes.com>

#pragma once

#include <QtQmlIntegration/QtQmlIntegration>

#include "FactPanelController.h"

/// Power Component MVC Controller for PowerComponent.qml.
class PowerComponentController : public FactPanelController
{
    Q_OBJECT
    QML_ELEMENT
public:
    PowerComponentController(void);
    
    Q_INVOKABLE void calibrateEsc(void);
    Q_INVOKABLE void startBusConfigureActuators(void);
    Q_INVOKABLE void stopBusConfigureActuators(void);
    
signals:
    void oldFirmware(void);
    void newerFirmware(void);
    void incorrectFirmwareRevReporting(void);
    void connectBattery(void);
    void disconnectBattery(void);
    void batteryConnected(void);
    void calibrationFailed(const QString& errorMessage);
    void calibrationSuccess(const QStringList& warningMessages);
    
private slots:
    void _handleVehicleTextMessage(int vehicleId, int compId, int severity, QString text, const QString &description);
    
private:
    void _stopCalibration(void);
    void _stopBusConfig(void);
    
    QStringList _warningMessages;
    static const int _neededFirmwareRev = 1;
};
