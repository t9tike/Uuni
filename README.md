# Uuni
A monitoring setup for heat treatment oven using couple of k-type thermocouples, ntc thermistors, arduino uno (changing to nano asap) and raspberry pi 3 b+.
Arduino gets and handles sensor data from thermocouples and thermistors and raspberry pi reads those from serial and then writes them to a simple database.
Raspberry pi also works as a simple server with LAMP-stack, so you can monitor sensor data from the webpage.
Work in progress!

Database still not included here.
