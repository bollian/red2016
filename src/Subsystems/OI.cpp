#include <PID/IntakeAngle.hpp>
#include <PID/ShooterPitch.hpp>
#include <PID/ShooterWheels.hpp>
#include <Ports/OI.hpp>
#include <Subsystems/ClimberArm.hpp>
#include <Subsystems/IntakeAngle.hpp>
#include <Subsystems/Mobility.hpp>
#include <Subsystems/OI.hpp>
#include <Subsystems/Sensors.hpp>
#include <Subsystems/ShooterPitch.hpp>
#include <Subsystems/ShooterWheels.hpp>
#include <Subsystems/Winches.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace OI
{
	const float JOYSTICK_DEADZONE = 0.1;
	
	Joystick* left_joy;
	Joystick* right_joy;
	
	Joystick* buttons_joy1;
	Joystick* buttons_joy2;
	
	bool last_pid_switch = false;
	bool last_shooter_wheels_switch = false;
	int last_intake_angle_dial = -1;
	int last_shooter_pitch_dial = -1;
	int last_shooter_wheels_dial = -1;
	Utils::VerticalDirection last_intake_angle_dir = Utils::VerticalDirection::V_STILL;
	
	IntakeAnglePID* intake_angle_pid = IntakeAnglePID::getInstance();
	ShooterPitchPID* shooter_pitch_pid = ShooterPitchPID::getInstance();
	ShooterWheelsPID* shooter_wheels_pid = ShooterWheelsPID::getInstance();

	float getJoystickAnalogPort(Joystick* joy, unsigned int port, float deadzone = 0.0);

	void initialize()
	{
		right_joy = new Joystick(OIPorts::RIGHT_JOYSTICK);
		left_joy = new Joystick(OIPorts::LEFT_JOYSTICK);
		
		buttons_joy1 = new Joystick(OIPorts::BUTTONS_JOYSTICK1);
		buttons_joy2 = new Joystick(OIPorts::BUTTONS_JOYSTICK2);
	}
	
	void process()
	{
		Mobility::setLeftSpeed(getJoystickAnalogPort(left_joy, OIPorts::JOYSTICK_Y_PORT, JOYSTICK_DEADZONE));
		Mobility::setRightSpeed(getJoystickAnalogPort(right_joy, OIPorts::JOYSTICK_Y_PORT, JOYSTICK_DEADZONE));
		
		bool sensor_switch = buttons_joy1->GetRawButton(OIPorts::SENSOR_ENABLE_SWITCH);
		Sensors::enableGyro(sensor_switch);
		Sensors::enableShooterAngle(sensor_switch);
		Sensors::enableIntakeAngle(sensor_switch);
		Sensors::enableShooterTach(sensor_switch);
		Sensors::enableLidar(sensor_switch);
		Sensors::enableDriveEncoders(sensor_switch);
		Sensors::enableBallLimit(sensor_switch);
		Sensors::enableShooterLimit(sensor_switch);
		Sensors::enablePDP(sensor_switch);
		
		////// PID & Sensor enable //////
		bool pid_switch;
		if (sensor_switch) {
			pid_switch = buttons_joy1->GetRawButton(OIPorts::PID_ENABLE_SWITCH);
		}
		else {
			pid_switch = false;
		}
		if (pid_switch != pid_switch) {
			IntakeAnglePID::getInstance()->enable(pid_switch);
			ShooterPitchPID::getInstance()->enable(pid_switch);
			ShooterWheelsPID::getInstance()->enable(pid_switch);
			
			last_pid_switch = pid_switch;
		}
		
		////// Winches & Climber Arm //////
		bool winch_switch = buttons_joy2->GetRawButton(OIPorts::MANUAL_WINCH_ENABLE_SWITCH);
		if (winch_switch) {
			Winches::setFrontSpeed(getJoystickAnalogPort(buttons_joy2, OIPorts::FRONT_WINCH_JOYSTICK, JOYSTICK_DEADZONE));
			Winches::setFrontSpeed(getJoystickAnalogPort(buttons_joy2, OIPorts::BACK_WINCH_JOYSTICK, JOYSTICK_DEADZONE));
		}
		else {
			ClimberArm::setSpeed(getJoystickAnalogPort(buttons_joy2, OIPorts::FRONT_WINCH_JOYSTICK));
		}
		
		////// Shooter speed dial //////
		int dial;
		bool shooter_switch = buttons_joy1->GetRawButton(OIPorts::SHOOTER_WHEELS_SWITCH);
		if (shooter_switch) {
			dial = Utils::convertVoltage(getJoystickAnalogPort(buttons_joy1, OIPorts::SHOOTER_SPEED_DIAL) + 1.0, ShooterWheels::getPresetCount(), 2.0);
			if (dial != last_shooter_wheels_dial) {
				if (shooter_wheels_pid->isEnabled()) {
					shooter_wheels_pid->setTarget(ShooterWheels::getRPMPreset(dial));
				}
				else {
					ShooterWheels::setSpeed(ShooterWheels::getSpeedPreset(dial));
				}
				
				last_shooter_wheels_dial = dial;
			}
		}
		else if (last_shooter_wheels_switch) { // if the switch was just turned off
			ShooterWheels::setSpeed(0.0);
			last_shooter_wheels_dial = -1; // forces a shooter update when the switch is turned back on
		}
		last_shooter_wheels_switch = shooter_switch;
		
		////// Shooter pitch dial //////
		dial = Utils::convertVoltage(getJoystickAnalogPort(buttons_joy1, OIPorts::SHOOTER_PITCH_DIAL) + 1.0, ShooterPitch::getPresetCount(), 2.0);
		if (dial != last_shooter_pitch_dial) { // if the dial has been moved
			if (shooter_pitch_pid->isEnabled()) {
				shooter_pitch_pid->setTarget(ShooterPitch::getAnglePreset(dial));
			}
			else {
				// TODO: implement non-pid shooter pitch controls
			}
			
			last_shooter_pitch_dial = dial;
		}
		
		////// Intake angle manual controls //////
		Utils::VerticalDirection intake_angle_dir = Utils::VerticalDirection::V_STILL;
		if (buttons_joy1->GetRawButton(OIPorts::MOVE_INTAKE_UP_BUTTON)) {
			intake_angle_dir = Utils::VerticalDirection::UP;
		}
		else if (buttons_joy1->GetRawButton(OIPorts::MOVE_INTAKE_DOWN_BUTTON)) {
			intake_angle_dir = Utils::VerticalDirection::DOWN;
		}
		else {
			intake_angle_dir = Utils::VerticalDirection::V_STILL;
		}
		
		// always update the intake dial
		dial = Utils::convertVoltage(getJoystickAnalogPort(buttons_joy1, OIPorts::INTAKE_ANGLE_DIAL) + 1.0, IntakeAngle::getPresetCount(), 2.0);
		
		switch (intake_angle_dir) {
		case Utils::VerticalDirection::UP:
		case Utils::VerticalDirection::DOWN:
			IntakeAngle::setDirection(intake_angle_dir);
			break;
		case Utils::VerticalDirection::V_STILL:
			////// Intake angle dial //////
			if (dial != last_intake_angle_dial) {
				if (intake_angle_pid->isEnabled()) {
					intake_angle_pid->setTarget(IntakeAngle::getAnglePreset(dial));
				}
				else {
					// TODO: implement non-pid intake angle control
				}
			}
			else if (intake_angle_dir != last_intake_angle_dir) {
				if (intake_angle_pid->isEnabled()) {
					intake_angle_pid->setTarget(Sensors::getIntakeAngle());
				}
				else {
					// TODO: implement non-pid intake angle control
				}
			}
			break;
		}
		
		last_intake_angle_dial = dial; // always update the intake dial, even while using manual controls
		last_intake_angle_dir = intake_angle_dir;
	}
	
	bool isPIDEnabled()
	{
		return buttons_joy1->GetRawButton(OIPorts::PID_ENABLE_SWITCH);
	}
	
	float getJoystickAnalogPort(Joystick* joy, unsigned int port, float deadzone)
	{
		float joy_value = -joy->GetRawAxis(port);
		
		if (deadzone != 0.0 && Utils::valueInRange(joy_value, -deadzone, deadzone)) {
			return 0.0;
		}
		
		return -joy->GetRawAxis(port);
	}
}
