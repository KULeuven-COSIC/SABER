#!/usr/bin/python -u
# -*- coding: utf-8 -*-

import subprocess
import serial
import csv
import re
import os
import numpy
import signal
import sys
import time

uart = '/dev/ttyACM0'

def replace_line(file_name, line_num, text):
    lines = open(file_name, 'r').readlines()
    lines[line_num-1] = text
    out = open(file_name, 'w')
    out.writelines(lines)
    out.close()

def build():
	# Build
	cmd = "make clean && make"
	subprocess.Popen(cmd, shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE).wait()
	# Execute
	cmd = "make flash"
	subprocess.Popen(cmd, shell = True, stdout = subprocess.PIPE).wait()

def signal_handler(signal, frame):
	global ser
	if not ser is None:
		print('\nClosing connections...')
		ser.close()
	print('Done!')
	sys.exit(0)


def main():
	global ser
	ser = None
	signal.signal(signal.SIGINT, signal_handler)

	# Init serial communication
	ser = serial.Serial(uart, baudrate=115200)
	#time.sleep(5)
	ser.flushInput()
	ser.flushOutput()

	# Set up for memory benchmark
	replace_line('./src/main.c', 13, '#define MEMSIZE\n')
	build()

	# Process output
	line = ser.readline()
	t = int( (re.findall(r'0x[0-9A-F]+', line, re.I)[0]) ,16)
	print "RAM for key_gen = "+str(t)+" bytes"
	line = ser.readline()
	t = int( (re.findall(r'0x[0-9A-F]+', line, re.I)[0]) ,16)
	print "RAM for encaps = "+str(t)+" bytes"
	line = ser.readline()
	t = int( (re.findall(r'0x[0-9A-F]+', line, re.I)[0]) ,16)
	print "RAM for decaps = "+str(t)+" bytes"
	line = ser.readline()
	t = int( (re.findall(r'0x[0-9A-F]+', line, re.I)[0]) ,16)
	print "Total RAM for Saber# = "+str(t)+" bytes"

	print 'benchmark of memory done!'


	# Set up for timing benchmark
	replace_line('./src/main.c', 13, '#define SPEED\n')
	build()

	# Process output
	line = ser.readline()
	t = int( (re.findall(r'0x[0-9A-F]+', line, re.I)[0]) ,16)
	print "Time for key_gen = "+str(t)+" clock cycles"
	line = ser.readline()
	t = int( (re.findall(r'0x[0-9A-F]+', line, re.I)[0]) ,16)
	print "Time for encaps = "+str(t)+" clock cycles"
	line = ser.readline()
	t = int( (re.findall(r'0x[0-9A-F]+', line, re.I)[0]) ,16)
	print "Time for decaps = "+str(t)+" clock cycles"

	print 'benchmark of time done!'

	subprocess.Popen("make clean", shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE).wait()
	ser.close()

	sys.exit(0)



if __name__ == "__main__":
	main()
