#include <memory>
#include <Subsystems/Cameras.h>
#include <Subsystems/ShooterPitch.h>
#include <WPILib.h>

using namespace std;

namespace Cameras
{
	static const int IMAGE_WIDTH = 640; // pixel width of the stream image
	static const int IMAGE_HEIGHT = 360; // pixel height of the stream image

	const float TARGET_WIDTH = 51.1; // width of the actual target, cm
	const float TARGET_HEIGHT = 31.5; // height of the actual target, cm

	const float TARGET_ELEVATION = 246.38; // height of the target from the floor, cm
	const float TOWER_TO_GOAL_DISTANCE = 13.5;

	const float CAMERA_MOUNT_ANGLE = 0.0; // TODO: measure actual angle on real robot
	const float CAMERA_MOUNT_HEIGHT = 30.0; // height of the camera from the floor, cm
	const float CAMERA_SIDE_OFFSET = 28.2; // left-right distance from the camera to the center of the robot, cm

	const float HEIGHT_DISTANCE_RATIO = 46.25; // ratio of the target's pixel height to distance from the target in cm

	struct Contour {
		float x;
		float y;
		float area;
		float width;
		float height;
	};
	Contour target;

	shared_ptr<NetworkTable> grip = NetworkTable::GetTable("GRIP");

	void initialize()
	{

	}

	void process()
	{

	}

	void refreshContours()
	{
		// find the highest contours
		unsigned int index = 0;
		float height = 0.0f;
		for(unsigned int x = 0; x < grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>()).size(); x++) {
			if(grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>())[x] > height) {
				height = grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>())[x];
				index = x;
			}
		}

		if(canSeeGoal()) {
			target.x = grip->GetNumberArray("vision_contours/centerX", llvm::ArrayRef<double>())[index];
			target.y = grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>())[index];
			target.area = grip->GetNumberArray("vision_contours/area", llvm::ArrayRef<double>())[index];
			target.width = grip->GetNumberArray("vision_contours/width", llvm::ArrayRef<double>())[index];
			target.height = grip->GetNumberArray("vision_contours/height", llvm::ArrayRef<double>())[index];
		}
		else {
			// none of these values should ever be negative, so use -1.0 as a default when no goal is seen
			target.x = -1.0;
			target.y = -1.0;
			target.area = -1.0;
			target.width = -1.0;
			target.height = -1.0;
		}
	}

	bool canSeeGoal()
	{
		// do we have a contour area and location?
		if(grip->GetNumberArray("vision_contours/area", llvm::ArrayRef<double>()).size() > 0 &&
		   grip->GetNumberArray("vision_contours/centerX", llvm::ArrayRef<double>()).size() > 0 &&
		   grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>()).size() > 0) {

			return true; // then return true
		}
		return false; // otherwise, return false
	}

	float getTargetX()
	{
		if(canSeeGoal()) {
			return target.x / IMAGE_WIDTH;
		}
		return 0.0f;
	}

	float getTargetY()
	{
		if(canSeeGoal()) {
			return target.y / IMAGE_HEIGHT;
		}
		return 0.0f;
	}

	float getTargetWidth()
	{
		return target.width;
	}

	float getTargetHeight()
	{
		return target.height;
	}

	float getDistanceFromTarget()
	{
		if(canSeeGoal()) {
			return HEIGHT_DISTANCE_RATIO * IMAGE_HEIGHT / target.height;
		}
		else {
			return 0.0f;
		}
	}

	float getTargettingPitch()
	{
		if (canSeeGoal()) {
			return (CAMERA_MOUNT_ANGLE + atan((ShooterPitch::SHOOTER_TO_TARGET_HEIGHT - CAMERA_MOUNT_HEIGHT) / getDistanceFromTarget()));
		}
		return 0.0;
	}

	int getHorizontalPixelsFromTarget()
	{
		return (target.x - IMAGE_WIDTH / 2) - (getTargetWidth() / TARGET_WIDTH * CAMERA_SIDE_OFFSET);
	}

	bool isTargettingEnabled()
	{
		return true;
	}
}
