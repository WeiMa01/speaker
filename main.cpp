#include<iostream>
#include<map>
#include<vector>
#include <cstring>
#include <deque>
#include <functional>
#include <numeric>

using namespace std;
class speaker{
public:
    speaker(){
        name = "";
        score[0] = 0;
        score[1] = 0;
        score[2] = 0;
    }
    speaker(string name,int score1,int score2,int score3){
        this->name = name;
        score[0] = score1;
        score[1] = score2;
        score[2] = score3;
    }
private:
    string name;
    int score[3];
    int id;
public:
    int getId() const {
        return id;
    }

    void setId(int id) {
        speaker::id = id;
    }
    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        speaker::name = name;
    }
    void setScore(int index,int value){
        score[index] = value;
    }
    const int *getScore() const {
        return score;
    }

    friend ostream& operator<<(ostream &out,const speaker &s){
        out << "id:" << s.id <<" name: " <<s.name ;
        for (int i = 0; i < 3; ++i) {
            out << " socre" << i+1 << ":" << s.score[i];
        }
        return out;
    }
};

int GenSpeaker(map<int, speaker> &speakers, vector<int> &v1);

int speech_contest_draw(vector<int> &v);

int speech_contest(int index, vector<int> &v1, map<int, speaker> &speakers, vector<int> &v2);

int speech_contest_print(int index, vector<int> &v1, map<int, speaker> &speaker);

int main(){
    map<int,speaker> speakers;
    vector<int>  v1;  //第一轮名单
    vector<int>  v2;  //2
    vector<int>  v3;  // 3
    vector<int>  v4;  // 最后前三名
    //产生选手，得到名单
    GenSpeaker(speakers,v1);
    //test GenSpeaker
    //第1轮， 抽签，比赛， 查看结果
    speech_contest_draw(v1);
    speech_contest(0,v1,speakers,v2);
    speech_contest_print(0,v2,speakers);
    //第2轮， 抽签，比赛， 查看结果
    speech_contest_draw(v2);
    speech_contest(1,v2,speakers,v3);
    speech_contest_print(1,v3,speakers);
    //第3轮， 抽签，比赛， 查看结果
    speech_contest_draw(v3);
    speech_contest(2,v3,speakers,v4);
    speech_contest_print(2,v4,speakers);

    return 0;
}

int speech_contest_print(int index, vector<int> &v1, map<int, speaker> &speakers) {
    for (vector<int>::iterator it = v1.begin(); it !=v1.end() ; ++it) {
        map<int, speaker>::iterator  iter = speakers.find(*it);
        cout << iter->second << endl;
    }
}

int speech_contest(int index, vector<int> &v1, map<int, speaker> &speakers, vector<int> &v2) {
    //小组的比赛得分 记录下来，求出前三名和后三名
    multimap<int,int,greater<int>> multiMapGroup;//小组成绩
    int tmpCount = 0 ;
    for (vector<int>::iterator it = v1.begin(); it !=v1.end() ; ++it) {
        //十个评委打分打分
        tmpCount++;
        deque<int> dscore;
        for (int j = 0; j < 10; ++j) {
            int score = 50+rand()%50;
            dscore.push_back(score);
        }
        sort(dscore.begin(),dscore.end());
        dscore.pop_back();
        dscore.pop_front();
        //求平均分
        int scoresum = accumulate(dscore.begin(),dscore.end(),0);
        int scoreavg = scoresum/dscore.size();
        speakers[*it].setScore(index,scoreavg);
        multiMapGroup.insert(pair<int,int>(scoreavg,*it));

        //处理分组
        if(tmpCount & 6 == 0){
            cout << "小组的比赛成绩" << endl;
            for (multimap<int,int,greater<int>>::iterator mit = multiMapGroup.begin(); mit !=multiMapGroup.end() ; ++mit) {
                cout << mit->second  << "\t" << speakers[mit->second].getName()
                <<"\t" << mit->first<< endl;
            }
            //前三名晋级
            while(multiMapGroup.size() > 3){
                multimap<int,int,greater<int>>::iterator it1 = multiMapGroup.begin();
                v2.push_back(it1->second);
                multiMapGroup.erase(it1);
            }
            multiMapGroup.clear();//清空本小组比赛成绩
        }
    }
    return 0;
}

int speech_contest_draw(vector<int> &v) {
    random_shuffle(v.begin(),v.end());
    return 0;
}

int GenSpeaker(map<int, speaker> &speakers, vector<int> &v1) {
    string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    random_shuffle(str.begin(),str.end());
    for (int i = 0; i < 24; ++i) {
        class speaker tmp;
        string s1 = "选手";
        s1.push_back(str[i]);
        s1.push_back((char)(i+1));
        tmp.setName(s1);
        tmp.setId(i+1);
        speakers.insert(pair<int,speaker>(100+i,tmp));
    }
    for (int i = 0; i < 24; ++i) {
        v1.push_back(100+i);
    }
    return 0;
}

