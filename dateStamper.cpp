#include "dateStamper.h"

std::string dateStamper(void)
{

    std::ostringstream stream;
    time_t rawtime;
    tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);


    stream <<(timeinfo->tm_year)+1900<<"-"<<(timeinfo->tm_mon)+1<<"-"<<timeinfo->tm_mday;



    return stream.str();

}
