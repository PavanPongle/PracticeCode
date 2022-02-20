
#!/bin/sh

echo "Build Started"

#sudo apt-get install libgtest-dev


#create the build directory
[ -d "./build" ] || mkdir build

cd build

cmake ../

cmake --build .

./FootballTurSim

./TestFootballTurSim –gtest_output=”xml:report.xml”



