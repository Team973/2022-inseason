# 2022-inseason
The repository for the 2022 season, Rapid React!
# Points of Intrest
- You can find the interactions between the turret and limelight in `SubsystemManager.cpp`. The turret logic can be found in `Turret.cpp`.

- `Teleop.cpp` allows our robot to change climb states when our driver presses the right button. In addition, the climb logic can be found in `Climb.cpp`.

- All of our different autos can be found in `AutoManager.cpp` and our commands can be found in the `src/main/cpp/src/auto/commands`. 

- Our distance based calculations for controlling shooting RPM are contained in the `SubsystemManager.cpp`.

# Our Philosophy
- We always build in manual overides so we do not rely on automation if something fails.

- We rely on a rigorous testing schedule to ensure that all of our code is reliable.

- We always try to keep our code up to date to allow for easier collaboration.
