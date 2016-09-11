#include <chrono>
#include <math.h>
#include <ED/PIDManager.hpp>

using namespace std;
using namespace std::chrono;

namespace ED
{
	PIDManager::PIDManager(float p, float i, float d) :
		enabled(true),
		target(0.0),
		
		p(p),
		i(i),
		d(d),
		
		last_input(0.0),
		last_output(0.0),
		feed_forward_output(0.0),
		
		last_error(0.0),
		accumulated_error(0.0),
		clear_accumulated_error(false),
		
		max_accumulated_error(0.0),
		min_accumulated_error(0.0),
		i_zone(0.0),
		
		last_timestamp(duration_cast<nanoseconds>(system_clock::now().time_since_epoch())),

		enable_mutex(),
		process_mutex(),
		user_mutex()
	{
		
	}
	
	PIDManager::~PIDManager()
	{

	}

	void PIDManager::process()
	{
		nanoseconds timestamp = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch());
		float input = returnPIDInput();

		user_mutex.lock();
		process_mutex.lock();
		float error = getTarget() - input;

		if (isEnabled()) {
			typedef duration<float> float_seconds;
			float cycle_time = duration_cast<float_seconds>(last_timestamp - timestamp).count();
			
			// create a temporaty copy so that thread locking is unnecessary
			float i_zone = this->i_zone;
			// because i_zone is read from twice here
			bool in_i_zone = fabs(error) < i_zone && i_zone != 0.0;
			if (in_i_zone) {
				// use average error for trapezoidal sum
				accumulated_error += cycle_time * (error + last_error) / 2.0;
				
				if (min_accumulated_error < max_accumulated_error) {
					if (accumulated_error > max_accumulated_error) {
						accumulated_error = max_accumulated_error;
					}
					else if (accumulated_error < min_accumulated_error) {
						accumulated_error = min_accumulated_error;
					}
				}
			}
			
			float pid = p * error + d * (input - last_input) / cycle_time;
			pid = in_i_zone ? pid : pid + i * accumulated_error;

			// use lock_guard to be exception safe since usePIDOutput could contain anything
			{ lock_guard<mutex> lock(enable_mutex);
				if (isEnabled()) { // by now we may have been disabled
					usePIDOutput(pid, feed_forward_output);
					last_input = input;
					last_output = pid;
				}
			}
		}

		// last_error and last_timestamp are set inside
		// the enable function, so they have to be protected
		// by mutexes
		last_error = error;
		last_timestamp = timestamp;

		process_mutex.unlock();
		user_mutex.unlock();
	}
	
	void PIDManager::enable(bool enable)
	{
		if (enable != enabled) { // prevent unnecessary thread locking
			// process only reads from enabled, so it's not necessary to lock yet
			enabled = enable;

			if (enable) {
				// only reset the history when we are reenabling
				process_mutex.lock();
				if (clear_accumulated_error) {
					accumulated_error = 0.0;
				}
				last_error = getTarget() - returnPIDInput();
				last_timestamp = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch());
				process_mutex.unlock();
			}
			else {
				// wait until after process finishes,
				// guaranteeing that usePIDOutput is
				// not longer called after this function exits
				enable_mutex.lock();
				enable_mutex.unlock();
			}
		}
	}
	
	bool PIDManager::isEnabled() const
	{
		return enabled;
	}
	
	void PIDManager::setTarget(float target)
	{
		process_mutex.lock();
		feed_forward_output = getFeedForwardOutput(target);
		this->target = target;
		process_mutex.unlock();
	}
	
	float PIDManager::getTarget() const
	{
		return target;
	}
	
	void PIDManager::setPID(float p, float i, float d)
	{
		process_mutex.lock();
		this->p = p;
		this->i = i;
		this->d = d;
		process_mutex.unlock();
	}
	
	float PIDManager::getP() const
	{
		return p;
	}
	
	float PIDManager::getI() const
	{
		return i;
	}
	
	float PIDManager::getD() const
	{
		return d;
	}
	
	void PIDManager::autoClearAccumulatedError(bool clear)
	{
		clear_accumulated_error = clear;
	}

	void PIDManager::clearAccumulatedError()
	{
		process_mutex.lock();
		accumulated_error = 0.0;
		process_mutex.unlock();
	}
	
	void PIDManager::setAbsoluteIZone(float range)
	{
		i_zone = fabs(range);
	}
	
	void PIDManager::limitAccumulatedError(float min, float max)
	{
		process_mutex.lock();
		min_accumulated_error = min;
		max_accumulated_error = max;
		process_mutex.unlock();
	}
	
	float PIDManager::getLastInput() const
	{
		return last_input;
	}
	
	float PIDManager::getLastOutput() const
	{
		return last_output;
	}
	
	float PIDManager::getFeedForwardOutput(float new_target)
	{
		return 0.0;
	}

	void PIDManager::lockForConfigChange()
	{
		user_mutex.lock();
	}

	void PIDManager::unlockAfterConfigChange()
	{
		user_mutex.unlock();
	}
}
