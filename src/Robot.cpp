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

class Robot: public SampleRobot
{
public:
	Robot()
	{
	}

	void RobotInit()
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

	void Autonomous()
	{
		char message[1023];
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

			snprintf(message, 1023, "sees goal: %d, shooter angle: %.2f, intake angle: %.2f, ball switch: %d, home switch: %d, lidar dist: %d",
					Cameras::canSeeGoal(),
					Sensors::getShooterAngle(),
					Sensors::getIntakeAngle(),
					Sensors::isBallLimitPressed(),
					Sensors::isShooterLimitPressed(),
					Sensors::getLidarDistance());
			DriverStation::ReportError(message);
		}
	}

	void OperatorControl()
	{
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
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
		while (IsEnabled() && IsTest()) {

		}
	}
};

START_ROBOT_CLASS(Robot)
