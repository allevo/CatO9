
//
//  CatO9Printer.h
//  catO9XCode
//
//  Created by Tommaso Allevi on 04/10/14.
//  Copyright (c) 2014 allevo. All rights reserved.
//

#ifndef catO9XCode_CatO9Printer_h
#define catO9XCode_CatO9Printer_h

#include "CatO9Event.h"

class CatO9Printer {
public:
    virtual void printEvent(CatO9Event* event) = 0;
};

#endif
