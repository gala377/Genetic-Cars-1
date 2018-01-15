/*!
* @authors Jakub Gajownik, Rafa� Galczak
* @date 15.01.18
*
* \brief Simulation aggregate physics objects like Ground and Vehicles.
*        As well as being in charge of interacting with other systems using signals (observers).
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <memory>
#include <vector>
#include "include\Vehicle.h"
#include "include\Ground.h"
#include "include\GroundGenerator.h"
#include "include\ObjectsFactory.h"
#include "include\Population.h"
#include <cstdio>
#include <cmath>
#include <QTimer>

class Simulation : public QObject {
	Q_OBJECT

	const std::size_t TRACK_SEGMENTS = 1000;
	const float TRACK_SEGMENT_WIDTH = 1.2f;
	const float TRACK_SEGMENTS_DELTA = 1.0f;
	const float CARS_START_X = 6.0f;
	const float CARS_START_Y = -5.4f;
	const std::size_t CHECK_TIME = 3000;
	const std::size_t MAX_ROUND_TIME = 60000;
public:
	Simulation(QObject *parent = Q_NULLPTR);

	void stop();
	void start();
	void newGround();
	void newVehicles();
	void setMutationRate(float mutation_rate);
	void setPopulationSize(std::size_t new_size);
	void setEliteSpecimen(std::size_t elite_specimen);

	float getMutationRate() const;
	std::size_t getEliteSpecimen() const;
	std::size_t getPopulationSize() const;
	const Objects::Vehicle& getBestVehicle() const;
	const std::vector<Objects::Vehicle> getVehicles() const;
	const std::weak_ptr<Objects::Ground> getGround() const;
public slots:
	void reset();
private slots:
	void endRound();
	void checkActivity();
signals:
	void roundEnd(std::vector<float> distances);
private:
	void clearVehicles();

	QTimer watchdog_;
	QTimer round_timer_;

	std::vector<float> fitnesses_;
	std::vector<Objects::Vehicle> vehicles_;
	std::shared_ptr<Objects::Ground> ground_;

	Algorithm::Population population_;
};

#endif