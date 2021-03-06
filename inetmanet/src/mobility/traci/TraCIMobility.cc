//
// TraCIMobility - Mobility module to be controlled by TraCIScenarioManager
// Copyright (C) 2006 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

#include <limits>
#include <iostream>
#include <sstream>

#include "mobility/traci/TraCIMobility.h"

Define_Module(TraCIMobility);

namespace
{
const double MY_INFINITY = (std::numeric_limits<double>::has_infinity ? std::numeric_limits<double>::infinity() : std::numeric_limits<double>::max());

double roadIdAsDouble(std::string road_id)
{
    std::istringstream iss(road_id);
    double d;
    if (!(iss >> d)) return MY_INFINITY;
    return d;
}
}

void TraCIMobility::Statistics::initialize()
{
    firstRoadNumber = MY_INFINITY;
    startTime = simTime();
    totalTime = 0;
    stopTime = 0;
    minSpeed = MY_INFINITY;
    maxSpeed = -MY_INFINITY;
    totalDistance = 0;
    totalCO2Emission = 0;
}

void TraCIMobility::Statistics::watch(cSimpleModule& )
{
    WATCH(totalTime);
    WATCH(minSpeed);
    WATCH(maxSpeed);
    WATCH(totalDistance);
}

void TraCIMobility::Statistics::recordScalars(cSimpleModule& module)
{
    if (firstRoadNumber != MY_INFINITY) module.recordScalar("firstRoadNumber", firstRoadNumber);
    module.recordScalar("startTime", startTime);
    module.recordScalar("totalTime", totalTime);
    module.recordScalar("stopTime", stopTime);
    if (minSpeed != MY_INFINITY) module.recordScalar("minSpeed", minSpeed);
    if (maxSpeed != -MY_INFINITY) module.recordScalar("maxSpeed", maxSpeed);
    module.recordScalar("totalDistance", totalDistance);
    module.recordScalar("totalCO2Emission", totalCO2Emission);
}

void TraCIMobility::initialize(int stage)
{
    // skip stage 1 initialisation of BasicMobility as this messes with pos.x/pos.y and triggers an NB update with these wrong values
    if (stage != 1)
    {
        BasicMobility::initialize(stage);
    }

    if (stage == 1)
    {
        debug = par("debug");
        accidentCount = par("accidentCount");

        currentPosXVec.setName("posx");
        currentPosYVec.setName("posy");
        currentSpeedVec.setName("speed");
        currentAccelerationVec.setName("acceleration");
        currentCO2EmissionVec.setName("co2emission");

        statistics.initialize();
        statistics.watch(*this);

        if (!isPreInitialized)
        {
            external_id = -1;
            nextPos = Coord(-1,-1);
            road_id = -1;
            speed = -1;
            angle = M_PI;
            pos.x = -1;
            pos.y = -1;
        }
        isPreInitialized = false;

        WATCH(road_id);
        WATCH(speed);
        WATCH(angle);
        WATCH(pos.x);
        WATCH(pos.y);

        startAccidentMsg = 0;
        stopAccidentMsg = 0;
        manager = 0;
        last_speed = -1;

        if (accidentCount > 0)
        {
            simtime_t accidentStart = par("accidentStart");
            startAccidentMsg = new cMessage("scheduledAccident");
            stopAccidentMsg = new cMessage("scheduledAccidentResolved");
            scheduleAt(simTime() + accidentStart, startAccidentMsg);
        }

        updatePosition();
    }

}

void TraCIMobility::finish()
{
    statistics.stopTime = simTime();

    statistics.recordScalars(*this);

    cancelAndDelete(startAccidentMsg);
    cancelAndDelete(stopAccidentMsg);

    isPreInitialized = false;
}

void TraCIMobility::handleSelfMsg(cMessage *msg)
{
    if (msg == startAccidentMsg)
    {
        commandSetMaximumSpeed(0);
        simtime_t accidentDuration = par("accidentDuration");
        scheduleAt(simTime() + accidentDuration, stopAccidentMsg);
        accidentCount--;
    }
    else if (msg == stopAccidentMsg)
    {
        commandSetMaximumSpeed(-1);
        if (accidentCount > 0)
        {
            simtime_t accidentInterval = par("accidentInterval");
            scheduleAt(simTime() + accidentInterval, startAccidentMsg);
        }
    }
}

void TraCIMobility::preInitialize(std::string external_id, const Coord& position, std::string road_id, double speed, double angle)
{
    if (debug) EV << "pre-initializing to " << position.x << " " << position.y << " " << road_id << " " << speed << " " << angle << std::endl;

    this->external_id = external_id;
    nextPos = position;
    pos = position;
    this->road_id = road_id;
    this->speed = speed;
    this->angle = angle;

    isPreInitialized = true;
}

void TraCIMobility::nextPosition(const Coord& position, std::string road_id, double speed, double angle)
{
    if (debug) EV << "nextPosition " << position.x << " " << position.y << " " << road_id << " " << speed << " " << angle << std::endl;
    isPreInitialized = false;
    nextPos = position;
    this->road_id = road_id;
    this->speed = speed;
    this->angle = angle;
    changePosition();
}

void TraCIMobility::changePosition()
{
    simtime_t updateInterval = simTime() - this->lastUpdate;
    this->lastUpdate = simTime();

    // keep track of first road id we encounter
    if (statistics.firstRoadNumber == MY_INFINITY && (!road_id.empty())) statistics.firstRoadNumber = roadIdAsDouble(road_id);

    // keep speed statistics
    if ((pos.x != -1) && (pos.y != -1))
    {
        double distance = pos.distance(nextPos);
        statistics.totalDistance += distance;
        statistics.totalTime += updateInterval;
        if (speed != -1)
        {
            statistics.minSpeed = std::min(statistics.minSpeed, speed);
            statistics.maxSpeed = std::max(statistics.maxSpeed, speed);
            currentPosXVec.record(pos.x);
            currentPosYVec.record(pos.y);
            currentSpeedVec.record(speed);
            if (last_speed != -1)
            {
                double acceleration = (speed - last_speed) / updateInterval;
                double co2emission = calculateCO2emission(speed, acceleration);
                currentAccelerationVec.record(acceleration);
                currentCO2EmissionVec.record(co2emission);
                statistics.totalCO2Emission+=co2emission * updateInterval.dbl();
            }
            last_speed = speed;
        }
        else
        {
            last_speed = -1;
            speed = -1;
        }
    }

    pos = nextPos;
    fixIfHostGetsOutside();
    updatePosition();
}

void TraCIMobility::fixIfHostGetsOutside()
{
    raiseErrorIfOutside();
}

double TraCIMobility::calculateCO2emission(double v, double a)
{
    // Calculate CO2 emission parameters according to:
    // Cappiello, A. and Chabini, I. and Nam, E.K. and Lue, A. and Abou Zeid, M., "A statistical model of vehicle emissions and fuel consumption," IEEE 5th International Conference on Intelligent Transportation Systems (IEEE ITSC), pp. 801-809, 2002

    double A = 1000 * 0.1326; // W/m/s
    double B = 1000 * 2.7384e-03; // W/(m/s)^2
    double C = 1000 * 1.0843e-03; // W/(m/s)^3
    double M = 1325.0; // kg

    // power in W
    double P_tract = A*v + B*v*v + C*v*v*v + M*a*v; // for sloped roads: +M*g*sin_theta*v

    /*
    // "Category 7 vehicle" (e.g. a '92 Suzuki Swift)
    double alpha = 1.01;
    double beta = 0.0162;
    double delta = 1.90e-06;
    double zeta = 0.252;
    double alpha1 = 0.985;
    */

    // "Category 9 vehicle" (e.g. a '94 Dodge Spirit)
    double alpha = 1.11;
    double beta = 0.0134;
    double delta = 1.98e-06;
    double zeta = 0.241;
    double alpha1 = 0.973;

    if (P_tract <= 0) return alpha1;
    return alpha + beta*v*3.6 + delta*v*v*v*(3.6*3.6*3.6) + zeta*a*v;
}

