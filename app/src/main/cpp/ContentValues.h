//
// Created by William Kamp on 10/11/16.
//

#ifndef PROJECT_CONTENT_VALUES_H
#define PROJECT_CONTENT_VALUES_H


#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Constants.h"

class ContentValues {
public:
    enum DataType {
        NONE,
        INT,
        REAL,
        TEXT,
        BLOB,
    };

private:

    struct Data {
        DataType dataType;
        std::vector<byte> dataBlob;
        double dataReal;
        std::int64_t dataInt;
        std::string dataText;

        Data() {};
        Data(const std::vector<byte> &dataBlob) : dataBlob(dataBlob) {
            dataType = BLOB;
        };
        Data(const double dataReal) : dataReal(dataReal) {
            dataType = REAL;
        };
        Data(const std::int64_t dataInt) : dataInt(dataInt) {
            dataType = INT;
        };
        Data(const std::string &dataText) : dataText(dataText) {
            dataType = TEXT;
        };
    };
    std::unordered_set<std::string> _keys;
    std::vector<Data> _values;
    std::unordered_map<std::string, long> _dataMap;
    void putData(std::string key, Data &data);
    Data getData(std::string key);
public:


    const std::unordered_set<std::string> &keySet() const;
    const std::vector<std::string> keys() const;

    bool isEmpty();
    bool containsKey(std::string key);
    DataType typeForKey(std::string key);

    //region ACCESSORS

    std::int64_t getAsInteger(std::string key);

    double getAsReal(std::string key);

    std::string getAsText(std::string key);

    std::vector<byte> getAsBlob(std::string key);

    void putInteger(std::string key, std::int64_t value);

    void putReal(std::string key, double value);

    void putString(std::string key, std::string value);

    void putBlob(std::string key, std::vector<byte> &blob);

    //endregion

};


#endif //PROJECT_CONTENT_VALUES_H
