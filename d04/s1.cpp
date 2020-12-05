#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using Passport = std::map< std::string, std::string >;

std::vector< std::string > split( const std::string &s, char delimiter ) {
    std::vector< std::string > tokens;

    size_t prevPos = 0, nextPos;
    while (( nextPos = s.find( delimiter, prevPos )) != std::string::npos ) {
        tokens.emplace_back( s.substr( prevPos, nextPos - prevPos ));
        prevPos = nextPos + 1;
    }
    tokens.emplace_back( s.substr( prevPos ));

    return tokens;
}

std::vector< Passport > loadPassports( std::istream &inputstream ) {
    std::vector< Passport > passports;
    Passport passport;

    std::string line;
    while ( std::getline( inputstream, line )) {
        if ( line.empty()) {
            passports.push_back( passport );
            passport.clear();
            continue;
        }

        auto fields = split( line, ' ' );
        for ( auto &field : fields ) {
            auto keyValue = split( field, ':' );
            passport.insert( std::make_pair( keyValue[ 0 ], keyValue[ 1 ] ));
        }
    }

    passports.push_back( passport );

    return passports;
}

bool isValid( const Passport &passport ) {
    std::vector< std::string > requiredFields{
        "byr",
        "iyr",
        "eyr",
        "hgt",
        "hcl",
        "ecl",
        "pid"
    };

    for ( auto &field : requiredFields ) {
        if ( passport.find( field ) == passport.end()) {
            return false;
        }
    }

    return true;
}

int main() {
    std::ifstream infile( "in.txt" );

    auto passports = loadPassports( infile );

    int validCount = 0;
    for ( auto &passport : passports ) {
        if ( isValid( passport )) {
            validCount++;
        }
    }

    std::cout << validCount << std::endl;


    return 0;
}
