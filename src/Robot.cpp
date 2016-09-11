#include <Coordination.hpp>
#include <Robot.hpp>
#include <Subsystems/Cameras.hpp>
#include <Subsystems/ClimberArm.hpp>
#include <Subsystems/HolderWheels.hpp>
#include <Subsystems/IntakeAngle.hpp>
#include <Subsystems/IntakeRoller.hpp>
#include <Subsystems/Mobility.hpp>
#include <Subsystems/OI.hpp>
#include <Subsystems/Sensors.hpp>
#include <Subsystems/ShooterPitch.hpp>
#include <Subsystems/ShooterWheels.hpp>
#include <Subsystems/Winches.hpp>
#include <WPILib.h>

void Robot::RobotInit()
{
	Cameras::initialize();
	ClimberArm::initialize();
	HolderWheels::initialize();
	IntakeAngle::initialize();
	IntakeRoller::initialize();
	Mobility::initialize();
	OI::initialize();
	Sensors::initialize();
	ShooterPitch::initialize();
	ShooterWheels::initialize();
	Winches::initialize();
	
	Coordination::initialize();
}

void Robot::Disabled()
{
	IntakeAngle::enablePID(false);
	ShooterPitch::enablePID(false);
	ShooterWheels::enablePID(false);
	
	interruptAll();
	
	char message[1023];
	while (!IsEnabled()) {
		snprintf(message, 1023, "sees goal: %d, shooter angle: %.2f, shooter rpm: %.2f, intake angle: %.2f, ball switch: %d, home switch: %d, lidar dist: %d",
			Cameras::canSeeGoal(),
			Sensors::getShooterAngle(),
			Sensors::getShooterAngle(),
			Sensors::getIntakeAngle(),
			Sensors::isBallLimitPressed(),
			Sensors::isShooterLimitPressed(),
			Sensors::getLidarDistance());
		DriverStation::ReportError(message);
	}
}

void Robot::Autonomous()
{
	IntakeAngle::enablePID(true);
	ShooterPitch::enablePID(true);
	ShooterWheels::enablePID(true);
	
	interruptAll();
	
	while (IsEnabled() && IsAutonomous()) {
		Cameras::process();
		ClimberArm::process();
		HolderWheels::process();
		IntakeAngle::process();
		IntakeRoller::process();
		Mobility::process();
		Sensors::process();
		ShooterPitch::process();
		ShooterWheels::process();
		Winches::process();
		
		processPID();
	}
}

void Robot::OperatorControl()
{
	bool enable_pid = OI::isPIDEnabled();
	IntakeAngle::enablePID(enable_pid);
	ShooterPitch::enablePID(enable_pid);
	ShooterWheels::enablePID(enable_pid);
	
	interruptAll();
	
	while (IsEnabled() && IsOperatorControl()) {
		Cameras::process();
		ClimberArm::process();
		HolderWheels::process();
		IntakeAngle::process();
		IntakeRoller::process();
		Mobility::process();
		OI::process();
		Sensors::process();
		ShooterPitch::process();
		ShooterWheels::process();
		Winches::process();
		
		processPID();
	}
}

/**
 * Runs during test mode
 */
void Robot::Test()
{
	while (IsEnabled() && IsTest()) {

	}
}

void Robot::processPID()
{
	IntakeAngle::processPID();
	ShooterPitch::processPID();
	ShooterWheels::processPID();
}

void Robot::interruptAll()
{
	Coordination::interrupt();
	
	HolderWheels::interrupt();
	IntakeAngle::interrupt();
	Mobility::interrupt();
	ShooterPitch::interrupt();
	ShooterWheels::interrupt();
}

START_ROBOT_CLASS(Robot)
