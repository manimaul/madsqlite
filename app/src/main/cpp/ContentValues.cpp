//
// Created by William Kamp on 10/11/16.
//

#include <iostream>
#include "ContentValues.h"

const std::unordered_set<std::string> &ContentValues::keySet() const {
    return _keys;
}

const std::vector<std::string> ContentValues::keys() const {
    return std::vector<std::string>(_keys.begin(), _keys.end());
}

bool ContentValues::containsKey(std::string const &key) {
    return _keys.find(key) != _keys.end();
}

void ContentValues::putData(std::string const &key, ContentValues::Data &data) {
    if (containsKey(key)) {
        long i = _dataMap.at(key);
        _values[i] = data;
    } else {
        long i = _values.size();
        _values.emplace_back(data);
        _dataMap.emplace(key, i);
    }
    _keys.emplace(key);
}

ContentValues::Data ContentValues::getData(std::string const &key) {
    long i = _dataMap.at(key);
    return _values[i];
}

std::int64_t ContentValues::getAsInteger(std::string const &key) {
    if (containsKey(key)) {
        const Data &data = getData(key);
        switch (data.dataType) {
            case INT:
                return data.dataInt;
            case REAL:
                return (std::int64_t) data.dataReal;
            case TEXT:
                return stoi(data.dataText);
            case BLOB:
                return ntohs(*reinterpret_cast<const std::int64_t *>(&data.dataBlob[0]));
            case NONE:
            default:
                break;
        }
    }
    return 0;
}

double ContentValues::getAsReal(std::string const &key) {
    if (containsKey(key)) {
        const Data &data = getData(key);
        switch (data.dataType) {
            case INT:
                return data.dataInt;
            case REAL:
                return data.dataReal;
            case TEXT:
                return stod(data.dataText);
            case BLOB:
                return ntohs(*reinterpret_cast<const double *>(&data.dataBlob[0]));
            case NONE:
            default:
                break;
        }
    }
    return 0;
}

std::string ContentValues::getAsText(std::string const &key) {
    if (containsKey(key)) {
        const Data &data = getData(key);
        switch (data.dataType) {
            case INT:
                return std::to_string(data.dataInt);
            case REAL:
                return std::to_string(data.dataReal);
            case TEXT:
                return data.dataText;
            case BLOB:
                return std::string(data.dataBlob.begin(), data.dataBlob.end());
            case NONE:
            default:
                break;
        }
    }
    return std::string();
}

std::vector<byte> ContentValues::getAsBlob(std::string const &key) {
    if (containsKey(key)) {
        return getData(key).dataBlob;
    }
    return std::vector<byte>();
}

void ContentValues::putInteger(std::string const &key, std::int64_t value) {
    Data d = {value};
    putData(key, d);
}

void ContentValues::putReal(std::string const &key, double value) {
    Data d = {value};
    putData(key, d);
}

void ContentValues::putString(std::string const &key, std::string const &value) {
    Data d = {value};
    putData(key, d);
}

void ContentValues::putBlob(std::string const &key, std::vector<byte> &value) {
    Data d = {value};
    putData(key, d);
}

bool ContentValues::isEmpty() {
    return _keys.size() <= 0;
}

ContentValues::DataType ContentValues::typeForKey(std::string const &key) {
    if (containsKey(key)) {
        return getData(key).dataType;
    }
    return NONE;
}

void ContentValues::putBlob(std::string const &key, void *blob, size_t sz) {
    byte *charBuf = (byte*)blob;
    std::vector<byte> value(charBuf, charBuf + sz);
    Data d = {value};
    putData(key, d);
}
