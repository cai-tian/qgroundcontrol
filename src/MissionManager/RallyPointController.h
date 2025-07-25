/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QtCore/QLoggingCategory>
#include <QtPositioning/QGeoCoordinate>
#include <QtQmlIntegration/QtQmlIntegration>

#include "PlanElementController.h"
#include "QmlObjectListModel.h"

Q_DECLARE_LOGGING_CATEGORY(RallyPointControllerLog)

class GeoFenceManager;
class RallyPointManager;
class Vehicle;

class RallyPointController : public PlanElementController
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")
public:
    explicit RallyPointController(PlanMasterController* masterController, QObject* parent = nullptr);
    ~RallyPointController();
    
    Q_PROPERTY(QmlObjectListModel*  points                  READ points                                             CONSTANT)
    Q_PROPERTY(QString              editorQml               READ editorQml                                          CONSTANT)
    Q_PROPERTY(QObject*             currentRallyPoint       READ currentRallyPoint      WRITE setCurrentRallyPoint  NOTIFY currentRallyPointChanged)

    Q_INVOKABLE void addPoint       (QGeoCoordinate point);
    Q_INVOKABLE void removePoint    (QObject* rallyPoint);

    void start                      (bool flyView) final;
    bool supported                  (void) const final;
    void save                       (QJsonObject& json) final;
    bool load                       (const QJsonObject& json, QString& errorString) final;
    void loadFromVehicle            (void) final;
    void sendToVehicle              (void) final;
    void removeAll                  (void) final;
    void removeAllFromVehicle       (void) final;
    bool syncInProgress             (void) const final;
    bool dirty                      (void) const final { return _dirty; }
    void setDirty                   (bool dirty) final;
    bool containsItems              (void) const final;
    bool showPlanFromManagerVehicle (void) final;

    QmlObjectListModel* points                  (void) { return &_points; }
    QString             editorQml               (void) const;
    QObject*            currentRallyPoint       (void) const { return _currentRallyPoint; }

    void setCurrentRallyPoint   (QObject* rallyPoint);
    bool isEmpty                (void) const;

signals:
    void currentRallyPointChanged(QObject* rallyPoint);
    void loadComplete(void);

private slots:
    void _managerLoadComplete       (void);
    void _managerSendComplete       (bool error);
    void _managerRemoveAllComplete  (bool error);
    void _setFirstPointCurrent      (void);
    void _updateContainsItems       (void);
    void _managerVehicleChanged     (Vehicle* managerVehicle);

private:
    Vehicle*            _managerVehicle =       nullptr;
    RallyPointManager*  _rallyPointManager =    nullptr;
    bool                _dirty =                false;
    QmlObjectListModel  _points;
    QObject*            _currentRallyPoint =    nullptr;
    bool                _itemsRequested =       false;

    static constexpr int    _jsonCurrentVersion = 2;
    static constexpr const char* _jsonFileTypeValue =  "RallyPoints";
    static constexpr const char* _jsonPointsKey =      "points";
};
