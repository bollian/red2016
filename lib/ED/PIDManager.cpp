#include <chrono>
#include <math.h>
#include <ED/PIDManager.hpp>

using namespace std::chrono;

namespace ED
{
	PIDManager::PIDManager(float p, float i, float d) :
		enabled(false),
		target(0.0),
		
		p(p),
		i(i),
		d(d),
		
		last_input(0.0),
		last_output(0.0),
		feed_forward_output(0.0),
		
		accumulated_error(0.0),
		
		max_accumulated_error(0.0),
		min_accumulated_error(0.0),
		i_zone(0.0),
		
		last_timestamp(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()))
	{
		
	}
	
	void PIDManager::process()
	{
		nanoseconds timestamp = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch());
		float input = returnPIDInput();
		float error = getTarget() - input;
		
		if (isEnabled()) {
			
			bool in_i_zone = fabs(error) < i_zone && i_zone != 0.0;
			if (in_i_zone) {
				typedef duration<float> float_seconds;
				// use average error for trapezoidal sum
				accumulated_error += duration_cast<float_seconds>(last_timestamp - timestamp).count() * (error + last_error) / 2.0;
				
				if (min_accumulated_error < max_accumulated_error) {
					accumulated_error = accumulated_error > max_accumulated_error ? max_accumulated_error : accumulated_error;
					accumulated_error = accumulated_error < min_accumulated_error ? min_accumulated_error : accumulated_error;
				}
			}
			
			
			float pid = p * error + d * (input - last_input);
			pid = in_i_zone ? pid : pid + i * accumulated_error;
			
			usePIDOutput(pid, feed_forward_output);
			last_input = input;
			last_output = pid;
		}
		last_error = error;
		last_timestamp = timestamp;
	}
	
	void PIDManager::enable(bool enable)
	{
		last_error = getTarget() - returnPIDInput();
		last_timestamp = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch());
		
		enabled = enable;
	}
	
	bool PIDManager::isEnabled() const
	{
		return enabled;
	}
	
	void PIDManager::setTarget(float target)
	{
		feed_forward_output = getFeedForwardOutput(target);
		this->target = target;
	}
	
	float PIDManager::getTarget() const
	{
		return target;
	}
	
	void PIDManager::setP(float p)
	{
		this->p = p;
	}
	
	void PIDManager::setI(float i)
	{
		this->i = i;
	}
	
	void PIDManager::setD(float d)
	{
		this->d = d;
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
	
	void PIDManager::clearAccumulatedError()
	{
		accumulated_error = 0.0;
	}
	
	void PIDManager::setAbsoluteIZone(float range)
	{
		i_zone = fabs(range);
	}
	
	void PIDManager::limitAccumulatedError(float min, float max)
	{
		min_accumulated_error = min;
		max_accumulated_error = max;
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
}
