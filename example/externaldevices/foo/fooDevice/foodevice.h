/*
 * Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
 * Copyright (C) 2006-2010 RobotCub Consortium
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is just an example for an empty device.


#include <yarp/dev/DeviceDriver.h>

namespace yarp {
    namespace dev {
      class foodevice;
    }
}

class yarp::dev::foodevice : public DeviceDriver
{
private:
public:
    foodevice() {}
    virtual bool open(yarp::os::Searchable& config);
};

