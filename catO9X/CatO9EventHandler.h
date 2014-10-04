//
//  EventHandler.h
//  catO9XCode
//
//  Created by Tommaso Allevi on 02/10/14.
//  Copyright (c) 2014 allevo. All rights reserved.
//

#ifndef __catO9XCode__EventHandler__
#define __catO9XCode__EventHandler__

#ifndef CATO9_CLASS
#define CATO9_CLASS
class CatO9;
#endif


#ifndef CATO9EVENT_CLASS
#define CATO9EVENT_CLASS
class CatO9Event;
#endif


class CatO9EventHandler {
    
public:
    virtual void onFileEdit(CatO9* cat, CatO9Event* event) = 0;
    virtual void onFileCreate(CatO9* cat, CatO9Event* event) = 0;
};

#endif /* defined(__catO9XCode__EventHandler__) */
