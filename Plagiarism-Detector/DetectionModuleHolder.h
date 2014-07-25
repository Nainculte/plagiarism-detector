#ifndef DETECTIONMODULEHOLDER_H
#define DETECTIONMODULEHOLDER_H

#include <QString>

class DetectionModuleInterface;

class DetectionModuleHolder
{
public:
    virtual ~DetectionModuleHolder(void) {}

public:
    virtual void statusChanged(int newStatus) = 0;
    virtual void progressChanged(int newProgress) = 0;
};

#endif // DETECTIONMODULEHOLDER_H
