//
// Created by 刘宇杰 on 24-4-18.
//

#include "baseCodes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <iomanip>

//#define START "西土城" // 起点
//#define END "大兴机场" // 终点

#define ONE "1号线"
#define TWO "2号线"
#define FOUR "4号线"
#define FIVE "5号线"
#define SIX "6号线"
#define SEVEN "7号线"
#define EIGHT "8号线"
#define NINE "9号线"
#define TEN "10号线"
#define ELEVEN "11号线"
#define THIRTEEN "13号线"
#define FOURTEEN "14号线"
#define FIFTEEN "15号线"
#define SIXTEEN "16号线"
#define SEVENTEEN "17号线"
#define NINETEEN "19号线"
#define CHANGPING "昌平线"
#define XIJIAO "西郊线"
#define YANFANG "燕房线"
#define YIZHUANG "亦庄线"
#define FANGSHAN "房山线"
#define AIRPORT "首都机场线"
#define S1 "S1线"
#define DAXING "大兴线"
#define DAXING_AIRPORT "大兴机场线"
#define BATONG "八通线"
#define YIZHUANG_T1 "亦庄线T1线"

using namespace std;

unordered_map<string, float> lineVelocity; // 地铁线路速度

string result_1;

// 定义图的邻接表结构
unordered_map<string, vector<pair<pair<string, int>, pair<string, float>>>> adjList; // <站点, <(相邻站点, 距离), (线路, 速度)>>

// 定义图的操作
class graphOperation {
public:
    // 添加边(用于最少换乘路径)
    void addEdge(const string &from, const string &to, int weight, const string &line) {
        pair<string, float> lineInfo = make_pair(line, lineVelocity[line]);
        adjList[from].push_back(make_pair(make_pair(to, weight), lineInfo));
        adjList[to].push_back(make_pair(make_pair(from, weight), lineInfo));
        // 无向图,双向添加
    }

    // 从文件中导入地铁线路并构造无向图(用于最少换乘路径)
    void importFromFile(const string &filename) {
        ifstream file(filename);
        string line;

        if (!file.is_open()) {
            cerr << "Unable to open the file." << endl;
        }

        while (getline(file, line)) {
            istringstream iss(line);
            string from, to, lineName;
            int weight;
            while (iss >> from >> to >> weight >> lineName) {
                addEdge(from, to, weight, lineName);
            }
        }

        file.close();
    }

    // 添加线路
    void addLine(const string &line, const string &filename) {
        bool needAddLine = true;
        for (auto &station: adjList) {
            for (auto &edge: station.second) {
                if (edge.second.first == line) {
                    needAddLine = false;
                    break;
                }
            }
            if (!needAddLine) break;
        }

        if (needAddLine) {
            ifstream file(filename);
            string line_in_file;

            bool line_exist = false;

            if (!file.is_open()) {
                cerr << "Unable to open the file." << endl;
            }

            while (getline(file, line_in_file)) {
                istringstream iss(line_in_file);
                string from, to, lineName;
                int weight;
                while (iss >> from >> to >> weight >> lineName && lineName == line) {
                    addEdge(from, to, weight, lineName);
                    line_exist = true;
                }
            }

            file.close();

            if (!line_exist) {
                cout << "这条线路还未开通或已经被您删除!" << endl;
                result_1 = "这条线路还未开通或已经被您删除!";
            } else {
                cout << "添加线路成功!" << endl;
                result_1 = "添加线路成功!";
            }
        } else {
            cout << "这条线路已经存在于您的地铁线路中, 不能重复添加!" << endl;
            result_1 = "这条线路已经存在于您的地铁线路中, 不能重复添加!";
        }
    }

    // 删除线路
    void deleteLine(const string &line) {
        bool line_exist = false;
        for (auto &station: adjList) {
            station.second.erase(remove_if(station.second.begin(), station.second.end(),
                                           [&](const pair<pair<string, int>, pair<string, float>> &edge) {
                                               if (edge.second.first == line) {
                                                   line_exist = true;
                                                   return true;
                                               }
                                               return false;
                                           }), station.second.end());
        }
        if (line_exist) {
            cout << "删除线路成功!" << endl;
            result_1 = "删除线路成功!";
        } else {
            cout << "这条线路还未开通或已经被您删除!" << endl;
            result_1 = "这条线路还未开通或已经被您删除!";
        }
    }

    // 判断是否存在通路(基于BFS)
    bool isPathExist(const string &start, const string &end) {
        unordered_set<string> visited;
        queue<string> q;
        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            for (const auto &edge: adjList[current]) {
                if (edge.first.first == end) {
                    return true;
                }
                if (visited.find(edge.first.first) == visited.end()) {
                    q.push(edge.first.first);
                    visited.insert(edge.first.first);
                }
            }
        }

        return false;
    }

    // 基于Dijkstra算法查找最少换乘的路径
    vector<pair<string, string>> findLeastTransferPath(const string &start, const string &end) {
        unordered_map<string, int> transferCount; // 记录换乘次数

        using QueueElement = pair<pair<int, int>, string>; // <换乘次数, 总距离, 站点>
        auto comp = [](const QueueElement &a, const QueueElement &b) {
            return (a.first.first > b.first.first
                    || (a.first.first == b.first.first && a.first.second > b.first.second));
        };
        priority_queue<QueueElement, vector<QueueElement>, decltype(comp)> q(comp); // 小顶堆,用于记录换乘次数和总距离

        // 记录前驱线路
        unordered_map<string, string> prevLine;
        // 记录前驱站点
        unordered_map<string, string> prev;

        unordered_map<string, int> distance; // 记录到达每个站点的总距离

        // 起点
        prev[start] = "";
        transferCount[start] = 0;
        q.push(make_pair(make_pair(0, 0), start));
        distance[start] = 0;

        while (!q.empty()) {
            string current = q.top().second;
            q.pop();

            if (current == end) {
                vector<pair<string, string>> path;
                for (string at = end; !at.empty(); at = prev[at]) {
                    path.push_back(make_pair(at, prevLine[at]));
                }
                reverse(path.begin(), path.end());
                path.begin()->second = (path.begin() + 1)->second; // 起点线路与第一个站点线路相同
                return path;
            }

            for (auto &edge: adjList[current]) {
                int newTransferCount = transferCount[current] + (edge.second.first != prevLine[current]
                                                                 ? 1 : 0);
                int newDistance = distance[current] + edge.first.second;
                if (transferCount.find(edge.first.first) == transferCount.end()
                    || newTransferCount < transferCount[edge.first.first]) {
                    transferCount[edge.first.first] = newTransferCount;
                    if (newDistance < distance[edge.first.first] || distance.find(edge.first.first) == distance.end()) {
                        distance[edge.first.first] = newDistance;
                    }
                    q.push(make_pair(make_pair(newTransferCount, newDistance),
                                     edge.first.first));
                    prev[edge.first.first] = current; // 记录路径
                    prevLine[edge.first.first] = edge.second.first; // 记录线路
                }
            }
        }

        return {}; // 如果没有路径
    }

    // 基于Dijkstra算法查找最短时间的路径
    vector<pair<string, string>> findShortestTimePath(const string &start, const string &end) {
        unordered_map<string, float> time;
        unordered_map<string, int> transferCount; // 记录换乘次数

        // 记录前驱线路
        unordered_map<string, string> prevLine;
        // 记录前驱站点
        unordered_map<string, string> prev;

        unordered_map<string, int> distance; // 记录到达每个站点的总距离

        time[start] = 0;
        transferCount[start] = 0;
        distance[start] = 0;

        using QueueElement = pair<pair<int, int>, string>; // <总时间, 总距离, 站点>
        auto comp = [](const QueueElement &a, const QueueElement &b) {
            return a.first.first > b.first.first || (a.first.first == b.first.first
                                                     && a.first.second > b.first.second);
        };
        priority_queue<QueueElement, vector<QueueElement>, decltype(comp)> queue(comp); // 小顶堆,用于记录总时间

        queue.push(make_pair(make_pair(0, 0), start));

        while (!queue.empty()) {
            string current = queue.top().second;
            queue.pop();

            for (const auto &edge: adjList[current]) {
                int newTransferCount = transferCount[current] + (edge.second.first != prevLine[current] ? 1 : 0);
                float newTime = time[current] + (((((float) edge.first.second / 1000) / edge.second.second) * 60)
                                                 + 1 + (float) newTransferCount * 5);
                int newDistance = distance[current] + edge.first.second;
                if (time.find(edge.first.first) == time.end()
                    || newTime < time[edge.first.first]) {
                    time[edge.first.first] = newTime;
                    transferCount[edge.first.first] = newTransferCount;
                    if (newDistance < distance[edge.first.first] || distance.find(edge.first.first) == distance.end()) {
                        distance[edge.first.first] = newDistance;
                    }
                    queue.push(make_pair(make_pair(newTime, newDistance), edge.first.first));
                    prev[edge.first.first] = current;
                    prevLine[edge.first.first] = edge.second.first;
                }
            }
        }

        vector<pair<string, string>> path;
        for (string at = end; !at.empty(); at = prev[at]) {
            path.push_back(make_pair(at, prevLine[at]));
        }
        reverse(path.begin(), path.end());
        path.begin()->second = (path.begin() + 1)->second; // 起点线路与第一个站点线路相同
        return path;
    }

    // 计算路径长度
    float calculatePathLength(const vector<pair<string, string>> &path) {
        float length = 0;
        for (auto station = path.begin(); station != path.end(); station++) {
            if (next(station) != path.end()) {
                for (const auto &edge: adjList[station->first]) {
                    if (edge.first.first == next(station)->first) {
                        length += (float) edge.first.second / 1000;
                        break;
                    }
                }
            }
        }
        return length;
    }

    // 计算路径时间
    float calculatePathTime(const vector<pair<string, string>> &path) {
        float time = 0;
        for (auto station = path.begin(); station != path.end(); station++) {
            if (next(station) != path.end()) {
                for (const auto &edge: adjList[station->first]) {
                    if (edge.first.first == next(station)->first) {
                        time += (float) (((((float) edge.first.second / 1000) / edge.second.second) * 60)
                                         + 1 + (float) (station->second != next(station)->second) * 5);
                        break;
                    }
                }
            }
        }
        return time;
    }

    // 计算路径价格
    int calculatePathPrice(vector<pair<string, string>> &path) {

        int price_DaXing = 0, price_ShouDu = 0, price;
        for (const auto &station: path) {
            if (station.second == DAXING_AIRPORT)
                price_DaXing = 35;
            if (station.second == AIRPORT)
                price_ShouDu = 25;
        }
        // 删除大兴机场和首都机场有关的站点
        path.erase(remove_if(path.begin(), path.end(),
                             [&](const pair<string, string> &station) {
                                 return station.first == DAXING_AIRPORT || station.first == AIRPORT;
                             }), path.end());

        float length = calculatePathLength(path);
        if (length <= 6)
            price = 3;
        else if (length > 6 && length <= 12)
            price = 4;
        else if (length > 12 && length <= 22)
            price = 5;
        else if (length > 22 && length <= 32)
            price = 6;
        else price = 6 + (length - 32) / 20;

        price = price + price_DaXing + price_ShouDu;

        return price;
    }
};

// 存储地铁每个线路的速度
void convertLinesVelocity() {
    lineVelocity = {
            {ONE,            75},
            {TWO,            80},
            {FOUR,           90},
            {FIVE,           80},
            {SIX,            100},
            {SEVEN,          80},
            {EIGHT,          80},
            {NINE,           80},
            {TEN,            80},
            {ELEVEN,         100},
            {THIRTEEN,       75},
            {FOURTEEN,       75},
            {FIFTEEN,        80},
            {SIXTEEN,        80},
            {SEVENTEEN,      100},
            {NINETEEN,       120},
            {CHANGPING,      100},
            {XIJIAO,         70},
            {YANFANG,        80},
            {YIZHUANG,       80},
            {FANGSHAN,       100},
            {AIRPORT,        110},
            {S1,             100},
            {DAXING,         80},
            {DAXING_AIRPORT, 160},
            {BATONG,         80},
            {YIZHUANG_T1,    80}
    };
}

// 打印
class print : public graphOperation {
public:
//    void printGraph() {
//        for (const auto &p: adjList) {
//            cout << p.first << " -> ";
//            for (const auto &q: p.second) {
//                cout << "(" << q.first.first << ", " << q.first.second << ", " << q.second.first << ") ";
//            }
//            cout << endl;
//        }
//    } // 根据邻接表输出图(debug用)
//
//    void print_specific_station(const string &station) {
//        cout << station << "->";
//        for (const auto &q: adjList[station])
//            cout << "(" << q.first.first << ", " << q.first.second << ", " << q.second.first << ") ";
//        cout << endl;
//    } // 根据站点输出特定站点的邻接表(debug用)
//
//    void print_line(const string &line) {
//        cout << line << ":\n";
//        for (const auto &p: adjList) {
//            for (const auto &q: p.second) {
//                if (q.second.first == line)
//                    cout << p.first << " -> " << q.first.first;
//            }
//        }
//    } // 根据线路输出特定线路的邻接表(debug用)

    static void printPath(const vector<pair<string, string>> &path) {
        for (auto station = path.begin(); station != path.end(); station++) {
            cout << station->first << "(" << station->second << ")";
            if (next(station) != path.end() && next(station)->second != station->second) {
                cout << " ==> " << "您需要换乘: " << next(station)->second;
            }
            if (next(station) != path.end()) {
                cout << " -> ";
            }
        }
        cout << endl;
    } // 输出路径
};

void baseCodes::graphInitial()
{
    graphOperation g;
    convertLinesVelocity();
    g.importFromFile("../subway.txt");
}

string baseCodes::insert_or_delete(char choice_1, const string &line_name) {
    graphOperation g;

    if (choice_1 == 'A' || choice_1 == 'a') {
        g.addLine(line_name, "../subway.txt");
    } else if (choice_1 == 'D' || choice_1 == 'd') {
        g.deleteLine(line_name);
    }

    return result_1;
}

string baseCodes::base_code(const string &start, const string &end, int choice_2) {
    graphOperation g;

    string result;

//    // 输入起点和终点
//    string utf8_start, utf8_end;
//    cout << "请输入起始站(例如: 西土城): " << endl;
//    getline(cin, utf8_start);
//    cout << "请输入终点站(例如: 沙河): " << endl;
//    getline(cin, utf8_end);

//    string utf8_start = convertToUtf8(start, "GBK");
//    string utf8_end = convertToUtf8(end, "GBK");

    // 判断是否存在通路
    if (!g.isPathExist(start, end)) {
        result = "糟糕！ 您输入的起始站和终点站之间没有通路!";
        return result;
    }

    vector<pair<string, string>> path_1 = g.findLeastTransferPath(start, end);
    vector<pair<string, string>> path_2 = g.findShortestTimePath(start, end);

    // 基于当前系统的当前日期/时间
    time_t now = time(0);
    tm ltm = *localtime(&now);

    // 计算预计到达时间
    chrono::system_clock::time_point NOW = chrono::system_clock::now();

    // 计算路径1的预计到达时间
    int travelTimeInSeconds1 = static_cast<int>(g.calculatePathTime(path_1) * 60);
    chrono::seconds travelDuration1(travelTimeInSeconds1);

    chrono::system_clock::time_point arrivalTime1 = NOW + travelDuration1;

    time_t arrivalTime_t1 = chrono::system_clock::to_time_t(arrivalTime1);
    tm arrivalTime_tm1 = *localtime(&arrivalTime_t1);

    // 计算路径2的预计到达时间
    int travelTimeInSeconds2 = static_cast<int>(g.calculatePathTime(path_2) * 60);
    chrono::seconds travelDuration2(travelTimeInSeconds2);

    chrono::system_clock::time_point arrivalTime2 = NOW + travelDuration2;

    time_t arrivalTime_t2 = chrono::system_clock::to_time_t(arrivalTime2);
    tm arrivalTime_tm2 = *localtime(&arrivalTime_t2);

//    cout << "请选择您的需求: (输入1或2 -- 1. 最少换乘路径 2. 最短时间路径)" << endl;
//    int choice_1;
//    cin >> choice_1;

    cout << "当前时间为: "
         << 1900 + ltm.tm_year << "年"
         << setfill('0') << setw(2) << 1 + ltm.tm_mon << "月"
         << setfill('0') << setw(2) << ltm.tm_mday << "日" << " "
         << setfill('0') << setw(2) << ltm.tm_hour << ":"
         << setfill('0') << setw(2) << ltm.tm_min << ":"
         << setfill('0') << setw(2) << ltm.tm_sec << endl;

    result += "当前时间为: ";
    result += to_string(1900 + ltm.tm_year) + "年";
    result += to_string(1 + ltm.tm_mon) + "月";
    result += to_string(ltm.tm_mday) + "日 ";
    result += to_string(ltm.tm_hour) + ":";
    result += to_string(ltm.tm_min) + ":";
    result += to_string(ltm.tm_sec) + "\n";

    if (choice_2 == 1) {
        cout << "1. 最少换乘路线为:" << endl;
        print::printPath(path_1);
        cout << "路程: " << g.calculatePathLength(path_1) << " km" << endl;
        cout << "预计花费时间: " << fixed << setprecision(2) << g.calculatePathTime(path_1) << " min" << endl;
        cout << "总价格: " << g.calculatePathPrice(path_1) << " RMB" << endl;
        cout << "预计到达时间: "
             << 1900 + arrivalTime_tm1.tm_year << "年"
             << setfill('0') << setw(2) << 1 + arrivalTime_tm1.tm_mon << "月"
             << setfill('0') << setw(2) << arrivalTime_tm1.tm_mday << "日" << " "
             << setfill('0') << setw(2) << arrivalTime_tm1.tm_hour << ":"
             << setfill('0') << setw(2) << arrivalTime_tm1.tm_min << ":"
             << setfill('0') << setw(2) << arrivalTime_tm1.tm_sec << endl;

        result += "您的最少换乘路径为: \n\n";
        for (auto station = path_1.begin(); station != path_1.end(); station++) {
            result += station->first + "(" + station->second + ")";
            if (next(station) != path_1.end() && next(station)->second != station->second) {
                result = result + " ==> " + "您需要换乘: " + next(station)->second;
            }
            if (next(station) != path_1.end()) {
                result += " -> ";
            }
        }
        result += "\n\n";
        result += "路程: " + to_string(g.calculatePathLength(path_1)) + " km\n";
        result += "预计花费时间: " + to_string(g.calculatePathTime(path_1)) + " min\n";
        result += "总价格: " + to_string(g.calculatePathPrice(path_1)) + " RMB\n";
        result += "预计到达时间: "
                  + to_string(1900 + arrivalTime_tm1.tm_year) + "年"
                  + to_string(1 + arrivalTime_tm1.tm_mon) + "月"
                  + to_string(arrivalTime_tm1.tm_mday) + "日 "
                  + to_string(arrivalTime_tm1.tm_hour) + ":"
                  + to_string(arrivalTime_tm1.tm_min) + ":"
                  + to_string(arrivalTime_tm1.tm_sec) + "\n";
    } else if (choice_2 == 2) {
        cout << "2. 最短时间路径为:" << endl;
        print::printPath(path_2);
        cout << "路程: " << g.calculatePathLength(path_2) << " km" << endl;
        cout << "预计花费时间: " << fixed << setprecision(2) << g.calculatePathTime(path_2) << " min" << endl;
        cout << "总价格: " << g.calculatePathPrice(path_2) << " RMB" << endl;
        cout << "预计到达时间: "
             << 1900 + arrivalTime_tm2.tm_year << "年"
             << setfill('0') << setw(2) << 1 + arrivalTime_tm2.tm_mon << "月"
             << setfill('0') << setw(2) << arrivalTime_tm2.tm_mday << "日" << " "
             << setfill('0') << setw(2) << arrivalTime_tm2.tm_hour << ":"
             << setfill('0') << setw(2) << arrivalTime_tm2.tm_min << ":"
             << setfill('0') << setw(2) << arrivalTime_tm2.tm_sec << endl;

        result += "您的最短时间路径为: \n\n";
        for (auto station = path_2.begin(); station != path_2.end(); station++) {
            result += station->first + "(" + station->second + ")";
            if (next(station) != path_2.end() && next(station)->second != station->second) {
                result = result + " ==> " + "您需要换乘: " + next(station)->second;
            }
            if (next(station) != path_2.end()) {
                result += " -> ";
            }
        }
        result += "\n\n";
        result += "路程: " + to_string(g.calculatePathLength(path_2)) + " km\n";
        result += "预计花费时间: " + to_string(g.calculatePathTime(path_2)) + " min\n";
        result += "总价格: " + to_string(g.calculatePathPrice(path_2)) + " RMB\n";
        result += "预计到达时间: "
                  + to_string(1900 + arrivalTime_tm2.tm_year) + "年"
                  + to_string(1 + arrivalTime_tm2.tm_mon) + "月"
                  + to_string(arrivalTime_tm2.tm_mday) + "日 "
                  + to_string(arrivalTime_tm2.tm_hour) + ":"
                  + to_string(arrivalTime_tm2.tm_min) + ":"
                  + to_string(arrivalTime_tm2.tm_sec) + "\n";
    } else {
        result = "您的输入不合法!";
    }

    return result;
}
