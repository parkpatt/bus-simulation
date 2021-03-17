/*!
 * \mainpage Transit Simulator 2020
 *
 * \section intro_sec Introduction
 *
 * Welcome to the documentation for my Transit Simulator. On this page, I will
 * tell you how to obtain, compile, and run the Transit Simulator. I will also 
 * discuss some of the design decisions I made.
 *
 * NOTE: The implementation for the observer pattern currently has some bugs.
 * As far as I can tell, the bugs have to do with clearing observers. After 
 * clicking one bus, then clicking on another, the simulation will sometimes
 * freeze, or not update the observer information appropriately.
 *
 * \section obtaining Obtaining the Code
 *
 * To obtain the source code for this simulation, use the University of 
 * Minnesota Github page at github.umn.edu/umn-csci-3081-s20/repo-patte591
 *
 * \section compiling Compilation
 *
 * To compile the simulation, navigate to the /project/src directory and type
 * 'make' into the command line. Note that some warnings will be generated
 * during compilation. Apparently, whoever wrote the initial codebase for this
 * project didn't know what the hell they were doing. The warnings will be 
 * very painful to read, so don't bother; just rest assured that the code will
 * indeed compile.
 * 
 *
 * \section running Running the Code
 * 
 * To run the simulation, Navigate to the /project directory and type 
 * ./build/bin/vis_sim <port_number>
 * port number should be a 4-digit number beginning with either 8 or 9. The
 * remaining digits can be anything. This should launch the web server for
 * the simulation.
 *
 * Once the server has been launched, open a browser and load the following
 * URL: 
 * http://127.0.0.1:<port_number>/web_graphics/project.html
 * replace <port_number> with the 4-digit number you chose for the previous step.
 * Once the webpage loads, the simulation is ready to go. Press the start button
 * to begin simulating!
 *
 * Note: Additional instructions for running the simulation via ssh can be found
 * in the file project/README.md
 *
 * \section design_choices Design Decisions
 *
 * In order to make the code more extensible, it was decided that the generation
 * of new buses should be decoupled from the VisualizationSimulator class, and 
 * handled instead by a BusFactory class. Both concrete and abstract factory
 * patterns were considered in the design of BusFactory, but, in the end, I went
 * with the abstract factory pattern. 
 *
 * The main motivation for using an abstract factory pattern rather than a 
 * concrete one was that an abstract factory pattern could be more easily 
 * extended in the event that other kinds of buses are desired. With a concrete 
 * factory pattern, the entire BusFactory code would have to be modified to 
 * allow for the generation of new types of buses. On the other hand, with the 
 * abstract factory pattern, all that needs to be done to add new types of buses 
 * is to define new subclasses of the BusFactory class. 
 *
 * One benefit of using the concrete factory pattern instead of the abstract
 * factory pattern is that the concrete pattern would have been able to handle
 * the random generation of different bus types. In the current implementation,
 * this randomization is handled in the file web_code/web/main.cpp, where a 
 * random number between 1 and 3 is used to determine which size of BusFactory
 * will be used during the simulation. If the concrete factory pattern had been 
 * used instead of the abstract factory pattern, this randomization could have 
 * been handled within the BusFactory code itself.
 *
 * \section observer_pattern Designing and Implementing the Observer Pattern
 * 
 * In order to implement the Observer pattern, two new classes were added:
 * IObservable, and IObserver. the Bus class was subsequently made to be a 
 * subclass of IObservable, and a class BusWebObserver was provided to me
 * in the file my_web_server_command.cc to extend the IObserver class. The
 * IObserver and IObservable classes were added using new header files in the
 * src directory; one header file for each class. For IObservable, the methods
 * RegisterObserver, ClearObservers and NotifyObservers were implemented. These
 * methods are defined in .cc files matching the .hh files in which they were 
 * declared, also in the src directory. The file bus.cc was also modified so 
 * that when Bus::Update() is called, it now updates the BusData field, and 
 * invokes the NotifyObserver method inherited from IObservable on the newly-
 * updated BusData struct.
 *
 * Currently, there are some bugs in the observer pattern functionality of the
 * project, as mentioned in the Introduction. I believe these bugs have 
 * something to do with old observers not being cleared properly.
 */
