#include "timestamper.h"

std::string timestamper(void)
{

    std::ostringstream stream;
    time_t rawtime;
    tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);


    stream << (timeinfo->tm_year)+1900<<"/"<<(timeinfo->tm_mon)+1<<"/"<<timeinfo->tm_mday<<" "
    <<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec;



    return stream.str();

}
