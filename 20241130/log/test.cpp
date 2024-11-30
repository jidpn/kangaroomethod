#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// ランダムなIPアドレスを生成
string generateRandomIP() {
    return "127.0.0." + to_string(rand() % 255 + 1);  // ランダムなIPアドレス
}

// ランダムなHTTPメソッドを生成
string generateRandomMethod() {
    int method = rand() % 2;
    return method == 0 ? "GET" : "POST";
}

// ランダムなURLを生成
string generateRandomURL() {
    return "/page" + to_string(rand() % 5 + 1) + ".html";
}

// ランダムなHTTPステータスコードを生成
int generateRandomStatusCode() {
    return 200 + rand() % 5;  // 200〜205 のステータスコード
}

// ランダムなレスポンスサイズを生成
int generateRandomSize() {
    return rand() % 5000 + 100;  // 100〜5100 のレスポンスサイズ
}

int main() {
    std::cout << "作成するログサイズを選択" << std::endl;
    int log_size; 
    std::cin >> log_size;
    std::cout << "作成するログファイル名を選択" << std::endl;
    std::string log_filename;
    std::cin >> log_filename;
    std::cout << "外れ値の値の大きさを選択" << std::endl;
    int skip;
    std::cin >> skip;

    srand(time(0));  // ランダムシードを初期化

    // ログファイルのパスを指定
    ofstream logFile(log_filename);

    if (!logFile) {
        cerr << "Failed to open log file!" << std::endl;
        return 1;
    }
    time_t now = time(0);
    // ダミーアクセスログをlog_size行生成
    for (int i = 0; i < log_size; ++i) {
        if(i == log_size /2 && skip != 0){
            now += skip;
        }else{
    	    now += rand() % (5+6) - 3;
        }
        tm* localtm = localtime(&now);
        stringstream date;
        date << "[" << localtm->tm_mday << "/"
             << 1 + localtm->tm_mon << "/"
             << 1900 + localtm->tm_year << ":"
             << localtm->tm_hour << ":"
             << localtm->tm_min << ":"
             << localtm->tm_sec << " +0900]";

        // ランダムなログエントリを生成
        logFile << generateRandomIP() << " - - " << date.str()
                << " \"" << generateRandomMethod() << " "
                << generateRandomURL() << " HTTP/1.1\" "
                << generateRandomStatusCode() << " "
                << generateRandomSize() << endl;
    }

    logFile.close();
    cout << "Log file created successfully!" << endl;

    return 0;
}

