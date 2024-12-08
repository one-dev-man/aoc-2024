#pragma once

// 

#include <iostream>
#include <functional>
#include <list>
#include <vector>
#include <map>
#include <sstream>

// 

using namespace std;

// 

namespace collections {

        const size_t nindex = string::npos;

        // 

        template<typename In, typename Out>
        list<Out> map(
            const list<In> &l,
            const function<Out (In)> &mapper
        ) {
            list<Out> result = {};
            for(const In &value : l) result.push_back(mapper(value));
            return result;
        }

        // 

        template<typename In, typename Out>
        vector<Out> map(
            const vector<In> &v,
            const function<Out (In)> &mapper
        ) {
            vector<Out> result = {};
            for(const In &value : v) result.push_back(mapper(value));
            return result;
        }

        // 

        template<typename InKey, typename InValue, typename OutKey, typename OutValue>
        std::map<OutKey, OutValue> map(
            const std::map<InKey, InValue> &m,
            const function<pair<OutKey, OutValue> (pair<InKey, InValue>)> &mapper
        ) {
            std::map<OutKey, OutValue> result = {};
            for(const pair<InKey, InValue> &entry : m) result[entry.first] = entry.second;
            return result;
        }

        //

        template<typename V>
        list<V> copy(const list<V> &l) {
            return collections::map(l, [](V value) -> V { return value; });
        }

        //

        template<typename V>
        vector<V> copy(const vector<V> &v) {
            return collections::map(v, [](V value) -> V { return value; });
        }

        //

        template<typename K, typename V>
        std::map<K, V> copy(const std::map<K, V> &m) {
            return collections::map(m, [](pair<K, V> entry) -> pair<K, V> { return entry; });
        }

        // 

        #define __collections_find(c, value, booleanComparator)\
            bool found = false;\
            size_t index = 0;\
            \
            for(\
                auto it = c.begin(), itend = c.end();\
                it != itend && !found;\
                ++it, ++index\
            ) found = booleanComparator(*it, value);\
            \
            return found ? index : collections::nindex;\

        template<typename V>
        size_t find(
            const list<V> &l,
            const V &value,
            const function<bool (V v1, V v2)> &booleanComparator = [](V v1, V v2) -> bool { return v1 == v2; }
        ) { __collections_find(l, value, booleanComparator); }

        template<typename V>
        size_t find(
            const vector<V> &v,
            const V &value,
            const function<bool (V v1, V v2)> &booleanComparator = [](V v1, V v2) -> bool { return v1 == v2; }
        ) { __collections_find(v, value, booleanComparator); }

        //

        template<typename V>
        size_t count(
            const vector<V> &v,
            const V value,
            const function<bool (V v1, V v2)> &booleanComparator = [](V v1, V v2) -> bool { return v1 == v2; }
        ) {
            size_t result = 0;

            for(const V &currentValue : v)
                if(booleanComparator(currentValue, value)) result++;

            return result;
        }

        //

        #define __collections_print(c, out, stringifier)\
            const size_t size = c.size();\
            \
            out << "[";\
            if(size > 0) {\
                out << stringifier(c.front());\
                auto it = c.begin();\
                it++;\
                for(\
                    auto itend = c.end();\
                    it != itend;\
                    ++it\
                ) {\
                    out << ", ";\
                    out << stringifier(*it);\
                }\
            }\
            out << "]";\

        template<typename V>
        void print(
            const list<V> &l,
            ostream &out,
            function<string (V value)> stringifier = [](V value) -> string { stringstream strs; strs << value; return strs.str(); }
        ) { __collections_print(l, out, stringifier); }

        template<typename V>
        void print(
            const vector<V> &v,
            ostream &out,
            function<string (V value)> stringifier = [](V value) -> string { stringstream strs; strs << value; return strs.str(); }
        ) { __collections_print(v, out, stringifier); }

}