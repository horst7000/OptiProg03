#include "NonBipartitionCertificate.h"

std::ostream &operator<<(std::ostream &os, const NonBipartitionCertificate &certificate) {
    if(certificate.begin != -1) {

        os << "Es liegt ein Kreis ungerader Länge vor:" << std::endl;

        os << certificate.begin << " ";
        int predecessor = certificate.pre[certificate.begin];
        os << predecessor << " ";

        while(predecessor != -1 && predecessor != certificate.begin) {
            predecessor = certificate.pre[predecessor];
            os << predecessor << " ";
        }
        os << std::endl;
    }
    return os;
}
