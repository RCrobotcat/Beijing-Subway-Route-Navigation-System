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

//#define START "������" // ���
//#define END "���˻���" // �յ�

#define ONE "1����"
#define TWO "2����"
#define FOUR "4����"
#define FIVE "5����"
#define SIX "6����"
#define SEVEN "7����"
#define EIGHT "8����"
#define NINE "9����"
#define TEN "10����"
#define ELEVEN "11����"
#define THIRTEEN "13����"
#define FOURTEEN "14����"
#define FIFTEEN "15����"
#define SIXTEEN "16����"
#define SEVENTEEN "17����"
#define NINETEEN "19����"
#define CHANGPING "��ƽ��"
#define XIJIAO "������"
#define YANFANG "�෿��"
#define YIZHUANG "��ׯ��"
#define FANGSHAN "��ɽ��"
#define AIRPORT "�׶�������"
#define S1 "S1��"
#define DAXING "������"
#define DAXING_AIRPORT "���˻�����"
#define BATONG "��ͨ��"
#define YIZHUANG_T1 "��ׯ��T1��"

using namespace std;

unordered_map<string, float> lineVelocity; // ������·�ٶ�

// ����ͼ�Ĳ���
class graphOperation {
protected:
    // ����ͼ�Ľṹ
    unordered_map<string, vector<pair<pair<string, int>, pair<string, float>>>> adjList; // <վ��, <(����վ��, ����), (��·, �ٶ�)>>

public:
    // ��ӱ�(�������ٻ���·��)
    void addEdge(const string &from, const string &to, int weight, const string &line) {
        pair<string, float> lineInfo = make_pair(line, lineVelocity[line]);
        adjList[from].push_back(make_pair(make_pair(to, weight), lineInfo));
        adjList[to].push_back(make_pair(make_pair(from, weight), lineInfo));
        // ����ͼ,˫�����
    }

    // ���ļ��е��������·����������ͼ(�������ٻ���·��)
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

    // �����·
    void addLine(const string &line, const string &filename)
    {
        bool needAddLine = true;
        for (auto &station : adjList) {
            for(auto &edge : station.second)
            {
                if(edge.second.first == line)
                {
                    needAddLine = false;
                    break;
                }
            }
            if(!needAddLine) break;
        }

        if(needAddLine)
        {
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

            if(!line_exist)
            {
                cout << "������·��δ��ͨ���Ѿ�����ɾ��!" << endl;
            }
            else
            {
                cout << "�����·�ɹ�!" << endl;
            }
        }
        else
        {
            cout << "������·�Ѿ����������ĵ�����·��, �����ظ����!" << endl;
        }
    }

    // ɾ����·
    void deleteLine(const string &line) {
        bool line_exist = false;
        for (auto &station : adjList) {
            station.second.erase(remove_if(station.second.begin(), station.second.end(),
                                           [&](const pair<pair<string, int>, pair<string, float>> &edge) {
                                               if (edge.second.first == line) {
                                                   line_exist = true;
                                                   return true;
                                               }
                                               return false;
                                           }), station.second.end());
        }
        if(line_exist)
        {
            cout << "ɾ����·�ɹ�!" << endl;
        }
        else
        {
            cout << "������·��δ��ͨ���Ѿ�����ɾ��!" << endl;
        }
    }

    // �ж��Ƿ����ͨ·(����BFS)
    bool isPathExist(const string &start, const string &end) {
        unordered_set<string> visited;
        queue<string> q;
        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            for (const auto &edge : adjList[current]) {
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

    // ����Dijkstra�㷨�������ٻ��˵�·��
    vector<pair<string, string>> findLeastTransferPath(const string& start, const string& end) {
        unordered_map<string, int> transferCount; // ��¼���˴���

        using QueueElement = pair<pair<int, int>, string>; // <���˴���, �ܾ���, վ��>
        auto comp = [](const QueueElement& a, const QueueElement& b) {
            return (a.first.first > b.first.first
                    || (a.first.first == b.first.first && a.first.second > b.first.second));
        };
        priority_queue<QueueElement, vector<QueueElement>, decltype(comp)> q(comp); // С����,���ڼ�¼���˴������ܾ���

        // ��¼ǰ����·
        unordered_map<string, string> prevLine;
        // ��¼ǰ��վ��
        unordered_map<string, string> prev;

        unordered_map<string, int> distance; // ��¼����ÿ��վ����ܾ���

        // ���
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
                path.begin()->second = (path.begin() + 1)->second; // �����·���һ��վ����·��ͬ
                return path;
            }

            for (auto& edge : adjList[current]) {
                int newTransferCount = transferCount[current] + (edge.second.first != prevLine[current]
                                                                 ? 1 : 0);
                int newDistance = distance[current] + edge.first.second;
                if (transferCount.find(edge.first.first) == transferCount.end()
                    || newTransferCount < transferCount[edge.first.first]) {
                    transferCount[edge.first.first] = newTransferCount;
                    if(newDistance < distance[edge.first.first] || distance.find(edge.first.first) == distance.end()) {
                        distance[edge.first.first] = newDistance;
                    }
                    q.push(make_pair(make_pair(newTransferCount, newDistance),
                                     edge.first.first));
                    prev[edge.first.first] = current; // ��¼·��
                    prevLine[edge.first.first] = edge.second.first; // ��¼��·
                }
            }
        }

        return {}; // ���û��·��
    }

    // ����Dijkstra�㷨�������ʱ���·��
    vector<pair<string, string>> findShortestTimePath(const string& start, const string& end) {
        unordered_map<string, float> time;
        unordered_map<string, int> transferCount; // ��¼���˴���

        // ��¼ǰ����·
        unordered_map<string, string> prevLine;
        // ��¼ǰ��վ��
        unordered_map<string, string> prev;

        unordered_map<string, int> distance; // ��¼����ÿ��վ����ܾ���

        time[start] = 0;
        transferCount[start] = 0;
        distance[start] = 0;

        using QueueElement = pair<pair<int, int>, string>; // <��ʱ��, �ܾ���, վ��>
        auto comp = [](const QueueElement& a, const QueueElement& b) {
            return a.first.first > b.first.first || (a.first.first == b.first.first
                                                     && a.first.second > b.first.second);
        };
        priority_queue<QueueElement, vector<QueueElement>, decltype(comp)> queue(comp); // С����,���ڼ�¼��ʱ��

        queue.push(make_pair(make_pair(0, 0), start));

        while (!queue.empty()) {
            string current = queue.top().second;
            queue.pop();

            for (const auto& edge : adjList[current]) {
                int newTransferCount = transferCount[current] + (edge.second.first != prevLine[current] ? 1 : 0);
                float newTime = time[current] + (((((float) edge.first.second / 1000) / edge.second.second) * 60)
                                                 + 1 + (float) newTransferCount * 5);
                int newDistance = distance[current] + edge.first.second;
                if (time.find(edge.first.first) == time.end()
                    || newTime < time[edge.first.first]) {
                    time[edge.first.first] = newTime;
                    transferCount[edge.first.first] = newTransferCount;
                    if(newDistance < distance[edge.first.first] || distance.find(edge.first.first) == distance.end()) {
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
        path.begin()->second = (path.begin() + 1)->second; // �����·���һ��վ����·��ͬ
        return path;
    }

    // ����·������
    float calculatePathLength(const vector<pair<string, string>>& path) {
        float length = 0;
        for (auto station = path.begin(); station != path.end(); station++) {
            if (next(station) != path.end()) {
                for (const auto& edge : adjList[station->first]) {
                    if (edge.first.first == next(station)->first) {
                        length += (float) edge.first.second / 1000;
                        break;
                    }
                }
            }
        }
        return length;
    }

    // ����·��ʱ��
    float calculatePathTime(const vector<pair<string, string>>& path) {
        float time = 0;
        for (auto station = path.begin(); station != path.end(); station++) {
            if (next(station) != path.end()) {
                for (const auto& edge : adjList[station->first]) {
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

    // ����·���۸�
    int calculatePathPrice(vector<pair<string, string>>& path) {

        int price_DaXing = 0, price_ShouDu = 0, price;
        for(const auto& station : path) {
            if(station.second == DAXING_AIRPORT)
                price_DaXing = 35;
            if(station.second == AIRPORT)
                price_ShouDu = 25;
        }
        // ɾ�����˻������׶������йص�վ��
        path.erase(remove_if(path.begin(), path.end(),
                             [&](const pair<string, string>& station) {
                                 return station.first == DAXING_AIRPORT || station.first == AIRPORT;
                             }), path.end());

        float length = calculatePathLength(path);
        if(length <= 6)
            price = 3;
        else if(length > 6 && length <= 12)
            price = 4;
        else if(length > 12 && length <= 22)
            price = 5;
        else if(length > 22 && length <= 32)
            price = 6;
        else price = 6 + (length - 32) / 20;

        price = price + price_DaXing + price_ShouDu;

        return price;
    }
};

// �洢����ÿ����·���ٶ�
void convertLinesVelocity()
{
    lineVelocity = {
            {ONE, 75},
            {TWO, 80},
            {FOUR, 90},
            {FIVE, 80},
            {SIX, 100},
            {SEVEN, 80},
            {EIGHT, 80},
            {NINE, 80},
            {TEN, 80},
            {ELEVEN, 100},
            {THIRTEEN, 75},
            {FOURTEEN, 75},
            {FIFTEEN, 80},
            {SIXTEEN, 80},
            {SEVENTEEN, 100},
            {NINETEEN, 120},
            {CHANGPING, 100},
            {XIJIAO, 70},
            {YANFANG, 80},
            {YIZHUANG, 80},
            {FANGSHAN, 100},
            {AIRPORT, 110},
            {S1, 100},
            {DAXING, 80},
            {DAXING_AIRPORT, 160},
            {BATONG, 80},
            {YIZHUANG_T1, 80}
    };
}

// ��ӡ
class print : public graphOperation{
public:
//    void printGraph() {
//        for (const auto &p: adjList) {
//            cout << p.first << " -> ";
//            for (const auto &q: p.second) {
//                cout << "(" << q.first.first << ", " << q.first.second << ", " << q.second.first << ") ";
//            }
//            cout << endl;
//        }
//    } // �����ڽӱ����ͼ(debug��)
//
//    void print_specific_station(const string &station) {
//        cout << station << "->";
//        for (const auto &q: adjList[station])
//            cout << "(" << q.first.first << ", " << q.first.second << ", " << q.second.first << ") ";
//        cout << endl;
//    } // ����վ������ض�վ����ڽӱ�(debug��)
//
//    void print_line(const string &line) {
//        cout << line << ":\n";
//        for (const auto &p: adjList) {
//            for (const auto &q: p.second) {
//                if (q.second.first == line)
//                    cout << p.first << " -> " << q.first.first;
//            }
//        }
//    } // ������·����ض���·���ڽӱ�(debug��)

    static void printPath(const vector<pair<string, string>>& path) {
        for (auto station = path.begin(); station != path.end(); station++) {
            cout << station->first << "(" << station->second << ")";
            if (next(station) != path.end() && next(station)->second != station->second) {
                cout << " ==> " << "����Ҫ����: " << next(station)->second;
            }
            if (next(station) != path.end()) {
                cout << " -> ";
            }
        }
        cout << endl;
    } // ���·��
};

int main() {
    convertLinesVelocity();

    graphOperation g;
    g.importFromFile("../subway.txt");

    // ��ӻ�ɾ����·
    while(true)
    {
        cout << "����Ҫ��ӻ�ɾ��һ��������·��? (Y/N)" << endl;
        char choice;
        cin >> choice;
        cin.ignore(); // ���Ի��з�
        if(choice == 'Y' || choice == 'y')
        {
            cout << "������һ������Ҫ��ӻ�ɾ���ĵ�����·(����: ��ƽ��): ";
            string line;
            getline(cin, line);
            cout << "��ϣ�����������·����ɾ��������·? (A/D)" << endl;
            char choice2;
            cin >> choice2;
            cin.ignore();
            if(choice2 == 'A' || choice2 == 'a')
            {
                g.addLine(line, "../subway.txt");
            }
            else if(choice2 == 'D' || choice2 == 'd')
            {
                g.deleteLine(line);
            }
        }
        else if(choice == 'N' || choice == 'n')
        {
            break;
        }
    }

    // ���������յ�
    string utf8_start, utf8_end;
    cout << "��������ʼվ(����: ������): " << endl;
    getline(cin, utf8_start);
    cout << "�������յ�վ(����: ɳ��): " << endl;
    getline(cin, utf8_end);

//    string utf8_start = convertToUtf8(start, "GBK");
//    string utf8_end = convertToUtf8(end, "GBK");

    // �ж��Ƿ����ͨ·
    if(!g.isPathExist(utf8_start, utf8_end))
    {
        cout << "���! ����վ��֮�䲻���ڵ���ͨ·! ����ӵ�����·ʹ����վ֮�����ͨ·��" << endl;
        return 0;
    }

    vector<pair<string, string>> path_1 = g.findLeastTransferPath(utf8_start, utf8_end);
    vector<pair<string, string>> path_2 = g.findShortestTimePath(utf8_start, utf8_end);

    // ���ڵ�ǰϵͳ�ĵ�ǰ����/ʱ��
    time_t now = time(0);
    tm ltm = *localtime(&now);

    // ����Ԥ�Ƶ���ʱ��
    chrono::system_clock::time_point NOW = chrono::system_clock::now();

    // ����·��1��Ԥ�Ƶ���ʱ��
    int travelTimeInSeconds1 = static_cast<int>(g.calculatePathTime(path_1) * 60);
    chrono::seconds travelDuration1(travelTimeInSeconds1);

    chrono::system_clock::time_point arrivalTime1 = NOW + travelDuration1;

    time_t arrivalTime_t1 = chrono::system_clock::to_time_t(arrivalTime1);
    tm arrivalTime_tm1 = *localtime(&arrivalTime_t1);

    // ����·��2��Ԥ�Ƶ���ʱ��
    int travelTimeInSeconds2 = static_cast<int>(g.calculatePathTime(path_2) * 60);
    chrono::seconds travelDuration2(travelTimeInSeconds2);

    chrono::system_clock::time_point arrivalTime2 = NOW + travelDuration2;

    time_t arrivalTime_t2 = chrono::system_clock::to_time_t(arrivalTime2);
    tm arrivalTime_tm2 = *localtime(&arrivalTime_t2);

    cout << "��ѡ����������: (����1��2 -- 1. ���ٻ���·�� 2. ���ʱ��·��)" << endl;
    int choice_1;
    cin >> choice_1;

    cout << "��ǰʱ��Ϊ: "
         << 1900 + ltm.tm_year << "��"
         << setfill('0') << setw(2) << 1 + ltm.tm_mon << "��"
         << setfill('0') << setw(2) << ltm.tm_mday << "��" << " "
         << setfill('0') << setw(2) << ltm.tm_hour << ":"
         << setfill('0') << setw(2) << ltm.tm_min << ":"
         << setfill('0') << setw(2) << ltm.tm_sec << endl;

    if(choice_1 == 1) {
        cout << "1. ���ٻ���·��Ϊ:" << endl;
        print::printPath(path_1);
        cout << "·��: " << g.calculatePathLength(path_1) << " km" << endl;
        cout << "Ԥ�ƻ���ʱ��: " << fixed << setprecision(2) << g.calculatePathTime(path_1) << " min" << endl;
        cout << "�ܼ۸�: " << g.calculatePathPrice(path_1) << " RMB" << endl;
        cout << "Ԥ�Ƶ���ʱ��: "
             << 1900 + arrivalTime_tm1.tm_year << "��"
             << setfill('0') << setw(2) << 1 + arrivalTime_tm1.tm_mon << "��"
             << setfill('0') << setw(2) << arrivalTime_tm1.tm_mday << "��" << " "
             << setfill('0') << setw(2) << arrivalTime_tm1.tm_hour << ":"
             << setfill('0') << setw(2) << arrivalTime_tm1.tm_min << ":"
             << setfill('0') << setw(2) << arrivalTime_tm1.tm_sec << endl;
    }
    else if(choice_1 == 2) {
        cout << "2. ���ʱ��·��Ϊ:" << endl;
        print::printPath(path_2);
        cout << "·��: " << g.calculatePathLength(path_2) << " km" << endl;
        cout << "Ԥ�ƻ���ʱ��: " << fixed << setprecision(2) << g.calculatePathTime(path_2) << " min" << endl;
        cout << "�ܼ۸�: " << g.calculatePathPrice(path_2) << " RMB" << endl;
        cout << "Ԥ�Ƶ���ʱ��: "
             << 1900 + arrivalTime_tm2.tm_year << "��"
             << setfill('0') << setw(2) << 1 + arrivalTime_tm2.tm_mon << "��"
             << setfill('0') << setw(2) << arrivalTime_tm2.tm_mday << "��" << " "
             << setfill('0') << setw(2) << arrivalTime_tm2.tm_hour << ":"
             << setfill('0') << setw(2) << arrivalTime_tm2.tm_min << ":"
             << setfill('0') << setw(2) << arrivalTime_tm2.tm_sec << endl;
    }
    else{
        cout << "���벻�Ϸ�!" << endl;
    }

    return 0;
}
