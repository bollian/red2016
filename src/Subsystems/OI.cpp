#include <PID/IntakeAngle.hpp>
#include <PID/ShooterPitch.hpp>
#include <PID/ShooterWheels.hpp>
#include <Ports/OI.hpp>
#include <Subsystems/ClimberArm.hpp>
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
	Joystick* left_joy;
	Joystick* right_joy;
	
	Joystick* buttons_joy1;
	Joystick* buttons_joy2;
	
	bool last_pid_switch = false;
	bool last_shooter_wheels_switch = false;
	int last_shooter_wheels_dial = -1;
	int last_shooter_pitch_dial = -1;
	
	ShooterPitchPID* shooter_pitch_pid = ShooterPitchPID::getInstance();
	ShooterWheelsPID* shooter_wheels_pid = ShooterWheelsPID::getInstance();

	float getJoystickAnalogPort(Joystick* joy, unsigned int port);

	void initialize()
	{
		right_joy = new Joystick(OIPorts::RIGHT_JOYSTICK);
		left_joy = new Joystick(OIPorts::LEFT_JOYSTICK);
		
		buttons_joy1 = new Joystick(OIPorts::BUTTONS_JOYSTICK1);
		buttons_joy2 = new Joystick(OIPorts::BUTTONS_JOYSTICK2);
	}
	
	void process()
	{
		Mobility::setLeftSpeed(getJoystickAnalogPort(left_joy, OIPorts::JOYSTICK_Y_PORT));
		Mobility::setRightSpeed(getJoystickAnalogPort(right_joy, OIPorts::JOYSTICK_Y_PORT));
		
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
			Winches::setFrontSpeed(getJoystickAnalogPort(buttons_joy2, OIPorts::FRONT_WINCH_JOYSTICK));
			Winches::setFrontSpeed(getJoystickAnalogPort(buttons_joy2, OIPorts::BACK_WINCH_JOYSTICK));
		}
		else {
			ClimberArm::setSpeed(getJoystickAnalogPort(buttons_joy2, OIPorts::FRONT_WINCH_JOYSTICK));
		}
		
		////// Shooter speed dial //////
		bool shooter_switch = buttons_joy1->GetRawButton(OIPorts::SHOOTER_WHEELS_SWITCH);
		if (shooter_switch) {
			int shooter_dial = Utils::convertVoltage(getJoystickAnalogPort(buttons_joy1, OIPorts::SHOOTER_SPEED_DIAL), ShooterWheels::getPresetCount(), 5.0);
			if (shooter_dial != last_shooter_wheels_dial) {
				if (shooter_wheels_pid->isEnabled()) {
					shooter_wheels_pid->setTarget(ShooterWheels::getRPMPreset(shooter_dial));
				}
				else {
					ShooterWheels::setSpeed(ShooterWheels::getSpeedPreset(shooter_dial));
				}
			}
		}
		else if (last_shooter_wheels_switch) { // if the switch was just turned off
			ShooterWheels::setSpeed(0.0);
			last_shooter_wheels_dial = -1; // forces a shooter update when the switch is turned back on
		}
		last_shooter_wheels_switch = shooter_switch;
		
		////// Shooter pitch dial //////
		int pitch_dial = Utils::convertVoltage(getJoystickAnalogPort(buttons_joy1, OIPorts::SHOOTER_PITCH_DIAL), ShooterPitch::getPresetCount(), 5.0);
		if (pitch_dial != last_shooter_pitch_dial) { // if the dial has been moved
			if (shooter_pitch_pid->isEnabled()) {
				shooter_pitch_pid->setTarget(ShooterPitch::getAnglePreset(pitch_dial));
			}
			else {
				// TODO: implement non-pid shooter pitch controls
			}
			
			last_shooter_pitch_dial = pitch_dial;
		}
	}
	
	bool isPIDEnabled()
	{
		return buttons_joy1->GetRawButton(OIPorts::PID_ENABLE_SWITCH);
	}
	
	float getJoystickAnalogPort(Joystick* joy, unsigned int port)
	{
		return -joy->GetRawAxis(port);
	}
}
