//
//  CatO9File.h
//  catO9XCode
//
//  Created by Tommaso Allevi on 02/10/14.
//  Copyright (c) 2014 allevo. All rights reserved.
//

#ifndef catO9XCode_CatO9File_h
#define catO9XCode_CatO9File_h


#include <fstream>
#include <string>
using std::string;
using std::ifstream;
using std::ios_base;


class CatO9File {
private:
    string filename;
    ifstream stream;
public:
    CatO9File(string filename) :
    filename(filename),
    stream(filename.c_str())
    { }

    void seekToTheEnd() {
        stream.seekg(0, ios_base::end);
    }

    string readUntilEnd() {
        string all = "";
        int pos;
        char a;
        while(1) {
            pos = stream.tellg();
            a = stream.peek();
            if (a == EOF) {
                // The stream is set ot EOF
                // This is ugly but should work
                stream.seekg(-1, ios_base::cur);
                stream.seekg(1, ios_base::cur);
                break;
            }
            a = stream.get();
            all += a;
        }
        return all;
    }

    string getFilename() const {
        return filename;
    }
};

#endif
