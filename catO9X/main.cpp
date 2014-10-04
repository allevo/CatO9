#include <iostream>
#include <set>

using std::cout;
using std::cerr;
using std::endl;

#include "CatO9Event.h"
#include "CatO9Printer.h"
#include "CatO9.h"


class CatO9PrinterSimple: public CatO9Printer {
private:
    string filenameOfLastEvent;

public:
    void printEvent(CatO9Event* event) {
        if (event->getFilename() != this->filenameOfLastEvent) {
            cout << " ===== " << event->getFilename() <<  " ===== " << endl;
            this->filenameOfLastEvent = event->getFilename();
        }
        if(event->isType(IN_MODIFY)) {
            cout << event->getLines() << endl;
        }
        if(event->isType(IN_CREATE)) {
            // Do nothing
        }
    }
};

void rtrim(string& s, const string& delimiters) {

    s.erase(s.find_last_not_of("/") + 1);
}


int main(int argc, char const *argv[]) {
    bool ret;

    if (argc != 2) {
        cerr << "Please tell me which directory you want to watch" << endl;
        return -1;
    }
    string watch_dir = string(argv[1]);
    rtrim(watch_dir, "\\");

    CatO9 cato9(new CatO9PrinterSimple());
    try {
        cato9.watchFolder(watch_dir);
    } catch (InotifyException &e) {
        cerr << "Direcotry not found: " << endl;
        return -1;
    }


    // When stating, all files already exist
    // are seeked to the end!
    ret = cato9.addFilesInDir(watch_dir, true);
    if(!ret) {
        cerr << "Error on adding " << watch_dir << endl;
    }

    set<CatO9Event*> events;
    set<CatO9Event*>::iterator it;
    while(1) {
        events = cato9.waitNextEvents();

        for(it = events.begin(); it != events.end(); it++) {
            cato9.callEventHandler(*it);
        }
    }

    return 0;
}