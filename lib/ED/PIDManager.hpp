#ifndef LIB_ED_PIDMANAGER_H_
#define LIB_ED_PIDMANAGER_H_

#include <chrono>

using namespace std::chrono;

namespace ED
{
/**
 * This class serves as a replacement to the PIDSubsystem provied by WPILib.
 *
 * Notable differences:
 * 1) there is no feed-forward support by default
 * 2) accumulated error is not reset by default when the target changes
 * 3) the setpoint is called the target, because SetSetpoint sounds silly
 * 4) there is no input range or output range
 *
 * There is no default support of a feed-forward value because it would be
 * unclear what the feed-forward value might be relative to.  The easiest
 * implementation would be to simple take the target value and multiply it
 * by a coefficient, but a more powerful implementation would be to multiply
 * the coefficient by the ratio of the new target to the maximum input because
 * then the maximum input can be changed without having to change the feed-
 * forward coefficient.  The more powerful implementation then creates the
 * question of whether or not the miniumum value of the ratio will be
 * considered zero or a separate minimum input value.
 *
 * Accumulated or integrated error is not reset when the target changes
 * because that can create motor backdrive that harms motors.  If this
 * feature is desired, it can be implemented by overriding getFeedForwardOutput().
 *
 * The overall goal of this class is to provide greater simplicity and
 * transparency than that provided by PIDSubsystem.  To further that end,
 * there is no implemented "output range," because that feature is easily
 * enough implemented by overriding the usePIDOutput function.  In addition,
 * the feature does not clearly define what happens when the actual PID
 * output naturally falls outside that output range.  This class tries the
 * best it can to avoid having to define quircky behavior like that.
 *
 * There is no input range, because setting maximum and miniumum values for
 * sensor input is easily implemented in the returnPIDInput input fuction,
 * the same way and output range can be implemented in usePIDOutput.
 */
class PIDManager
{
public:
	void process();
	
	void enable(bool);
	bool isEnabled() const;
	
	void setTarget(float);
	float getTarget() const;
	
	/**
	 * sets the proportional coefficient, leaving all other coefficients untouched
	 * @param p the new proportional coefficient
	 */
	void setP(float p);
	/**
	 * sets the integral coefficient, leaving all other coefficients untouched
	 * @param i the new integral coefficient
	 */
	void setI(float i);
	/**
	 * sets the derivative coefficient, leaving all other coefficients untouched
	 * @param d the new derivative coefficient
	 */
	void setD(float d);
	
	/**
	 * get the current proportional coefficient
	 * @return the proportional coefficient
	 */
	float getP() const;
	/**
	 * get the current integral coefficient
	 * @return the integral coefficient
	 */
	float getI() const;
	/**
	 * get the current derivative coefficient
	 * @return the derivative coefficient
	 */
	float getD() const;
	
	void clearAccumulatedError();
	/**
	 * sets the absolute range around the target in which the integral term isn't used
	 * and the accumulated error isn't updated.  To disable this feature, set the range
	 * to 0.0.
	 * @param range absolute range
	 */
	void setAbsoluteIZone(float range);
	/**
	 * sets the maximum and miniumum value of the accumulated error, limiting the power of the integral term
	 * to disable this limitation, set the limit to 0.0.  In the case that the accumulated error passes these
	 * bounds, the min or max is used depending on whether the accumulated error is greater than or less than
	 * the provided range.  To disable this feature, set the miniumum equal to or greater than the maximum.
	 * @param min the value below which the accumulated error isn't allowed to drop
	 * @param max the value above which the accumulated error isn't allowed to rise
	 */
	void limitAccumulatedError(float min, float max);
	
	float getLastInput() const;
	float getLastOutput() const;

protected:
	PIDManager(float p, float i, float d);
	
	virtual float returnPIDInput() = 0;
	/**
	 * override this function to use the output of the PID system
	 * normally this is where a user of the PIDManager would set the speed of motors and the like
	 * @param pid_output   output as a result of the normal proportional-integral-derivative loop
	 * @param feed_forward result of the getFeedForwardOutput function
	 */
	virtual void usePIDOutput(float pid_output, float feed_forward) = 0;
	
	/**
	 * called to determine the feed-forward output of the PIDManager
	 *
	 * Feed-forward output is used to jump-start a PID system by outputing a value
	 * relative to the target, as opposed to the error from the target.
	 *
	 * This function will be called everytime the setTarget is called, and as a result
	 * can be used as a sort of event for each time the target changes.  For example,
	 * one might want to call clearAccumulatedError in this function so that error
	 * accumulated from the previous target does not affect the new target.
	 *
	 * By the time this function is called, the target stored by the class (as returned by
	 * getTarget()) won't have changed, so to see the new target, use the new_target
	 * argument.
	 * @param  new_target the next target to be used by the PIDManager
	 * @return            a feed-forward value used to set an initial output of the PIDManager
	 */
	virtual float getFeedForwardOutput(float new_target);
	
private:
	bool enabled;
	float target;
	
	float p;
	float i;
	float d;
	
	float last_input;
	float last_output;
	float feed_forward_output;
	
	float last_error;
	float accumulated_error;
	
	float max_accumulated_error;
	float min_accumulated_error;
	float i_zone;
	
	nanoseconds last_timestamp;
};
}

#endif // LIB_ED_PIDMANAGER_H_
