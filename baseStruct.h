#ifndef BASESTRUCT_H
#define BASESTRUCT_H

#include <QString>

struct base {
    int ID;
    QString Title;
    QString Additional;
    QString ChangedFiles;
    QString DatePosted;
    QString DateModified;
};

struct key {
    int ID;
    QString Title;
};

#endif // BASESTRUCT_H
