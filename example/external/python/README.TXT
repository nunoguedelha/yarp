# Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
# Copyright (C) 2006-2010 RobotCub Consortium
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

This shows how to do some interaction with YARP from Python without 
using the YARP library.

It uses text mode tcp connections with acknowledgements ("CONNACK")
to make life simple.  Binary data could be sent with a bit more work.

Example usage:
  yarpserver
  yarp read /read
  ./yarprpc.py /read "10 20 30"    # these numbers should appear on yarp read
