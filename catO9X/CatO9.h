//
//  CatO9.h
//  catO9XCode
//
//  Created by Tommaso Allevi on 02/10/14.
//  Copyright (c) 2014 allevo. All rights reserved.
//

#ifndef __catO9XCode__CatO9__
#define __catO9XCode__CatO9__


#ifndef CATO9_CLASS
#define CATO9_CLASS
class CatO9;
#endif

#include <set>
#include <string>
using std::set;
using std::string;


#include <sys/stat.h>
#include "dirent.h"

#include "inotify-cxx/inotify-cxx.h"

#include "CatO9File.h"
#include "CatO9EventHandler.h"
#include "CatO9Printer.h"


class CatO9: public CatO9EventHandler {

private:
    set<CatO9File*> files;
    Inotify notify;
    CatO9EventHandler* eventHandler;
    CatO9Printer* printer;

public:

    CatO9(CatO9Printer* printer) :
    eventHandler(this),
    printer(printer)
    { }

    CatO9File* addFile(string path) {
        CatO9File* file = new CatO9File(path);
        files.insert(file);
        return file;
    }

    void watchFolder(string directory) {
        // need to keep allocate this variable for WaitForEvents call
        notify.Add(new InotifyWatch(directory, IN_CREATE | IN_MODIFY));
    }

    bool addFilesInDir(string directory, bool goToTheEnd) {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(directory.c_str())) == NULL) {
            cerr << "Error on open " << directory << endl;
            return false;
        }

        struct stat st;
        while ((ent = readdir(dir)) != NULL) {
            string path = directory + '/' + ent->d_name;
            lstat(path.c_str(), &st);
            if(!S_ISREG(st.st_mode)) {
                continue;
            }
            CatO9File* file = this->addFile(path);

            if (goToTheEnd) {
                file->seekToTheEnd();
            }
        }
        closedir (dir);
        return true;
    }

    string readUntilEnd(string filename) {
        set<CatO9File*>::iterator it;
        string ret = "";
        for(it = files.begin(); it != files.end(); it++) {
            if ((*it)->getFilename() == filename) {
                ret = (*it)->readUntilEnd();
                break;
            }
        }
        return ret;
    }

    void goToTheEnd(string filename) {
        set<CatO9File*>::iterator it;
        for(it = files.begin(); it != files.end(); it++) {
            if ((*it)->getFilename() == filename) {
                (*it)->readUntilEnd();
                break;
            }
        }
    }

    set<CatO9Event*> waitNextEvents() {
        set<CatO9Event*> events;

        try {
            notify.WaitForEvents();
            size_t count = notify.GetEventCount();
            InotifyEvent event;
            CatO9Event* catEvent;
            while (count > 0) {
                bool got_event = notify.GetEvent(&event);
                count--;
                if (!got_event) {
                    continue;
                }
                catEvent = new CatO9Event(event.GetWatch()->GetPath() + "/" + event.GetName(), event.GetMask());
                events.insert(catEvent);
            }
        } catch(InotifyException &e) {
            cout << "Inotify exception occured: " << e.GetMessage() << endl;
        } catch (...) {
            cout << "unknown exception occured" << endl;
        }

        return events;
    }

    void callEventHandler(CatO9Event* event) {
        if (event->isType(IN_MODIFY)) {
            eventHandler->onFileEdit(this, event);
        } else if (event->isType(IN_CREATE)) {
            eventHandler->onFileCreate(this, event);
        } else {
            cout << "Unknown" << endl;
        }
    }

    // EventHandler functions
    void onFileEdit(CatO9* cat, CatO9Event* event) {
        event->setAddedLines(readUntilEnd(event->getFilename()));
        printer->printEvent(event);
    }

    void onFileCreate(CatO9* cat, CatO9Event* event) {
        addFile(event->getFilename());
        printer->printEvent(event);
    }


};

#endif /* defined(__catO9XCode__CatO9__) */
