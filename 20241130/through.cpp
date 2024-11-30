#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <string>
#include <ctime>
#include <iomanip>
int calculate_time_to_int(std::string str_cur_record){
    std::tm tm = {};
    std::istringstream ss(str_cur_record);
    ss >> std::get_time(&tm, "%d/%m/%Y:%H:%M:%S");
    int time = std::mktime(&tm);
    return time;
}
int main()
{
    std::string file_name;
    std::cout << "走査するログファイルを指定" << std::endl;
    std::cin >> file_name ;
    std::ifstream ifs("log/"+file_name, std::ios::in ); // テスト用のファイルを読み込む
    std::string line;   
    std::string str_cur_record;
    int max_label_difference = 0;
    int current_diff;
    int cur_record;
    int cur_record_length;
    auto start = std::chrono::system_clock::now(); // 時間計測（start);
    getline(ifs,line); // 一番初めだけ whileの外でとる
    int min_record_length = line.size();
    std::stringstream valStream(line);
    std::getline(valStream,str_cur_record,' ');
    std::getline(valStream,str_cur_record,' ');
    std::getline(valStream,str_cur_record,' ');
    std::getline(valStream,str_cur_record,' ');
    str_cur_record = str_cur_record.substr(1,std::string::npos);
    int prev_record = calculate_time_to_int(str_cur_record);
    while(getline(ifs,line)){
        cur_record_length = line.size();
        if(cur_record_length < min_record_length){
            min_record_length = cur_record_length;
        }
        std::stringstream valStream(line);
        std::getline(valStream,str_cur_record,' ');
        std::getline(valStream,str_cur_record,' ');
        std::getline(valStream,str_cur_record,' ');
        std::getline(valStream,str_cur_record,' ');
        str_cur_record = str_cur_record.substr(1,std::string::npos); // 現在のレコードの日時
        cur_record = calculate_time_to_int(str_cur_record); // 日時をUNIXタイムに変換
        current_diff = abs(cur_record - prev_record); // 隣り合う日時の差
        if(current_diff > max_label_difference){
            max_label_difference = current_diff; // 日時の差の最大値を更新
        }
        prev_record = cur_record;
    }
    std::cout << "min_record_length:" << min_record_length << std::endl; // レコードの最小長
    std::cout << "max_label_difference:" << max_label_difference << std::endl; //　隣り合あうレコード間の差の最大値 
    auto end = std::chrono::system_clock::now();  // 時間計測(end)
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();  //時間計算
    std::cout << elapsed << std::endl; //時間表示
    return 0;
}
