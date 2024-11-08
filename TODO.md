Overall Goal: create a more useable code which is easy for people to use without in depth knowledge of how the simulation works.

TODO:
- Create Cmake file
- Flush out Readme
- Make drivers more customizable and more defined
- Output file tells you more about the simulation
- Fix enterence to enterance typo. Or maybe use a different word since cars also exit through the enterance of the parking lots.




Future work
- Reaccess tests and testing
- Set up Gtest
- File automatically created if no file with same name is present
- File in that sets up a simulation
- preferances for double empty parking spots to pull forward into?


Car.h
- There seem to be public member variables. This is bad practice and they should be made private.
- Consider the public static constexpr default values. Should they exist and should they be public? Are tests that use them helpful?
- Car speed should probably be a variable in the simulation instead of a constant value in Car

Strip.h
- Refactor getClosestVacantSpot()