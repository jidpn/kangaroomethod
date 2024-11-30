#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <cmath>
int calculate_time_to_int(std::string str_cur_record);
int main()
{
    std::string file_name;
    std::cout << "探索するログファイルを指定" << std::endl;
    std::cin >> file_name ;
    int MIN_RECORD_LENGTH;
    std::cout << "レコードの長さの最低値を指定" << std::endl;
    std::cin >> MIN_RECORD_LENGTH ;
    int MAX_RECORD_DIFF;
    std::cout << "隣り合う日時の差の最高値を指定" << std::endl;
    std::cin >> MAX_RECORD_DIFF ;
    std::cout << "探索する日時を指定：" << std::endl;
    std::string str_target_record; // 探索するレコード
    std::cin >> str_target_record; // 探索するレコードを入力

    int target_record; // 探索するレコード
    target_record = calculate_time_to_int(str_target_record);
    std::string line;   
    std::string str_cur_record;
    int jump;
    int cur_record;
    std::vector<double> result;
    for(int i=0;i<100;i++){
        auto start = std::chrono::system_clock::now(); // 時間計測（start);
        std::ifstream ifs("log/"+file_name, std::ios::in ); // テスト用のファイルを読み込む
        while(getline(ifs,line)){
            std::stringstream valStream(line);
            std::getline(valStream,str_cur_record,' ');
            std::getline(valStream,str_cur_record,' ');
            std::getline(valStream,str_cur_record,' ');
            std::getline(valStream,str_cur_record,' ');
            str_cur_record = str_cur_record.substr(1,std::string::npos); // レコードの日時取得
            cur_record = calculate_time_to_int(str_cur_record); //　UNIXタイムスタンプに変換
            if(cur_record == target_record){
                std::cout << line << std::endl; // レコードが見つかった場合
            }
            jump = abs(target_record - cur_record) / MAX_RECORD_DIFF -1; // 現在位置のレコードと探索するレコードの距離を測定
            if(jump >= 1){
                ifs.seekg(sizeof(char) * jump * MIN_RECORD_LENGTH,std::ios::cur);
                getline(ifs,line);
            }
        }
        ifs.close();
        auto end = std::chrono::system_clock::now();  // 時間計測(end)
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();  //時間計算
        result.push_back(elapsed);
    }
    double sum = 0;
    double sum_double = 0;
    for(auto const elem : result){
        sum += elem;
        sum_double += elem * elem;
    }
    double avg = sum / 100;

    std::cout << "avg_time:" << avg << std::endl; //時間平均表示
    std::cout << "std_time:" << sqrt(sum_double / 100 - avg *avg) << std::endl; //時間標準偏差表示

}
int calculate_time_to_int(std::string str_cur_record){ // UNIXタイムススタンプに使う関数
    std::tm tm = {};
    std::istringstream ss(str_cur_record);
    ss >> std::get_time(&tm, "%d/%m/%Y:%H:%M:%S");
    int time = std::mktime(&tm);
    return time;
}