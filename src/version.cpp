/*
 * File:   Version.cpp
 * Author: stefan
 *
 * Created on November 2, 2015, 7:23 PM
 */

#include "version.h"
#include <sstream>
#include <vector>
#include <iomanip>

Version::Version(const std::string &version) {
    std::string str = version;

    if(str.length() == 0) {
        throw VersionException(
            "version-string is empty or not set"
        );
    }
    this->majorn = 1;
    this->minorn = 1;
    this->buildn = 1;
    this->patchn = 1;

    return ; // FIXME
    throw VersionException(
        "not implemented yet"
    );


/*
    std::vector<std::string> sa = str.split("-");

        str = sa[0];
        try {
            if(sa.size() == 2) {
                this->patch = Integer.parseInt(sa[1]);
                if(this->patch > 9999) {
                    this->patch = 9999;
                }
            } else if(sa.size() > 2) {
                throw VersionException("invalid Version-string");
            }

            sa = str.split("\\.");

            this->major = Integer.parseInt(sa[0]);

            if(sa.size() > 1) {
                this->minor = Integer.parseInt(sa[1]);
            }

            if(sa.size() > 2) {
                this->build = Integer.parseInt(sa[2]);
            }

            if(sa.size() > 3) {
                this->patch = Integer.valueOf(sa[3]);
            }

        } catch(...) {
            throw VersionException("converting failed");
        }
    */
}

std::string Version::getJsonString() const {
    if(this->majorn == -1) {
        return "\"0.0.0.0\"";
    }
    std::stringstream ss;
    ss <<
        '"' << this->majorn << '.' <<
        this->minorn << '.' <<
        this->buildn << '.' <<
        this->patchn << '"';
    return ss.str();;
}

int Version::compareMajor(const Version &v) const {
    if(this->majorn < v.majorn) {
        return -1;
    } else if(this->majorn > v.majorn) {
        return 1;
    }
    return 0;
}

int Version::compareMinor(const Version &v) const {
    if(this->minorn < v.minorn) {
        return -1;
    } else if(this->minorn > v.minorn) {
        return 1;
    }
    return 0;
}

bool Version::operator <(const Version &v) const {
    if(this->majorn < v.majorn) {
        return true;
    } else if(this->majorn > v.majorn) {
        return false;
    } else if(this->minorn < v.minorn) {
        return true;
    } else if(this->minorn > v.minorn) {
        return false;
    } else if(this->buildn < v.buildn) {
        return true;
    } else if(this->buildn > v.buildn) {
        return false;
    } else if(this->patchn < v.patchn) {
        return true;
    } else if(this->patchn > v.patchn) {
        return false;
    }
    return false;
}

bool Version::operator >(const Version &v) const {
    return !this->operator <(v);
}

bool Version::operator <=(const Version &v) const {
    return this->operator <(v) || this->operator ==(v);
}

bool Version::operator >=(const Version &v) const {
    return this->operator >(v) || this->operator ==(v);
}

std::ostream& operator<<(std::ostream &out, const Version &v) {
    if(v.majorn == -1) {
        out << "0.0.0-0000";
        return out;
    }

    out <<
        v.majorn << "." << v.minorn << "." << v.buildn << "-" <<
        std::setw(4) << std::setfill('0') << v.patchn;

    return out;
}
