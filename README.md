RoboCup-simulator

Installation instructions
1. Download grSim and follow its install instructions
2. Download QtCreator, get the open source version
3. Open QtCreator and select Open Project and navigate to the client.pro file for this package and open it
4. Under the Projects tab, go to build and add a custom build step
5. Set the Working Directory to the client directory for this package
6. Set command to protoc and set the arguments to: --proto_path=proto --cpp_out=src proto/*.proto
7. Run a build to be sure that everything works

Other Notes
1. You must be running grSim in order to get use work out of the simulator

TODO
1. Write a Makefile
