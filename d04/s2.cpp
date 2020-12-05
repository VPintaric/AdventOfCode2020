#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <functional>
#include <regex>

using Passport = std::map< std::string, std::string >;
using ValidatorFunc = std::function< bool( const std::string & ) >;

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

ValidatorFunc makeYearValidator( int minYear, int maxYear ) {
    return [ minYear, maxYear ]( const std::string &field ) {
        auto year = std::stoi( field );
        return minYear <= year && year <= maxYear;
    };
}

bool validateHeight( const std::string &field ) {
    auto unit = field.substr( field.length() - 2 );
    auto height = std::stoi( field );
    if ( unit == "cm" ) {
        return 150 <= height && height <= 193;
    } else if ( unit == "in" ) {
        return 59 <= height && height <= 76;
    } else {
        return false;
    }
}

ValidatorFunc makeRegexValidator( const std::string &expr ) {
    return [ expr ]( const std::string &field ) -> bool {
        std::smatch m;
        return std::regex_match( field, m, std::regex( expr ));
    };
}

bool isValid( const Passport &passport ) {
    std::vector< std::pair< std::string, ValidatorFunc > > requiredFields{
        std::make_pair( "byr", makeYearValidator( 1920, 2002 )),
        std::make_pair( "iyr", makeYearValidator( 2010, 2020 )),
        std::make_pair( "eyr", makeYearValidator( 2020, 2030 )),
        std::make_pair( "hgt", validateHeight ),
        std::make_pair( "hcl", makeRegexValidator( "#[0-9a-f]{6}" )),
        std::make_pair( "ecl", makeRegexValidator( "amb|blu|brn|gry|grn|hzl|oth" )),
        std::make_pair( "pid", makeRegexValidator( "[0-9]{9}" ))
    };

    for ( auto &fieldValidator : requiredFields ) {
        auto kv = passport.find( fieldValidator.first );
        if ( kv == passport.end()) {
            return false;
        }

        if ( !fieldValidator.second( kv->second )) {
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
