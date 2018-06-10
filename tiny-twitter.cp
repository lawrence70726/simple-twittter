//
//  main.cpp
//  LeetCodePrac
//
//  Created by 王俊凱 on 2018/6/7.
//  Copyright © 2018 王俊凱. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>


class NODE{
    public:
    std::string tweetid;
    int userid;
    int no;
    NODE* next;
    NODE* prev;
};
class LinkedList{
    public:
    class NODE node;
    NODE* AddValue(NODE *head, int c,std::string a, int b){     //w
        NODE* ptr = head;
        NODE *m = new NODE;
        if(ptr==NULL){
            m->next = NULL;
            m->prev = head;
            m->tweetid = a;
            m->no = b;
            m->userid = c;
            head = m;
        }
        else{
            while(ptr->next){
                ptr = ptr->next;
            }
            m->next = NULL;
            m->tweetid = a;
            ptr->next = m;
            m->prev = ptr;
            m->no = b;
            m->userid = c;
        }
        return head;
    }
    NODE* DeleteNode(NODE* head,int num){   //w
        NODE* ptr = head;
        NODE* ptr1;
        if(ptr->userid==num)
            head = DeleteBottom(ptr);
        else{
            while(ptr){
                if(ptr->userid == num && !(ptr->next)){
                    ptr1 = ptr;
                    ptr->prev->next = NULL;
                    delete ptr1;
                }
                else if(ptr->userid == num){
                    ptr1 = ptr;
                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;
                    delete ptr1;
                }
                ptr = ptr->next;
            }
        }
        return head;
    }
    NODE* DeleteBottom(NODE* head){    //w
        NODE* ptr = head;
        head = head->next;
        head->prev = NULL;
        delete ptr;
        return head;
    }
    void PrintForward(NODE* head){     //w
        NODE* ptr = head;
        while(ptr){
            std::cout << ptr->tweetid << " ";
            ptr = ptr->next;
        }
        std::cout << std::endl;
    }
    void PrintBackward(NODE* head){    //w
        NODE* ptr = head;
        while(ptr->next)
            ptr = ptr->next;
        while(ptr){
            std::cout << ptr->tweetid << " ";
            ptr = ptr->prev;
        }
        std::cout << std::endl;
    }
    void RemoveLinkedList(NODE *head){   //w
        if(head){
            NODE *p,*q;
            p = head;
            q = head->next;
            while(p->next){
                delete p;
                p = q;
                q = q->next;
            }
            delete p;
        }
    }
    NODE* CopyList(NODE *head){  //w
        NODE* ptr = head;
        NODE* ptr1=NULL;
        while(ptr){
            ptr1 = AddValue(ptr1, ptr->userid,ptr->tweetid, ptr->no);
            ptr = ptr->next;
        }
        return ptr1;
    }
    NODE* ConnectList(NODE *l1,NODE *l2){    //w
        if(!l1 || !l2)
            return l1;
        NODE *ptr1, *ptr2;
        ptr1 = l1;
        ptr2 = l2;
        while(ptr1->next)
            ptr1 = ptr1->next;
        ptr1->next = ptr2;
        ptr2->prev = ptr1;
        return l1;
    }
    NODE* merge(NODE *first, NODE *second)   //w
    {
        if (!first)
            return second;
        if (!second)
            return first;
        if (first->no < second->no)
        {
            first->next = merge(first->next,second);
            first->next->prev = first;
            first->prev = NULL;
            return first;
        }
        else
        {
            second->next = merge(first,second->next);
            second->next->prev = second;
            second->prev = NULL;
            return second;
        }
    }
    NODE* MergeSort(NODE *head)   //w
    {
        if (!head || !head->next)
            return head;
        NODE *second = split(head);
        // Recur for left and right halves
        head = MergeSort(head);
        second = MergeSort(second);
        // Merge the two sorted halves
        return merge(head,second);
    }
    NODE* split(NODE *head)   //w
    {
        NODE *fast = head,*slow = head;
        while (fast->next && fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        NODE *temp = slow->next;
        slow->next = NULL;
        return temp;
    }
};
class twitter{
    public:
    twitter(){
        tweetNo = 0;
        for(int i=0;i<10;i++){
            userID[i] = NULL;
            ownFeed[i] = NULL;
            for(int j=0;j<10;j++)
                following[i][j] = -1;
        }
    }
    /** Compose a new tweet. Users from 0 to 9 */
    void postTweet(int userId, std::string tweetId) {        //w
        userID[userId] = linkedlist.AddValue(userID[userId],userId,tweetId,tweetNo);
        ownFeed[userId] = linkedlist.AddValue(ownFeed[userId],userId,tweetId, tweetNo);
        for(int i=0;i<10;i++){
            if(following[i][userId]==1){
                ownFeed[i] = linkedlist.AddValue(ownFeed[i],userId,tweetId, tweetNo);
            }
        }
        tweetNo++;
    }
    
    /** Retrieve the most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    std::vector<std::string> getNewsFeed(int userId) {     //w
        std::vector<std::string> a;
        if(ownFeed[userId]==NULL){
            std::cout << "No posts\n";
            return {};
        }
        NODE* ptr = ownFeed[userId];
        while(ptr->next)
            ptr = ptr->next;
        while(ptr){
            a.push_back(ptr->tweetid);
            ptr = ptr->prev;
        }
        return a;
    }
    
    std::vector<std::string> getPersonalFeed(int userId) {     //w
        std::vector<std::string> a;
        if(userID[userId]==NULL){
            std::cout << "No personal posts\n";
            return {};
        }
        NODE* ptr = userID[userId];
        while(ptr->next)
            ptr = ptr->next;
        while(ptr){
            a.push_back(ptr->tweetid);
            ptr = ptr->prev;
        }
        return a;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    //合併做排序
    void follow(int followerId, int followeeId) {
        if(following[followerId][followeeId]==1){
            std::cout << "Already followed\n";
            return;
        }
        NODE *q;
        q = linkedlist.CopyList(userID[followeeId]);
        ownFeed[followerId] = linkedlist.ConnectList(ownFeed[followerId],q);
        ownFeed[followerId] = linkedlist.MergeSort(ownFeed[followerId]);
        following[followerId][followeeId] = 1;
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    //拆開
    void unfollow(int followerId, int followeeId) {
        linkedlist.DeleteNode(ownFeed[followerId], followeeId);
        following[followerId][followeeId] = -1;
    }
    private:
    class LinkedList linkedlist;
    class NODE* userID[10]; //only personal feed
    class NODE* ownFeed[10]; //personal feed and followee's feed
    int following[10][10];
    int tweetNo;
};

int main(int argc, const char * argv[]) {
    class twitter tw;
    std::vector<std::string> newsfeed;
    std::string msg,end="\0";
    int userid, followid, unfollowid;
    char ch;
    while(1){
        std::cout << "Input username to login (0 to 9): " << std::endl;
        do{
            std::cin >> userid;
            if(userid<0 || userid>9)
                std::cout << "Invalid username!!!" << std::endl;
        }while(userid<0 || userid>9);
        std::cin.clear();
        std::cin.ignore();
        while(1){
            std::cout << "F: Follow  ";
            std::cout << "U: Unfollow  ";
            std::cout << "T: Post a tweet  ";
            std::cout << "G: Get newsfeed  " << std::endl;
            std::cout << "P: Personal information  ";
            std::cout << "C: Change a user  ";
            std::cout << "Q: Quit " << std::endl;
            std::cin >> ch;
            fflush(stdin);
            std::cin.sync();
            switch(ch){
                case 'F':  //p
                case 'f':
                    std::cout << "Who do you want to follow? (0 to 9) " << std::endl;
                    std::cin >> followid;
                    if(followid==userid){
                        std::cout << "Invalid input\n";
                        break;
                    }
                    tw.follow(userid, followid);
                    std::cout << "Followed\n";
                    break;
                case 'U':   //p
                case 'u':
                    std::cout << "Who do you want to unfollow? (0 to 9) " << std::endl;
                    std::cin >> unfollowid;
                    if(unfollowid==userid){
                        std::cout << "Invalid input\n";
                        break;
                    }
                    tw.unfollow(userid, unfollowid);
                    std::cout << "Unfollowed\n";
                    break;
                case 'T':
                case 't':
                    std::cout << "Type your message (Press ENTER to submit) " << std::endl;
                    std::cin.clear();
                    std::cin.ignore();
                    std::getline(std::cin, msg);
                    msg += end;
                    tw.postTweet(userid, msg);
                    break;
                case 'G':  //p
                case 'g':
                    newsfeed = tw.getNewsFeed(userid);
                    std::cout << "-----------------------------------\n";
                    for(int i=0;i<newsfeed.size();i++){
                        std::cout << newsfeed[i] << std::endl;
                        std::cout << "-----------------------------------\n";
                    }
                    break;
                case 'P':
                case 'p':
                    break;
                case 'C':
                case 'c':
                    break;
                case 'Q':
                case 'q':
                    std::cout << "Closed" << std::endl;
                    exit(0);
                    break;
                default:
                    std::cout << "Invalid input." << std::endl;
                    break;
            }
            if(ch=='c'||ch=='C'){
                std::cin.clear();
                std::cin.ignore();
                break;
            }
        }
    }
    return 0;
}

