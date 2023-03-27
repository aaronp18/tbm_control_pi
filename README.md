This example uses the bcm2835 library to comunicate with the SPI.
The reference web site is: http://www.airspayce.com/mikem/bcm2835/

Download the library: http://www.airspayce.com/mikem/bcm2835/bcm2835-1.71.tar.gz, then:

tar zxvf bcm2835-1.71.tar.gz
cd bcm2835-1.71
./configure
make
sudo make check
sudo make install
cd ..

then compile the project from inside the project directory:

cd EasyCAT_Test

for the Standard example: gcc -o EasyCAT_Test EasyCAT_Test.cpp EasyCAT.cpp -l bcm2835
for the Custom example: gcc -DCUSTOM -o EasyCAT_Test EasyCAT_Test_Custom.cpp EasyCAT.cpp -l bcm2835

to run the example:

sudo ./EasyCAT_Test


Important Application Note for Raspberry Pi 4 or higher.

The SPI clock speed in the Raspberry Pi is calculated from
the CPU clock.
In the example application this value is set to:
BCM2835_SPI_CLOCK_DIVIDER_16, that is correct for
Raspberry Pi up to version 3.
From Raspberry 4 due to a higher CPU speed this value is
to change to: BCM2835_SPI_CLOCK_DIVIDER_32.

So if You use a Raspberry Pi 4 or higher in the example
application change the value
BCM2835_SPI_CLOCK_DIVIDER_16 to
BCM2835_SPI_CLOCK_DIVIDER_32.

## install paho mqtt

get packages

```
sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui
```
```
sudo apt-get install libssl-dev
```
```
sudo apt-get install doxygen graphviz
```

### install paho C lib

```
git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
git checkout v1.3.8

cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
sudo cmake --build build/ --target install
sudo ldconfig
```

### install paho C++ lib

```
git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp

cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
    -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
sudo cmake --build build/ --target install
sudo ldconfig
```