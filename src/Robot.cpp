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

Robot::Robot()
{
	intake_angle_pid = IntakeAnglePID::getInstance();
	shooter_pitch_pid = ShooterPitchPID::getInstance();
	shooter_wheels_pid = ShooterWheelsPID::getInstance();
}

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
}

void Robot::Disabled()
{
	intake_angle_pid->enable(false);
	shooter_pitch_pid->enable(false);
	shooter_wheels_pid->enable(false);
	
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
	intake_angle_pid->enable(true);
	shooter_pitch_pid->enable(true);
	shooter_wheels_pid->enable(true);
	
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
	intake_angle_pid->enable(enable_pid);
	shooter_pitch_pid->enable(enable_pid);
	shooter_wheels_pid->enable(enable_pid);
	
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
	intake_angle_pid->process();
	shooter_pitch_pid->process();
	shooter_wheels_pid->process();
}

START_ROBOT_CLASS(Robot)
