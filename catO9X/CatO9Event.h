//
//  CatO9Event.h
//  catO9XCode
//
//  Created by Tommaso Allevi on 02/10/14.
//  Copyright (c) 2014 allevo. All rights reserved.
//

#ifndef __catO9XCode__CatO9Event__
#define __catO9XCode__CatO9Event__


#ifndef CATO9EVENT_CLASS
#define CATO9EVENT_CLASS
class CatO9Event;
#endif

#include <stdint.h>
#include <string>
using std::string;


class CatO9Event {
private:
    string filename;
    uint32_t type;
    string addedLines;

public:
    CatO9Event(string filename, uint32_t type) :
    filename(filename),
    type(type) {}
    
    bool isType(uint32_t type) {
        return this->type & type;
    }
    
    string getFilename() {
        return this->filename;
    }
    
    uint32_t getMask() {
        return this->type;
    }

    void setAddedLines(string lines) {
        this->addedLines = lines;
    }

    string getLines() {
        return this->addedLines;
    }
};


#endif /* defined(__catO9XCode__CatO9Event__) */
