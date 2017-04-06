# red2016

A rewrite of the team116 [ed2015](https://github.com/team116/ed2016) project for funsies and personal reflection.

## Purpose

red2016 is a rewrite of team 116, Epsilon Delta's code for the FIRST Stronghold competition.  It seeks to provide a model that is easier for beginners to understand, avoids dynamic memory allocation, simplifies state control, makes the code easier to read, and address specific bugs in WPILib that we encountered during the competition season.

## Structure

For those familiar with the different code structures made available to FIRST Robotics Competition teams, red2016 tries to be a merger between the Iterative and Command-Based styles of robot code.  For everyone else, that sentence wasn't at all helpful, so I shall elaborate below.

The build system remains unchanged from what is normally encountered in FRC, aside from the dependency on Cross the Roads Electronics' library for the TalonSRX motor controller.  Visit [documentation](http://www.ctr-electronics.com/talon-srx.html#product_tabs_technical_resources) and [library](http://www.ctr-electronics.com/hro.html#product_tabs_technical_resources) for up-to-date information on how to get TalonSRXs working with your controls system.

### Robot

The `Robot` class represents the main control loop of the code.  It inherits from the `SampleRobot` class, and thus has to implement the `Disabled`, `Autonomous`, `OperatorControl`, and `Test` functions, which are called once, and only once, when the robot enters the various control modes.  This differs from the typical model of inheriting from the `IterativeRobot` class, which exposes different functions for the setup and the main control loop of each mode.  I chose to use `SampleRobot` because it unlocks the main control loop from the 50 Hz enforced refresh rate of `IterativeRobot`, and it exposes to students an easy to understand yet critical usage of while loops.

### Subsytems

Subsystems are where the main control logic of the robot is implemented, and each Subsystem represents a particular part of the robot at varying levels of granularity, from the four-motored `Mobility` to the dead-simple `IntakeRoller`.  The first thing a seasoned FRC student will notice is that each Subsystem is a namespace, not a class.  While many a tale has been told about the dangers of global variables and objects, the Subsytems structure avoids these pitfalls by only exposing functions instead of data in their headers.  This allows the exposed functions to act in identical functionality to public functions in a class, and allows new programmers to jump into the code without having to worry much about classes, which is always a difficult topic for beginners.  Because these Subsystems represent components of a well-known robot, there is little to no risk that multiple instances of these Subsystems will need to be instantiated at any point in time, which would be another advantage of classes over namespaces.  As per the educational purpose of FIRST, students will eventually have to learn about object-oriented code in order to implement PID control, but that can be delayed until after they've mastered variables, functions, and basic control.

The contents of the Subsystems vary depending on their complexity.  All Subsystems contain the `initialize` and `process` functions.  The `initialize` function is called when the code first starts, and never again after that.  The `process` function is called as part of the main control loop, and is where most logic is implemented.  There are Subsystems where these functions do nothing but are still defined.  This is simply to allow easy expansion onto a Subsystem, and alleviate the forgetful programmer from having to add the  `initialize` or `process` function calls to Robot.cpp.

#### IntakeRoller

`IntakeRoller` is probably the simplest Subsystem of them all, and serves simply as a wrapper for the contained motor controller object.  The getters and setters for speed and direction are fairly standard inclusions to the Subsystem, and allow both simpler and more complex control, while compartmentalizing the code to accomodate for the possible future inclusion of safety checks and other complexities.

#### Mobility

`Mobility` serves as the textbook example for the red2016 state-machine system.  Each value of the `Mobility::State` enum represents a different task the Subsystem may try to perform.  The `process` function then defines the behavior of the Subsystem for each state.  The Subsystem then defines another function, `setState`, that determines the behavior of the Subsystem when entering and leaving different states.  Note that `setState` is not exposed in the header, instead there is a function purpose-built for entering each state, which is necessary for when a state, such as `Mobility::State::DRIVE_STRAIGHT` needs some sort of input to do its work.  There are two states that are common between all Subsystems: `DISABLED` and `WAITING`.  `DISABLED` allows a Subsystem to do nothing, which is useful for when there is a known hardware or software failure, and you simply have to run the robot without fixing the issue.  `WAITING` is a sort of no-state state.  It is the default value for all Subsystems, and typically grants other Subsystems direct control.

#### ShooterPitch

`ShooterPitch` is also a Subsystem with a state machine, but it also makes use of PID control.  red2016 doesn't use the WPILib PIDSubsystem class because of a bug we encountered during the 2016 competition where disabling and enabling PID control in quick succession could result in the code crashing.  The replacement PID implementation works very simply, providing two virtual functions, `returnPIDInput` and `usePIDOutput`, that serve as the input and output to the PID algorithm.  A slightly clunky consequence of the implementation of Subsystems as namespaces means that a separate class must be created in order to take advantage of PID, but this actually creates two advantages.  Firstly, it compartmentalizes PID control away from the Subsystem, forcing the usage of the exposed Subsystem functions, so that anything the PID implementation attempts to do must first go through the necessary safety-checks of the Subsystem.  Second, it means that the Subsystem has control over access to the PID implementation.  If the Subsystem were a class that inherited from another class to implement PID, which is the standard way to do it using WPILib, all other Subsystems then gain direct access to the PID control, and can then disable or enable PID without the Subsystem knowing, which could then result in a mismatch between the state of the Subsystem and the state of the PID controller.  This problem is aggravated by red2016's state system: imagine a scenario where `ShooterPitch::getState()` returns `MANUAL_CONTROL`, but PID is enabled.  It sounds bad because it is bad.

### Ports

The Ports folder contains all the different hardware port mappings on the robot.  In previous years, team 116 has used a single file called Ports.h to store all this data, but this resulted in long compile times when anything inside that file was changed.  The Ports folder allows all that information to be organized by purpose, so that adding a port to the Ports/OI.hpp file will only cause a recompile of Subsystems/OI.cpp.  Additionally, the definitions of the variables are contained in separate source files, so changing the value of a port doesn't result in cascading changes to other files as well.
