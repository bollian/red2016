#ifndef LIB_ED_PIDMANAGER_H_
#define LIB_ED_PIDMANAGER_H_

#include <chrono>
#include <mutex>

using namespace std;
using namespace std::chrono;

namespace ED
{
/**
 * This class serves as a replacement to the PIDSubsystem provided by WPILib.
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
 * question of whether or not the minimum value of the ratio will be
 * considered zero or a separate minimum input value.
 *
 * Accumulated or integrated error is not reset by default when the target
 * changes because that can create motor backdrive that harms motors.  If
 * this feature is desired, it can be achieved by calling autoClearAccumulatedError(true).
 *
 * The overall goal of this class is to provide greater simplicity and
 * transparency than that provided by PIDSubsystem.  To further that end,
 * there is no implemented "output range," because that feature does not
 * clearly define what happens when the actual PID output naturally falls
 * outside that range.  In addition, an output range is very easily
 * implemented inside usePIDOutput.
 *
 * There is no input range, because setting maximum and minimum values for
 * sensor input is easily implemented in the returnPIDInput input function,
 * the same way and output range can be implemented in usePIDOutput.  If
 * wrapping behavior is desired, use the getRelative function from Utils.hpp
 * inside returnPIDInput.
 *
 * PIDManager is safe in a multithreaded environment when there is no more
 * than one user of the class on a separate thread.
 *
 * All the functions that change the behavior of the PIDManager are guaranteed
 * to be applied by the time the function exits, even in a multithreaded
 * setup.  However, when calling more than one function at a time,
 * use lockForConfigChange and unlockAfterConfigChange for the most reliable
 * behavior.
 */
class PIDManager
{
public:
	virtual ~PIDManager();

	void process();
	
	/**
	 * allows the PIDManager to process inputs and send outputs
	 */
	void enable(bool enable);
	bool isEnabled() const;
	
	void setTarget(float);
	float getTarget() const;
	
	/**
	 * sets the proportional, integral, and derivative coefficients
	 * @param p the new proportional coefficient
	 * @param i the new integral coefficient
	 * @param d the new derivative coefficient
	 */
	void setPID(float p, float i, float d);
	
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
	
	/**
	 * configures the PIDManager to clear the accumulated error for the I term every
	 * time the PIDManager is reanabled or the target is changed
	 *
	 * defaults to false
	 * @param clear enables or disables automatic clearing of the accumulation
	 */
	void autoClearAccumulatedError(bool clear);
	/**
	 * resets the accumulated error, which is used for the I term, to zero
	 */
	void clearAccumulatedError();

	/**
	 * sets the absolute range around the target in which the integral term isn't used
	 * and the accumulated error isn't updated.  To disable this feature, set the range
	 * to 0.0.
	 * @param range absolute range
	 */
	void setAbsoluteIZone(float range);
	/**
	 * sets the maximum and minimum value of the accumulated error, limiting the power of the integral term
	 * to disable this limitation, set the limit to 0.0.  In the case that the accumulated error passes these
	 * bounds, the min or max is used depending on whether the accumulated error is greater than or less than
	 * the provided range.  To disable this feature, set the minimum equal to or greater than the maximum.
	 * @param min the value below which the accumulated error isn't allowed to drop
	 * @param max the value above which the accumulated error isn't allowed to rise
	 */
	void limitAccumulatedError(float min, float max);
	
	/**
	 * prevents the PIDManager from commencing any more calculations
	 *
	 * If the PIDManager is operating on a separate thread from the user,
	 * and if the user is modifying multiple configuration values at once,
	 * it becomes possible for changes that are supposed to be applied
	 * together to be split so that one set of changes happens before
	 * usePIDOutput is called and the rest happen after.  This causes
	 * problems when the changesets only function with each other.
	 *
	 * It is recommended to call lockForConfigChange before a calling
	 * more than one of the following functions: setTarget, setPID,
	 * clearAccumulatedError, setAbsoluteIZone, or limitAccumulatedError.
	 *
	 * NOTE:  This function blocks not only this PIDManager from operating,
	 * but all other PIDManagers on the same thread.  As a result, it
	 * should be considered an expensive operation to be used sparingly.
	 * It is best to avoid having to change the configuration often.
	 */
	void lockForConfigChange();
	/**
	 * allows the PIDManager to recommence calculations
	 *
	 * This function must be called after a call to lockForConfigChange.
	 */
	void unlockAfterConfigChange();

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
	 * This function will be called every time the setTarget is called, and as a result
	 * can be used as a sort of event for each time the target changes.
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
	bool clear_accumulated_error;
	
	float max_accumulated_error;
	float min_accumulated_error;
	float i_zone;
	
	nanoseconds last_timestamp;

	mutex enable_mutex;
	mutex process_mutex;
	mutex user_mutex;
};
}

#endif // LIB_ED_PIDMANAGER_H_
