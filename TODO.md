Overall Goal: create a more useable code which is easy for people to use without in depth knowledge of how the simulation works.

TODO:
- Flush out Readme
- Make drivers more customizable and more defined
- Output file tells you more about the simulation




Future work
- Reaccess tests and testing
- File automatically created if no file with same name is present
- File in that sets up a simulation
- preferances for double empty parking spots to pull forward into?


Car.h
- Consider the public static constexpr default values. Should they exist and should they be public? Are tests that use them helpful?
- Car speed should probably be a variable in the simulation instead of a constant value in Car

CarUnitTest.h
- Consider readding the Argumented constructor test. Probably not.

Strip.h
- Seeing some serious jank with this class.