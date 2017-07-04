#include <iostream>
#include <limits.h>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;
class Twitter {
    struct Tweet {
        int time;
        int id;
        Tweet(int time, int id) : time(time), id(id) {}
    } ;

    unordered_map<int, vector<Tweet>> tweets;
    unordered_map<int, set<int>> following;
    int time;

public:
    /** Initialize your data structure here. */
    Twitter() {
        tweets.clear();
        following.clear();
        time  = 0;
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        time ++;
        Tweet t(time, tweetId);
        tweets[userId].push_back(t);
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<pair<Tweet*, Tweet*>> h;
        for (auto & u : following[userId]) {
            auto & t = tweets[u];
            if (t.size() > 0) {
                h.emplace_back(t.data(), t.data()+t.size()-1);
            }
        }
        auto & t = tweets[userId];
        if (t.size() > 0) {
            h.emplace_back(t.data(), t.data() + t.size() -1);
        }

        auto f = [](pair<Tweet*, Tweet*>&x, pair<Tweet*, Tweet*>y) {
            return x.second->time < y.second->time;
        };
        make_heap(h.begin(), h.end(), f);

        int n = 10;
        vector<int> o;
        for (int i =0; i<n && !h.empty() ;i ++) {
            pop_heap(h.begin(), h.end(), f);
            auto &hb = h.back();
            o.push_back(hb.second->id);
            if (hb.first == hb.second) {
                h.pop_back();
            } else {
                hb.second --;
                push_heap(h.begin(), h.end(), f);
            }

        }
        return o;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followeeId == followerId) return;
        following[followerId].insert(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */

int main() {
    Twitter *obj = new Twitter();
    {
        int user_id = 1;
        int tweet_id = 5;
        obj->postTweet(user_id, tweet_id);
        vector<int> vec = obj->getNewsFeed(user_id);
        for (auto && t: vec) {
            cout << t << ",";
        }
        cout << endl;
        obj->follow(1, 2);
        obj->postTweet(2,  6);
        vec = obj->getNewsFeed(1);
        for (auto && t: vec) {
            cout << t << ",";
        }
        cout << endl;
        obj->unfollow(1, 2);
        vec = obj->getNewsFeed(1);
        for (auto && t: vec) {
            cout << t << ",";
        }
        cout << endl;
    }
    return 0;
}
