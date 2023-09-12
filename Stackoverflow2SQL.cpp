/*
    Copyright(c) 2023 Tyler Crockett | Macdaddy4sure.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissionsand
    limitations under the License.
*/

#include "Stackoverflow2SQL.h"

using namespace std;

int main()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* result;
    string input;
    bool boolean = false;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    while (!boolean)
    {
        system("cls");

        cout << endl;
        cout << "============= Main Menu =============" << endl;
        cout << "| 1. Parse Stackexchange            |" << endl;
        cout << "-------------------------------------" << endl;
        cout << "| 0. Settings                       |" << endl;
        cout << "-------------------------------------" << endl;
        cout << endl;
        if (conn)
            cout << "MySQL Connection: True" << endl;
        else
            cout << "MySQL Connection: False" << endl;
        cout << "MySQL Hostname: " << mysql_hostname << endl;
        cout << "MySQL Username: " << mysql_username << endl;
        cout << "MySQL Password: " << mysql_password << endl;
        cout << "MySQL Database: " << mysql_database << endl;
        cout << "Stackoverflow Location: " << stackoverflow_location << endl;
        cout << endl;
        cout << "Your Selection: ";
        getline(cin, input);

        if (input == "1")
        {
            Parser();
        }
        if (input == "2")
        {
            
        }
        if (input == "0")
        {
            Settings();
        }
    }
}

void Settings()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* result;
    string input;
    bool boolean = false;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    while (!boolean)
    {
        system("cls");

        cout << endl;
        cout << "============= Settings ==============" << endl;
        cout << "| 1. Set MySQL Hostname             |" << endl;
        cout << "| 2. Set MySQL Username             |" << endl;
        cout << "| 3. Set MySQL Password             |" << endl;
        cout << "| 4. Set MySQL Database             |" << endl;
        cout << "| 5. Stackoverflow Location         |" << endl;
        cout << "-------------------------------------" << endl;
        cout << "| 0. Settings                       |" << endl;
        cout << "-------------------------------------" << endl;
        cout << endl;
        if (conn)
            cout << "MySQL Connection: True" << endl;
        else
            cout << "MySQL Connection: False" << endl;
        cout << "MySQL Hostname: " << mysql_hostname << endl;
        cout << "MySQL Username: " << mysql_username << endl;
        cout << "MySQL Password: " << mysql_password << endl;
        cout << "MySQL Database: " << mysql_database << endl;
        cout << "Stackoverflow Location: " << stackoverflow_location << endl;
        cout << endl;
        cout << "Your Selection: ";
        getline(cin, input);

        if (input == "1")
        {
            bool boolean2 = false;

            while (!boolean2)
            {
                system("cls");

                cout << "MySQL Hostname: ";
                getline(cin, input);

                if (input != "")
                {
                    mysql_hostname = input;
                    boolean2 = true;
                }
            }
        }
        if (input == "2")
        {
            bool boolean2 = false;

            while (!boolean2)
            {
                system("cls");

                cout << "MySQL Username: ";
                getline(cin, input);

                if (input != "")
                {
                    mysql_username = input;
                    boolean2 = true;
                }
            }
        }
        if (input == "3")
        {
            bool boolean2 = false;

            while (!boolean2)
            {
                system("cls");

                cout << "MySQL Password: ";
                getline(cin, input);

                if (input != "")
                {
                    mysql_password = input;
                    boolean2 = true;
                }
            }
        }
        if (input == "4")
        {
            bool boolean2 = false;

            while (!boolean2)
            {
                system("cls");

                cout << "MySQL Database: ";
                getline(cin, input);

                if (input != "")
                {
                    mysql_database = input;
                    boolean2 = true;
                }
            }
        }
        if (input == "5")
        {
            bool boolean2 = false;

            while (!boolean2)
            {
                system("cls");

                cout << "Stackoverflow Dump Location: ";
                getline(cin, input);

                if (input != "")
                {
                    stackoverflow_location = input;
                    boolean2 = true;
                }
            }
        }
        if (input == "0")
        {
            boolean = true;
        }
    }
}

void Parser()
{
    string table;
    string temp_path;
    string temp_filename;

    for (auto& q : directory_iterator(stackoverflow_location.c_str()))
    {
        temp_path = q.path().string();

        PostsParser(temp_path);
        CommentsParser(temp_path);
        PostLinksParser(temp_path);
        PostsHistoryParser(temp_path);
        UsersParser(temp_path);
        TagsParser(temp_path);
        VotesParser(temp_path);
        BadgesParser(temp_path);
    }
}

void PostsParser(string folder_location)
{
    string input;
    string temp_path;
    string temp_path2;
    string temp_filename;
    string Id = "";
    string PostTypeId = "";
    string AcceptedAnswerId = "";
    string CreationDate = "";
    string Score = "";
    string ViewCount = "";
    string Body = "";
    string OwnerUserId = "";
    string LastEditorUserId = "";
    string LastEditDate = "";
    string LastActivityDate = "";
    string Title = "";
    string Tags = "";
    string AnswerCount = "";
    string CommentCount = "";
    string FavoriteCount = "";
    string ContentLicense = "";
    string table = "_Posts";
    long progress = 0;

    fstream file;

    // Progress
    long count;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (auto& q : directory_iterator(folder_location.c_str()))
    {
        temp_path = q.path().string();
        temp_filename = q.path().filename().string();

        if (temp_filename == "Posts.xml")
        {
            file.open(temp_path.c_str());

            if (file.is_open())
            {
                // Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
                while (getline(file, input))
                {
                    system("cls");

                    //cout << input << endl;

                    Id.clear();
                    PostTypeId.clear();
                    AcceptedAnswerId.clear();
                    CreationDate.clear();
                    Score.clear();
                    ViewCount.clear();
                    Body.clear();
                    OwnerUserId.clear();
                    LastEditorUserId.clear();
                    LastEditDate.clear();
                    LastActivityDate.clear();
                    Title.clear();
                    Tags.clear();
                    AnswerCount.clear();
                    CommentCount.clear();
                    FavoriteCount.clear();
                    ContentLicense.clear();

                    for (int x = 0; x <= input.length(); x++)
                    {
                        if (input[x] == '<' && input[x + 1] == 'r' && input[x + 2] == 'o' && input[x + 3] == 'w' && input[x + 4] == ' ' && input[x + 5] == 'I' && input[x + 6] == 'd' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Id += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'P' && input[x + 1] == 'o' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'T' && input[x + 5] == 'y' && input[x + 6] == 'p' && input[x + 7] == 'e' && input[x + 8] == 'I' && input[x + 9] == 'd' && input[x + 10] == '=' && input[x + 11] == '\"')
                        {
                            for (int y = x + 12; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    PostTypeId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'A' && input[x + 1] == 'c' && input[x + 2] == 'c' && input[x + 3] == 'e' && input[x + 4] == 'p' && input[x + 5] == 't' && input[x + 6] == 'e' && input[x + 7] == 'd' && input[x + 8] == 'A' && input[x + 9] == 'n' && input[x + 10] == 's' && input[x + 11] == 'w' && input[x + 12] == 'e' && input[x + 13] == 'r' && input[x + 14] == 'I' && input[x + 15] == 'd' && input[x + 16] == '=' && input[x + 17] == '\"')
                        {
                            for (int y = x + 18; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    AcceptedAnswerId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'r' && input[x + 2] == 'e' && input[x + 3] == 'a' && input[x + 4] == 't' && input[x + 5] == 'i' && input[x + 6] == 'o' && input[x + 7] == 'n' && input[x + 8] == 'D' && input[x + 9] == 'a' && input[x + 10] == 't' && input[x + 11] == 'e' && input[x + 12] == '=' && input[x + 13] == '\"')
                        {
                            for (int y = x + 14; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    CreationDate += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'S' && input[x + 1] == 'c' && input[x + 2] == 'o' && input[x + 3] == 'r' && input[x + 4] == 'e' && input[x + 5] == '=' && input[x + 6] == '\"')
                        {
                            for (int y = x + 7; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Score += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'V' && input[x + 1] == 'i' && input[x + 2] == 'e' && input[x + 3] == 'w' && input[x + 4] == 'C' && input[x + 5] == 'o' && input[x + 6] == 'u' && input[x + 7] == 'n' && input[x + 8] == 't' && input[x + 9] == '=' && input[x + 10] == '\"')
                        {
                            for (int y = x + 11; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    ViewCount += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'B' && input[x + 1] == 'o' && input[x + 2] == 'd' && input[x + 3] == 'y' && input[x + 4] == '=' && input[x + 5] == '\"')
                        {
                            for (int y = x + 6; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Body += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'O' && input[x + 1] == 'w' && input[x + 2] == 'n' && input[x + 3] == 'e' && input[x + 4] == 'r' && input[x + 5] == 'U' && input[x + 6] == 's' && input[x + 7] == 'e' && input[x + 8] == 'r' && input[x + 9] == 'I' && input[x + 10] == 'd' && input[x + 11] == '=' && input[x + 12] == '\"')
                        {
                            for (int y = x + 13; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    OwnerUserId += input[y];
                                }
                                else
                                    break;

                            }
                        }
                        if (input[x] == 'L' && input[x + 1] == 'a' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'E' && input[x + 5] == 'd' && input[x + 6] == 'i' && input[x + 7] == 't' && input[x + 8] == 'o' && input[x + 9] == 'r' && input[x + 10] == 'U' && input[x + 11] == 's' && input[x + 12] == 'e' && input[x + 13] == 'r' && input[x + 14] == 'I' && input[x + 15] == 'd' && input[x + 16] == '=' && input[x + 17] == '\"')
                        {
                            for (int y = x + 18; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    LastEditorUserId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'L' && input[x + 1] == 'a' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'E' && input[x + 5] == 'd' && input[x + 6] == 'i' && input[x + 7] == 't' && input[x + 8] == 'D' && input[x + 9] == 'a' && input[x + 10] == 't' && input[x + 11] == 'e' && input[x + 12] == '=' && input[x + 13] == '\"')
                        {
                            for (int y = x + 14; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    LastEditDate += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'L' && input[x + 1] == 'a' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'A' && input[x + 5] == 'c' && input[x + 6] == 't' && input[x + 7] == 'i' && input[x + 8] == 'v' && input[x + 9] == 'i' && input[x + 10] == 't' && input[x + 11] == 'y' && input[x + 12] == 'D' && input[x + 13] == 'a' && input[x + 14] == 't' && input[x + 15] == 'e' && input[x + 16] == '=' && input[x + 17] == '\"')
                        {
                            for (int y = x + 18; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    LastActivityDate += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'T' && input[x + 1] == 'i' && input[x + 2] == 't' && input[x + 3] == 'l' && input[x + 4] == 'e' && input[x + 5] == '=' && input[x + 6] == '\"')
                        {
                            for (int y = x + 7; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Title += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'T' && input[x + 1] == 'a' && input[x + 2] == 'g' && input[x + 3] == 's' && input[x + 4] == '=' && input[x + 5] == '\"')
                        {
                            for (int y = x + 6; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Tags += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'A' && input[x + 1] == 'n' && input[x + 2] == 's' && input[x + 3] == 'w' && input[x + 4] == 'e' && input[x + 5] == 'r' && input[x + 6] == 'C' && input[x + 7] == 'o' && input[x + 8] == 'u' && input[x + 9] == 'n' && input[x + 10] == 't' && input[x + 11] == '=' && input[x + 12] == '\"')
                        {
                            for (int y = x + 13; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    AnswerCount += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'o' && input[x + 2] == 'm' && input[x + 3] == 'm' && input[x + 4] == 'e' && input[x + 5] == 'n' && input[x + 6] == 't' && input[x + 7] == 'C' && input[x + 8] == 'o' && input[x + 9] == 'u' && input[x + 10] == 'n' && input[x + 11] == 't' && input[x + 12] == '=' && input[x + 13] == '\"')
                        {
                            for (int y = x + 14; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    CommentCount += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'F' && input[x + 1] == 'a' && input[x + 2] == 'v' && input[x + 3] == 'o' && input[x + 4] == 'r' && input[x + 5] == 'i' && input[x + 6] == 't' && input[x + 7] == 'e' && input[x + 8] == 'C' && input[x + 9] == 'o' && input[x + 10] == 'u' && input[x + 11] == 'n' && input[x + 12] == 't' && input[x + 13] == '=' && input[x + 14] == '\"')
                        {
                            for (int y = x + 15; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    FavoriteCount += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'o' && input[x + 2] == 'n' && input[x + 3] == 't' && input[x + 4] == 'e' && input[x + 5] == 'n' && input[x + 6] == 't' && input[x + 7] == 'L' && input[x + 8] == 'i' && input[x + 9] == 'c' && input[x + 10] == 'e' && input[x + 11] == 'n' && input[x + 12] == 's' && input[x + 13] == 'e' && input[x + 14] == '=' && input[x + 15] == '\"')
                        {
                            for (int y = x + 16; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    ContentLicense += input[y];
                                }
                                else
                                    break;
                            }
                        }
                    }

                    folder_location = getStem(folder_location, table);
                    
                    cout << "Table: " << folder_location << endl;
                    cout << "Id: " << Id << endl;
                    cout << "PostTypeId: " << PostTypeId << endl;
                    cout << "AcceptedAnswerId: " << AcceptedAnswerId << endl;
                    cout << "CreationDate: " << CreationDate << endl;
                    cout << "Score: " << Score << endl;
                    cout << "ViewCount: " << ViewCount << endl;
                    cout << "Body: " << Body << endl;
                    cout << "OwnerUserId: " << OwnerUserId << endl;
                    cout << "LastEditorUserId: " << LastEditorUserId << endl;
                    cout << "LastEditDate: " << LastEditDate << endl;
                    cout << "LastActivityDate: " << LastActivityDate << endl;
                    cout << "Title: " << Title << endl;
                    cout << "Tags: " << Tags << endl;
                    cout << "AnswerCount: " << AnswerCount << endl;
                    cout << "CommentCount: " << CommentCount << endl;
                    cout << "FavoriteCount: " << FavoriteCount << endl;
                    cout << "ContentLicense: " << ContentLicense << endl;
                    cout << "Progress: " << progress << endl;

                    //cin.get();

                    PostsMySQL(folder_location, Id, PostTypeId, AcceptedAnswerId, CreationDate, Score, ViewCount, Body, OwnerUserId, LastEditorUserId, LastEditDate, LastActivityDate, Title, Tags, AnswerCount, CommentCount, FavoriteCount, ContentLicense);
                }
            }

            file.close();

            progress++;
        }
    }
}

void CommentsParser(string folder_location)
{
    string input;
    string temp_path;
    string temp_path2;
    string temp_filename;
    string Id = "";
    string PostId = "";
    string Score = "";
    string Text = "";
    string CreationDate = "";
    string UserId = "";
    string ContentLicense = "";
    string table = "_Comments";
    long progress = 0;

    fstream file;

    // Progress
    long count;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (auto& q : directory_iterator(folder_location.c_str()))
    {
        temp_path = q.path().string();
        temp_filename = q.path().filename().string();

        if (temp_filename == "Comments.xml")
        {
            file.open(temp_path.c_str());

            if (file.is_open())
            {
                // Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
                while (getline(file, input))
                {
                    system("cls");

                    /*cout << input << endl;*/

                    Id.clear();
                    PostId.clear();
                    Score.clear();
                    Text.clear();
                    CreationDate.clear();
                    UserId.clear();
                    ContentLicense.clear();

                    for (int x = 0; x <= input.length(); x++)
                    {
                        if (input[x] == '<' && input[x + 1] == 'r' && input[x + 2] == 'o' && input[x + 3] == 'w' && input[x + 4] == ' ' && input[x + 5] == 'I' && input[x + 6] == 'd' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Id += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'P' && input[x + 1] == 'o' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'I' && input[x + 5] == 'd' && input[x + 6] == '=' && input[x + 7] == '\"')
                        {
                            for (int y = x + 8; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    PostId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'S' && input[x + 1] == 'c' && input[x + 2] == 'o' && input[x + 3] == 'r' && input[x + 4] == 'e' && input[x + 5] == '=' && input[x + 6] == '\"')
                        {
                            for (int y = x + 7; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Score += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'T' && input[x + 1] == 'e' && input[x + 2] == 'x' && input[x + 3] == 't' && input[x + 4] == '=' && input[x + 5] == '\"')
                        {
                            for (int y = x + 6; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Text += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'r' && input[x + 2] == 'e' && input[x + 3] == 'a' && input[x + 4] == 't' && input[x + 5] == 'i' && input[x + 6] == 'o' && input[x + 7] == 'n' && input[x + 8] == 'D' && input[x + 9] == 'a' && input[x + 10] == 't' && input[x + 11] == 'e' && input[x + 12] == '=' && input[x + 13] == '\"')
                        {
                            for (int y = x + 14; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    CreationDate += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'U' && input[x + 1] == 's' && input[x + 2] == 'e' && input[x + 3] == 'r' && input[x + 4] == 'I' && input[x + 5] == 'd' && input[x + 6] == '=' && input[x + 7] == '\"')
                        {
                            for (int y = x + 8; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    UserId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'o' && input[x + 2] == 'n' && input[x + 3] == 't' && input[x + 4] == 'e' && input[x + 5] == 'n' && input[x + 6] == 't' && input[x + 7] == 'L' && input[x + 8] == 'i' && input[x + 9] == 'c' && input[x + 10] == 'e' && input[x + 11] == 'n' && input[x + 12] == 's' && input[x + 13] == 'e' && input[x + 14] == '=' && input[x + 15] == '\"')
                        {
                            for (int y = x + 16; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    ContentLicense += input[y];
                                }
                                else
                                    break;
                            }
                        }
                    }

                    folder_location = getStem(folder_location, table);

                    cout << "Table: " << folder_location << endl;
                    cout << "Id: " << Id << endl;
                    cout << "PostId: " << PostId << endl;
                    cout << "Score: " << Score << endl;
                    cout << "Text: " << Text << endl;
                    cout << "CreationDate: " << CreationDate << endl;
                    cout << "UserId: " << UserId << endl;
                    cout << "ContentLicense: " << ContentLicense << endl;

                    CommentsMySQL(folder_location, Id, PostId, Score, Text, CreationDate, UserId, ContentLicense);
                }

                cout << "Progress: " << progress << endl;
            }

            file.close();

            progress++;
        }
    }
}

void PostLinksParser(string folder_location)
{
    string input;
    string temp_path;
    string temp_path2;
    string temp_filename;
    string Id = "";
    string CreationDate = "";
    string PostId = "";
    string RelatedPostId = "";
    string LinkTypeId = "";
    string table = "_PostLinks";
    long progress = 0;

    fstream file;

    // Progress
    long count;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (auto& q : directory_iterator(folder_location.c_str()))
    {
        temp_path = q.path().string();
        temp_filename = q.path().filename().string();

        if (temp_filename == "PostLinks.xml")
        {
            file.open(temp_path.c_str());

            if (file.is_open())
            {
                // Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
                while (getline(file, input))
                {
                    system("cls");

                    cout << input << endl;

                    Id.clear();
                    CreationDate.clear();
                    PostId.clear();
                    RelatedPostId.clear();
                    LinkTypeId.clear();

                    for (int x = 0; x <= input.length(); x++)
                    {
                        if (input[x] == '<' && input[x + 1] == 'r' && input[x + 2] == 'o' && input[x + 3] == 'w' && input[x + 4] == ' ' && input[x + 5] == 'I' && input[x + 6] == 'd' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"' && input[y + 1] != ' ' && input[y + 2] != 'P' && input[y + 3] != 'o' && input[y + 4] != 's' && input[y + 5] != 't' && input[y + 6] != 'I' && input[y + 7] != 'd')
                                {
                                    Id += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'r' && input[x + 2] == 'e' && input[x + 3] == 'a' && input[x + 4] == 't' && input[x + 5] == 'i' && input[x + 6] == 'o' && input[x + 7] == 'n' && input[x + 8] == 'D' && input[x + 9] == 'a' && input[x + 10] == 't' && input[x + 11] == 'e' && input[x + 12] == '=' && input[x + 13] == '\"')
                        {
                            for (int y = x + 14; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    CreationDate += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'P' && input[x + 1] == 'o' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'I' && input[x + 5] == 'd' && input[x + 6] == '=' && input[x + 7] == '\"')
                        {
                            for (int y = x + 8; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    PostId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'R' && input[x + 1] == 'e' && input[x + 2] == 'l' && input[x + 3] == 'a' && input[x + 4] == 't' && input[x + 5] == 'e' && input[x + 6] == 'd' && input[x + 7] == 'P' && input[x + 8] == 'o' && input[x + 9] == 's' && input[x + 10] == 't' && input[x + 11] == 'I' && input[x + 12] == 'd' && input[x + 13] == '=' && input[x + 14] == '\"')
                        {
                            for (int y = x + 15; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    RelatedPostId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'L' && input[x + 1] == 'i' && input[x + 2] == 'n' && input[x + 3] == 'k' && input[x + 4] == 'T' && input[x + 5] == 'y' && input[x + 6] == 'p' && input[x + 7] == 'e' && input[x + 8] == 'I' && input[x + 9] == 'd' && input[x + 10] == '=' && input[x + 11] == '\"')
                        {
                            for (int y = x + 12; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    LinkTypeId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                    }

                    folder_location = getStem(folder_location, table);

                    cout << "Table: " << folder_location << endl;
                    cout << "Id: " << Id << endl;
                    cout << "CreationDate: " << CreationDate << endl;
                    cout << "PostId: " << PostId << endl;
                    cout << "RelatedPostId: " << RelatedPostId << endl;
                    cout << "LinkTypeId: " << LinkTypeId << endl;

                    PostsLinksMySQL(folder_location, Id, CreationDate, PostId, RelatedPostId, LinkTypeId);
                }

                cout << "Progress: " << progress << endl;
            }

            file.close();

            progress++;
        }
    }
}

void PostsHistoryParser(string folder_location)
{
    string input;
    string temp_path;
    string temp_path2;
    string temp_filename;
    string Id = "";
    string PostHistoryTypeId = "";
    string PostId = "";
    string CreationDate = "";
    string UserId = "";
    string Text = "";
    string ContentLicense = "";
    string table = "_PostsHistory";
    long progress = 0;

    fstream file;

    // Progress
    long count;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (auto& q : directory_iterator(folder_location.c_str()))
    {
        temp_path = q.path().string();
        temp_filename = q.path().filename().string();

        if (temp_filename == "PostsHistory.xml")
        {
            file.open(temp_path.c_str());

            if (file.is_open())
            {
                // Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
                while (getline(file, input))
                {
                    //cout << input << endl;

                    system("cls");

                    Id.clear();
                    PostHistoryTypeId.clear();
                    PostId.clear();
                    CreationDate.clear();
                    UserId.clear();
                    Text.clear();
                    ContentLicense.clear();

                    for (int x = 0; x <= input.length(); x++)
                    {
                        if (input[x] == '<' && input[x + 1] == 'r' && input[x + 2] == 'o' && input[x + 3] == 'w' && input[x + 4] == ' ' && input[x + 5] == 'I' && input[x + 6] == 'd' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"' && input[y + 1] != ' ' && input[y + 2] != 'P' && input[y + 3] != 'o' && input[y + 4] != 's' && input[y + 5] != 't')
                                {
                                    Id += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'P' && input[x + 1] == 'o' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'H' && input[x + 5] == 'i' && input[x + 6] == 's' && input[x + 7] == 't' && input[x + 8] == 'o' && input[x + 9] == 'r' && input[x + 10] == 'y' && input[x + 11] == 'T' && input[x + 12] == 'y' && input[x + 13] == 'p' && input[x + 14] == 'e' && input[x + 15] == 'I' && input[x + 16] == 'd' && input[x + 17] == '=' && input[x + 18] == '\"')
                        {
                            for (int y = x + 19; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    PostHistoryTypeId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'P' && input[x + 1] == 'o' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'I' && input[x + 5] == 'd' && input[x + 6] == '=' && input[x + 7] == '\"')
                        {
                            for (int y = x + 8; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    PostId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'r' && input[x + 2] == 'e' && input[x + 3] == 'a' && input[x + 4] == 't' && input[x + 5] == 'i' && input[x + 6] == 'o' && input[x + 7] == 'n' && input[x + 8] == 'D' && input[x + 9] == 'a' && input[x + 10] == 't' && input[x + 11] == 'e' && input[x + 12] == '=' && input[x + 13] == '\"')
                        {
                            for (int y = x + 14; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    CreationDate += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'U' && input[x + 1] == 's' && input[x + 2] == 'e' && input[x + 3] == 'r' && input[x + 4] == 'I' && input[x + 5] == 'd' && input[x + 6] == '=' && input[x + 7] == '\"')
                        {
                            for (int y = x + 8; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    UserId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'T' && input[x + 1] == 'e' && input[x + 2] == 'x' && input[x + 3] == 't' && input[x + 4] == '=' && input[x + 5] == '\"')
                        {
                            for (int y = x + 6; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Text += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'o' && input[x + 2] == 'n' && input[x + 3] == 't' && input[x + 4] == 'e' && input[x + 5] == 'n' && input[x + 6] == 't' && input[x + 7] == 'L' && input[x + 8] == 'i' && input[x + 9] == 'c' && input[x + 10] == 'e' && input[x + 11] == 'n' && input[x + 12] == 's' && input[x + 13] == 'e' && input[x + 14] == '=' && input[x + 15] == '\"')
                        {
                            for (int y = x + 16; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    ContentLicense += input[y];
                                }
                                else
                                    break;
                            }
                        }
                    }

                    folder_location = getStem(folder_location, table);

                    cout << "Table: " << folder_location << endl;
                    cout << "Id: " << Id << endl;
                    cout << "PostHistoryTypeId: " << PostHistoryTypeId << endl;
                    cout << "PostId: " << PostId << endl;
                    cout << "CreationDate: " << CreationDate << endl;
                    cout << "UserId: " << UserId << endl;
                    cout << "Text: " << Text << endl;
                    cout << "ContentLicense: " << ContentLicense << endl;

                    PostsHistoryMySQL(folder_location, Id, PostHistoryTypeId, PostId, CreationDate, UserId, Text, ContentLicense);
                }

                cout << "Progress: " << progress << endl;
            }

            file.close();

            progress++;
        }
    }
}

void UsersParser(string folder_location)
{
    string input;
    string temp_path;
    string temp_path2;
    string temp_filename;
    string Id = "";
    string Reputation = "";
    string CreationDate = "";
    string DisplayName = "";
    string LastAccessDate = "";
    string Location = "";
    string AboutMe = "";
    string Views = "";
    string UpVotes = "";
    string DownVotes = "";
    string AccountId = "";
    string table = "_Users";
    long progress = 0;

    fstream file;

    // Progress
    long count;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (auto& q : directory_iterator(folder_location.c_str()))
    {
        temp_path = q.path().string();
        temp_filename = q.path().filename().string();

        if (temp_filename == "Users.xml")
        {
            file.open(temp_path.c_str());

            if (file.is_open())
            {
                // Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
                while (getline(file, input))
                {
                    //cout << input << endl;

                    system("cls");

                    Id.clear();
                    Reputation.clear();
                    CreationDate.clear();
                    DisplayName.clear();
                    LastAccessDate.clear();
                    Location.clear();
                    AboutMe.clear();
                    Views.clear();
                    UpVotes.clear();
                    DownVotes.clear();
                    AccountId.clear();

                    for (int x = 0; x <= input.length(); x++)
                    {
                        if (input[x] == '<' && input[x + 1] == 'r' && input[x + 2] == 'o' && input[x + 3] == 'w' && input[x + 4] == ' ' && input[x + 5] == 'I' && input[x + 6] == 'd' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Id += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'R' && input[x + 1] == 'e' && input[x + 2] == 'p' && input[x + 3] == 'u' && input[x + 4] == 't' && input[x + 5] == 'a' && input[x + 6] == 't' && input[x + 7] == 'i' && input[x + 8] == 'o' && input[x + 9] == 'n' && input[x + 10] == '=' && input[x + 11] == '\"')
                        {
                            for (int y = x + 12; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Reputation += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'r' && input[x + 2] == 'e' && input[x + 3] == 'a' && input[x + 4] == 't' && input[x + 5] == 'i' && input[x + 6] == 'o' && input[x + 7] == 'n' && input[x + 8] == 'D' && input[x + 9] == 'a' && input[x + 10] == 't' && input[x + 11] == 'e' && input[x + 12] == '=' && input[x + 13] == '\"')
                        {
                            for (int y = x + 14; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    CreationDate += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'D' && input[x + 1] == 'i' && input[x + 2] == 's' && input[x + 3] == 'p' && input[x + 4] == 'l' && input[x + 5] == 'a' && input[x + 6] == 'y' && input[x + 7] == 'N' && input[x + 8] == 'a' && input[x + 9] == 'm' && input[x + 10] == 'e' && input[x + 11] == '=' && input[x + 12] == '\"')
                        {
                            for (int y = x + 13; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    DisplayName += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'L' && input[x + 1] == 'a' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'A' && input[x + 5] == 'c' && input[x + 6] == 'c' && input[x + 7] == 'e' && input[x + 8] == 's' && input[x + 9] == 's' && input[x + 10] == 'D' && input[x + 11] == 'a' && input[x + 12] == 't' && input[x + 13] == 'e' && input[x + 14] == '=' && input[x + 15] == '\"')
                        {
                            for (int y = x + 16; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    LastAccessDate += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'L' && input[x + 1] == 'o' && input[x + 2] == 'c' && input[x + 3] == 'a' && input[x + 4] == 't' && input[x + 5] == 'i' && input[x + 6] == 'o' && input[x + 7] == 'n' && input[x + 8] == '=' && input[x + 9] == '\"')
                        {
                            for (int y = x + 10; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Location += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'A' && input[x + 1] == 'b' && input[x + 2] == 'o' && input[x + 3] == 'u' && input[x + 4] == 't' && input[x + 5] == 'M' && input[x + 6] == 'e' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    AboutMe += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'V' && input[x + 1] == 'i' && input[x + 2] == 'e' && input[x + 3] == 'w' && input[x + 4] == 's' && input[x + 5] == '=' && input[x + 6] == '\"')
                        {
                            for (int y = x + 7; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Views += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'U' && input[x + 1] == 'p' && input[x + 2] == 'V' && input[x + 3] == 'o' && input[x + 4] == 't' && input[x + 5] == 'e' && input[x + 6] == 's' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    UpVotes += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'D' && input[x + 1] == 'o' && input[x + 2] == 'w' && input[x + 3] == 'n' && input[x + 4] == 'V' && input[x + 5] == 'o' && input[x + 6] == 't' && input[x + 7] == 'e' && input[x + 8] == 's' && input[x + 9] == '=' && input[x + 10] == '\"')
                        {
                            for (int y = x + 11; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    DownVotes += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'A' && input[x + 1] == 'c' && input[x + 2] == 'c' && input[x + 3] == 'o' && input[x + 4] == 'u' && input[x + 5] == 'n' && input[x + 6] == 't' && input[x + 7] == 'I' && input[x + 8] == 'd' && input[x + 9] == '=' && input[x + 10] == '\"')
                        {
                            for (int y = x + 11; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    AccountId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                    }

                    folder_location = getStem(folder_location, table);

                    cout << "Table: " << folder_location << endl;
                    cout << "Id: " << Id << endl;
                    cout << "Reputation: " << Reputation << endl;
                    cout << "CreationDate: " << CreationDate << endl;
                    cout << "DisplayName: " << DisplayName << endl;
                    cout << "LastAccessDate: " << LastAccessDate << endl;
                    cout << "Location: " << Location << endl;
                    cout << "AboutMe: " << AboutMe << endl;
                    cout << "Views: " << Views << endl;
                    cout << "UpVotes: " << UpVotes << endl;
                    cout << "DownVotes: " << DownVotes << endl;
                    cout << "AccountId: " << AccountId << endl;

                    UsersMySQL(folder_location, Id, Reputation, CreationDate, DisplayName, LastAccessDate, Location, AboutMe, Views, UpVotes, DownVotes, AccountId);
                }

                cout << "Progress: " << progress << endl;
            }

            file.close();

            progress++;
        }
    }
}

void TagsParser(string folder_location)
{
    string input;
    string temp_path;
    string temp_path2;
    string temp_filename;
    string Id = "";
    string TagName = "";
    string Count = "";
    string ExcerptPostId = "";
    string WikiPostId = "";
    string table = "Tags";
    long progress = 0;

    fstream file;

    // Progress
    long count;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (auto& q : directory_iterator(folder_location.c_str()))
    {
        temp_path = q.path().string();
        temp_filename = q.path().filename().string();

        if (temp_filename == "Tags.xml")
        {
            file.open(temp_path.c_str());

            if (file.is_open())
            {
                // Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
                while (getline(file, input))
                {
                    //cout << input << endl;

                    system("cls");

                    Id.clear();
                    TagName.clear();
                    Count.clear();
                    ExcerptPostId.clear();
                    WikiPostId.clear();

                    for (int x = 0; x <= input.length(); x++)
                    {
                        if (input[x] == '<' && input[x + 1] == 'r' && input[x + 2] == 'o' && input[x + 3] == 'w' && input[x + 4] == ' ' && input[x + 5] == 'I' && input[x + 6] == 'd' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Id += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'T' && input[x + 1] == 'a' && input[x + 2] == 'g' && input[x + 3] == 'N' && input[x + 4] == 'a' && input[x + 5] == 'm' && input[x + 6] == 'e' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    TagName += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'o' && input[x + 2] == 'u' && input[x + 3] == 'n' && input[x + 4] == 't' && input[x + 5] == '=' && input[x + 6] == '\"')
                        {
                            for (int y = x + 7; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Count += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'E' && input[x + 1] == 'x' && input[x + 2] == 'c' && input[x + 3] == 'e' && input[x + 4] == 'r' && input[x + 5] == 'p' && input[x + 6] == 't' && input[x + 7] == 'P' && input[x + 8] == 'o' && input[x + 9] == 's' && input[x + 10] == 't' && input[x + 11] == 'I' && input[x + 12] == 'd' && input[x + 13] == '=' && input[x + 14] == '\"')
                        {
                            for (int y = x + 15; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    ExcerptPostId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'W' && input[x + 1] == 'i' && input[x + 2] == 'k' && input[x + 3] == 'i' && input[x + 4] == 'P' && input[x + 5] == 'o' && input[x + 6] == 's' && input[x + 7] == 't' && input[x + 8] == 'I' && input[x + 9] == 'd' && input[x + 10] == '=' && input[x + 11] == '\"')
                        {
                            for (int y = x + 12; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    WikiPostId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                    }

                    folder_location = getStem(folder_location, table);

                    cout << "Table: " << folder_location << endl;
                    cout << "Id: " << Id << endl;
                    cout << "TagName: " << TagName << endl;
                    cout << "Count: " << Count << endl;
                    cout << "ExcerptPostId: " << ExcerptPostId << endl;
                    cout << "WikiPostId: " << WikiPostId << endl;

                    TagsMySQL(folder_location, Id, TagName, Count, ExcerptPostId, WikiPostId);
                }

                cout << "Progress: " << progress << endl;
            }

            file.close();

            progress++;
        }
    }
}

void VotesParser(string folder_location)
{
    string input;
    string temp_path;
    string temp_path2;
    string temp_filename;
    string Id = "";
    string PostId = "";
    string VoteTypeId = "";
    string UserId = "";
    string CreationDate = "";
    string table = "_Votes";
    long progress = 0;

    fstream file;

    // Progress
    long count;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (auto& q : directory_iterator(folder_location.c_str()))
    {
        temp_path = q.path().string();
        temp_filename = q.path().filename().string();

        if (temp_filename == "Votes.xml")
        {
            file.open(temp_path.c_str());

            if (file.is_open())
            {
                // Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
                while (getline(file, input))
                {
                    //cout << input << endl;

                    system("cls");

                    Id.clear();
                    PostId.clear();
                    VoteTypeId.clear();
                    UserId.clear();
                    CreationDate.clear();

                    for (int x = 0; x <= input.length(); x++)
                    {
                        if (input[x] == '<' && input[x + 1] == 'r' && input[x + 2] == 'o' && input[x + 3] == 'w' && input[x + 4] == ' ' && input[x + 5] == 'I' && input[x + 6] == 'd' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Id += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'P' && input[x + 1] == 'o' && input[x + 2] == 's' && input[x + 3] == 't' && input[x + 4] == 'I' && input[x + 5] == 'd' && input[x + 6] == '=' && input[x + 7] == '\"')
                        {
                            for (int y = x + 8; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    PostId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'V' && input[x + 1] == 'o' && input[x + 2] == 't' && input[x + 3] == 'e' && input[x + 4] == 'T' && input[x + 5] == 'y' && input[x + 6] == 'p' && input[x + 7] == 'e' && input[x + 8] == 'I' && input[x + 9] == 'd' && input[x + 10] == '=' && input[x + 11] == '\"')
                        {
                            for (int y = x + 12; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    VoteTypeId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'U' && input[x + 1] == 's' && input[x + 2] == 'e' && input[x + 3] == 'r' && input[x + 4] == 'I' && input[x + 5] == 'd' && input[x + 6] == '=' && input[x + 7] == '"')
                        {
                            for (int y = x + 8; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    UserId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'r' && input[x + 2] == 'e' && input[x + 3] == 'a' && input[x + 4] == 't' && input[x + 5] == 'i' && input[x + 6] == 'o' && input[x + 7] == 'n' && input[x + 8] == 'D' && input[x + 9] == 'a' && input[x + 10] == 't' && input[x + 11] == 'e' && input[x + 12] == '=' && input[x + 13] == '\"')
                        {
                            for (int y = x + 14; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    CreationDate += input[y];
                                }
                                else
                                    break;
                            }
                        }
                    }

                    folder_location = getStem(folder_location, table);

                    cout << "Table: " << folder_location << endl;
                    cout << "Id: " << Id << endl;
                    cout << "PostId: " << PostId << endl;
                    cout << "VoteTypeId: " << VoteTypeId << endl;
                    cout << "UserId: " << UserId << endl;
                    cout << "CreationDate: " << CreationDate << endl;

                    VotesMySQL(folder_location, Id, PostId, VoteTypeId, UserId, CreationDate);
                }

                cout << "Progress: " << progress << endl;
            }

            file.close();

            progress++;
        }
    }
}

void BadgesParser(string folder_location)
{
    string input;
    string temp_path;
    string temp_path2;
    string temp_filename;
    string Id = "";
    string UserId = "";
    string Name = "";
    string Date = "";
    string Class = "";
    string table = "_Badges";
    long progress = 0;

    fstream file;

    // Progress
    long count;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (auto& q : directory_iterator(folder_location.c_str()))
    {
        temp_path = q.path().string();
        temp_filename = q.path().filename().string();

        if (temp_filename == "Badges.xml")
        {
            file.open(temp_path.c_str());

            if (file.is_open())
            {
                // Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
                while (getline(file, input))
                {
                    //cout << input << endl;

                    system("cls");

                    Id.clear();
                    UserId.clear();
                    Name.clear();
                    Date.clear();
                    Class.clear();

                    for (int x = 0; x <= input.length(); x++)
                    {
                        if (input[x] == '<' && input[x + 1] == 'r' && input[x + 2] == 'o' && input[x + 3] == 'w' && input[x + 4] == ' ' && input[x + 5] == 'I' && input[x + 6] == 'd' && input[x + 7] == '=' && input[x + 8] == '\"')
                        {
                            for (int y = x + 9; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Id += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'U' && input[x + 1] == 's' && input[x + 2] == 'e' && input[x + 3] == 'r' && input[x + 4] == 'I' && input[x + 5] == 'd' && input[x + 6] == '=' && input[x + 7] == '\"')
                        {
                            for (int y = x + 8; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    UserId += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'N' && input[x + 1] == 'a' && input[x + 2] == 'm' && input[x + 3] == 'e' && input[x + 4] == '=' && input[x + 5] == '\"')
                        {
                            for (int y = x + 6; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Name += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'D' && input[x + 1] == 'a' && input[x + 2] == 't' && input[x + 3] == 'e' && input[x + 4] == '=' && input[x + 5] == '\"')
                        {
                            for (int y = x + 6; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Date += input[y];
                                }
                                else
                                    break;
                            }
                        }
                        if (input[x] == 'C' && input[x + 1] == 'l' && input[x + 2] == 'a' && input[x + 3] == 's' && input[x + 4] == 's' && input[x + 5] == '=' && input[x + 6] == '\"')
                        {
                            for (int y = x + 7; y <= input.length(); y++)
                            {
                                if (input[y] != '\"')
                                {
                                    Class += input[y];
                                }
                                else
                                    break;
                            }
                        }
                    }

                    folder_location = getStem(folder_location, table);

                    cout << "Table: " << folder_location << endl;
                    cout << "Id: " << Id << endl;
                    cout << "UserId: " << UserId << endl;
                    cout << "Name: " << Name << endl;
                    cout << "Date: " << Date << endl;
                    cout << "Class: " << Class << endl;

                    BadgesMySQL(folder_location, Id, UserId, Name, Date, Class);
                }

                cout << "Progress: " << progress << endl;
            }

            file.close();

            progress++;
        }
    }
}

void PostsMySQL(string site, string Id, string PostTypeId, string AcceptedAnswerId, string CreationDate, string Score, string ViewCount, string Body, string OwnerUserId, string LastEditorUserId, string LastEditDate, string LastActivityDate, string Title, string Tags, string AnswerCount, string CommentCount, string FavoriteCount, string ContentLicense)
{
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_RES* result;
    MYSQL_ROW row;
    string sql1;
    string sql2;
    string table2;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn2, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    //Title = ReplaceSpaces(Title);
    //Title = ToLowercase(Title);
    Title = fixCharacterSyntax(Title);
    //Body = ReplaceSpaces(Body);
    //Body = ToLowercase(Body);
    Body = fixCharacterSyntax(Body);

    if (conn)
    {
        site += "_Posts";
        //cout << "site: " << site << endl;
        sql1 = "CREATE TABLE IF NOT EXISTS `";
        sql1 += site.c_str();
        sql1 += "`(Id TEXT, PostTypeId TEXT, AcceptedAnswerId TEXT, CreationDate TEXT, Score TEXT, ViewCount TEXT, Body TEXT, OwnerUserId TEXT, LastEditorUserId TEXT, LastEditDate TEXT, LastActivityDate TEXT, Title TEXT, Tags TEXT, AnswerCount TEXT, CommentCount TEXT, FavoriteCount TEXT, ContentLicense TEXT);";
        //cout << "SQL1: " << sql1 << endl;
        mysql_query(conn, sql1.c_str());
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
    }

    if (conn2)
    {
        sql2 = "INSERT INTO `";
        sql2 += site.c_str();
        sql2 += "`(Id, PostTypeId, AcceptedAnswerId, CreationDate, Score, ViewCount, Body, OwnerUserId, LastEditorUserId, LastEditDate, LastActivityDate, Title, Tags, AnswerCount, CommentCount, FavoriteCount, ContentLicense) VALUES(\"";
        sql2 += Id.c_str();
        sql2 += "\", \"";
        sql2 += PostTypeId.c_str();
        sql2 += "\", \"";
        sql2 += AcceptedAnswerId.c_str();
        sql2 += "\", \"";
        sql2 += CreationDate.c_str();
        sql2 += "\", \"";
        sql2 += Score.c_str();
        sql2 += "\", \"";
        sql2 += ViewCount.c_str();
        sql2 += "\", \"";
        sql2 += Body.c_str();
        sql2 += "\", \"";
        sql2 += OwnerUserId.c_str();
        sql2 += "\", \"";
        sql2 += LastEditorUserId.c_str();
        sql2 += "\", \"";
        sql2 += LastEditDate.c_str();
        sql2 += "\", \"";
        sql2 += LastActivityDate.c_str();
        sql2 += "\", \"";
        sql2 += Title.c_str();
        sql2 += "\", \"";
        sql2 += Tags.c_str();
        sql2 += "\", \"";
        sql2 += AnswerCount.c_str();
        sql2 += "\", \"";
        sql2 += CommentCount.c_str();
        sql2 += "\", \"";
        sql2 += FavoriteCount.c_str();
        sql2 += "\", \"";
        sql2 += ContentLicense.c_str();
        sql2 += "\");";

        /*cout << "SQL2: " << sql2 << endl;*/
        mysql_query(conn2, sql2.c_str());

        fprintf(stderr, "%s\n", mysql_error(conn2));
        //cin.get();
        mysql_close(conn2);
    }
}

void CommentsMySQL(string site, string Id, string PostId, string Score, string Text, string CreationDate, string UserId, string ContentLicense)
{
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_RES* result;
    MYSQL_ROW row;
    string sql1;
    string sql2;
    string table = site;
    table += "_comments";

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn2, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    //Text = ReplaceSpaces(Text);
    //Text = ToLowercase(Text);
    Text = fixCharacterSyntax(Text);

    if (conn)
    {
        sql1 = "CREATE TABLE IF NOT EXISTS `";
        sql1 += table.c_str();
        sql1 += "`(Id TEXT, PostId TEXT, Score TEXT, Text_1 TEXT, CreationDate TEXT, UserId TEXT, ContentLicense TEXT);";
        //cout << "SQL1: " << sql1 << endl;
        mysql_query(conn, sql1.c_str());
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
    }

    if (conn2)
    {
        sql2 = "INSERT INTO `";
        sql2 += table.c_str();
        sql2 += "`(Id, PostId, Score, Text_1, CreationDate, UserId, ContentLicense) VALUES(\"";
        sql2 += Id.c_str();
        sql2 += "\", \"";
        sql2 += PostId.c_str();
        sql2 += "\", \"";
        sql2 += Score.c_str();
        sql2 += "\", \"";
        sql2 += Text.c_str();
        sql2 += "\", \"";
        sql2 += CreationDate.c_str();
        sql2 += "\", \"";
        sql2 += UserId.c_str();
        sql2 += "\", \"";
        sql2 += ContentLicense.c_str();
        sql2 += "\");";

        //cout << "SQL2: " << sql2 << endl;
        mysql_query(conn2, sql2.c_str());

        fprintf(stderr, "%s\n", mysql_error(conn2));
        //cin.get();
        mysql_close(conn2);
    }
}

void PostsLinksMySQL(string site, string Id, string CreationDate, string PostId, string RelatedPostId, string LinkTypeId)
{
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_RES* result;
    MYSQL_ROW row;
    string sql1;
    string sql2;
    string table2;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn2, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    if (conn)
    {
        site += "_PostLinks";
        sql1 = "CREATE TABLE IF NOT EXISTS `";
        sql1 += site.c_str();
        sql1 += "`(Id TEXT, CreationDate TEXT, PostId TEXT, RelatedPostId TEXT, LinkTypeId TEXT);";
        //cout << "SQL1: " << sql1 << endl;
        mysql_query(conn, sql1.c_str());
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
    }

    if (conn2)
    {
        sql2 = "INSERT INTO `";
        sql2 += site.c_str();
        sql2 += "`(Id, CreationDate, PostId, RelatedPostId, LinkTypeId) VALUES(\"";
        sql2 += Id.c_str();
        sql2 += "\", \"";
        sql2 += CreationDate.c_str();
        sql2 += "\", \"";
        sql2 += PostId.c_str();
        sql2 += "\", \"";
        sql2 += RelatedPostId.c_str();
        sql2 += "\", \"";
        sql2 += LinkTypeId.c_str();
        sql2 += "\");";

        //cout << "SQL2: " << sql2 << endl;
        mysql_query(conn2, sql2.c_str());

        fprintf(stderr, "%s\n", mysql_error(conn2));
        //cin.get();
        mysql_close(conn2);
    }
}

void PostsHistoryMySQL(string site, string Id, string PostHistoryTypeId, string PostId, string CreationDate, string UserId, string Text, string ContentLicense)
{
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_RES* result;
    MYSQL_ROW row;
    string sql1;
    string sql2;
    string table2;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn2, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    //Text = ReplaceSpaces(Text);
    //Text = ToLowercase(Text);
    Text = fixCharacterSyntax(Text);

    if (conn)
    {
        site += "_PostsHistory";
        sql1 = "CREATE TABLE IF NOT EXISTS `";
        sql1 += site.c_str();
        sql1 += "`(Id TEXT, PostHistoryTypeId TEXT, PostId TEXT, CreationDate TEXT, UserId TEXT, Text_1, ContentLicense TEXT);";
        //cout << "SQL1: " << sql1 << endl;
        mysql_query(conn, sql1.c_str());
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
    }

    if (conn2)
    {
        sql2 = "INSERT INTO `";
        sql2 += site.c_str();
        sql2 += "`(Id, PostHistoryTypeId, PostId, CreationDate, UserId, Text_1, ContentLicense) VALUES(\"";
        sql2 += Id.c_str();
        sql2 += "\", \"";
        sql2 += PostHistoryTypeId.c_str();
        sql2 += "\", \"";
        sql2 += PostId.c_str();
        sql2 += "\", \"";
        sql2 += CreationDate.c_str();
        sql2 += "\", \"";
        sql2 += UserId.c_str();
        sql2 += "\", \"";
        sql2 += Text.c_str();
        sql2 += "\", \"";
        sql2 += ContentLicense.c_str();
        sql2 += "\");";

        //cout << "SQL2: " << sql2 << endl;
        mysql_query(conn2, sql2.c_str());

        fprintf(stderr, "%s\n", mysql_error(conn2));
        //cin.get();
        mysql_close(conn2);
    }
}

void UsersMySQL(string site, string Id, string Reputation, string CreationDate, string DisplayName, string LastAccessDate, string Location, string AboutMe, string Views, string UpVotes, string DownVotes, string AccountId)
{
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_RES* result;
    MYSQL_ROW row;
    string sql1;
    string sql2;
    string table2;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn2, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    //AboutMe = ReplaceSpaces(AboutMe);
    //AboutMe = ToLowercase(AboutMe);
    AboutMe = fixCharacterSyntax(AboutMe);
    DisplayName = fixCharacterSyntax(DisplayName);

    if (conn)
    {
        site += "_Users";
        sql1 = "CREATE TABLE IF NOT EXISTS `";
        sql1 += site.c_str();
        sql1 += "`(Id TEXT, Reputation TEXT, CreationDate TEXT, DisplayName TEXT, LastAccessDate TEXT, Location TEXT, AboutMe TEXT, Views TEXT, UpVotes TEXT, DownVotes TEXT, AccountId TEXT);";
        //cout << "SQL1: " << sql1 << endl;
        mysql_query(conn, sql1.c_str());
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
    }

    if (conn2)
    {
        sql2 = "INSERT INTO `";
        sql2 += site.c_str();
        sql2 += "`(Id, Reputation, CreationDate, DisplayName, LastAccessDate, Location, AboutMe, Views, UpVotes, DownVotes, AccountId) VALUES(\"";
        sql2 += Id.c_str();
        sql2 += "\", \"";
        sql2 += Reputation.c_str();
        sql2 += "\", \"";
        sql2 += CreationDate.c_str();
        sql2 += "\", \"";
        sql2 += DisplayName.c_str();
        sql2 += "\", \"";
        sql2 += LastAccessDate.c_str();
        sql2 += "\", \"";
        sql2 += Location.c_str();
        sql2 += "\", \"";
        sql2 += AboutMe.c_str();
        sql2 += "\", \"";
        sql2 += Views.c_str();
        sql2 += "\", \"";
        sql2 += UpVotes.c_str();
        sql2 += "\", \"";
        sql2 += DownVotes.c_str();
        sql2 += "\", \"";
        sql2 += AccountId.c_str();
        sql2 += "\");";

        //cout << "SQL2: " << sql2 << endl;
        mysql_query(conn2, sql2.c_str());

        fprintf(stderr, "%s\n", mysql_error(conn2));
        //cin.get();
        mysql_close(conn2);
    }
}

void TagsMySQL(string site, string Id, string TagName, string Count, string ExcerptPostId, string WikiPostId)
{
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_RES* result;
    MYSQL_ROW row;
    string sql1;
    string sql2;
    string table2;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn2, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    //label = ReplaceSpaces(label);
    //label = ToLowercase(label);
    TagName = fixCharacterSyntax(TagName);

    if (conn)
    {
        site += "_Tags";

        sql1 = "CREATE TABLE IF NOT EXISTS `";
        sql1 += site.c_str();
        sql1 += "`(Id TEXT, TagName TEXT, Count TEXT, ExcerptPostId TEXT, WikiPostId TEXT);";
        //cout << "SQL1: " << sql1 << endl;
        mysql_query(conn, sql1.c_str());
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
    }

    if (conn2)
    {
        sql2 = "INSERT INTO `";
        sql2 += site.c_str();
        sql2 += "`(Id, TagName, Count, ExcerptPostId, WikiPostId) VALUES(\"";
        sql2 += Id.c_str();
        sql2 += "\", \"";
        sql2 += TagName.c_str();
        sql2 += "\", \"";
        sql2 += Count.c_str();
        sql2 += "\", \"";
        sql2 += ExcerptPostId.c_str();
        sql2 += "\", \"";
        sql2 += WikiPostId.c_str();
        sql2 += "\");";

        //cout << "SQL2: " << sql2 << endl;
        mysql_query(conn2, sql2.c_str());

        fprintf(stderr, "%s\n", mysql_error(conn2));
        //cin.get();
        mysql_close(conn2);
    }
}

void VotesMySQL(string site, string Id, string PostId, string VoteTypeId, string UserId, string CreationDate)
{
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_RES* result;
    MYSQL_ROW row;
    string sql1;
    string sql2;
    string table2;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn2, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    //label = ReplaceSpaces(label);
    //label = ToLowercase(label);
    /*label = fixCharacterSyntax(label);*/

    if (conn)
    {
        site += "_Votes";
        sql1 = "CREATE TABLE IF NOT EXISTS `";
        sql1 += site.c_str();
        sql1 += "`(Id TEXT, PostId TEXT, VoteTypeId TEXT, UserId TEXT, CreationDate TEXT);";
        //cout << "SQL1: " << sql1 << endl;
        mysql_query(conn, sql1.c_str());
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
    }

    if (conn2)
    {
        sql2 = "INSERT INTO `";
        sql2 += site.c_str();
        sql2 += "`(Id, PostId, VoteTypeId, UserId, CreationDate) VALUES(\"";
        sql2 += Id.c_str();
        sql2 += "\", \"";
        sql2 += PostId.c_str();
        sql2 += "\", \"";
        sql2 += VoteTypeId.c_str();
        sql2 += "\", \"";
        sql2 += UserId.c_str();
        sql2 += "\", \"";
        sql2 += CreationDate.c_str();
        sql2 += "\");";

        //cout << "SQL2: " << sql2 << endl;
        mysql_query(conn2, sql2.c_str());

        fprintf(stderr, "%s\n", mysql_error(conn2));
        //cin.get();
        mysql_close(conn2);
    }
}

void BadgesMySQL(string site, string Id, string UserId, string Name, string Date, string Class)
{
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_RES* result;
    MYSQL_ROW row;
    string sql1;
    string sql2;
    string table2;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn2, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    //label = ReplaceSpaces(label);
    //label = ToLowercase(label);
    Name = fixCharacterSyntax(Name);

    if (conn)
    {
        site += "_Badges";
        sql1 = "CREATE TABLE IF NOT EXISTS `";
        sql1 += site.c_str();
        sql1 += "`(Id TEXT, UserId TEXT, Name TEXT, Date TEXT, Class TEXT);";
        //cout << "SQL1: " << sql1 << endl;
        mysql_query(conn, sql1.c_str());
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
    }

    if (conn2)
    {
        sql2 = "INSERT INTO `";
        sql2 += site.c_str();
        sql2 += "`(Id, UserId, Name, Date, Class) VALUES(\"";
        sql2 += Id.c_str();
        sql2 += "\", \"";
        sql2 += UserId.c_str();
        sql2 += "\", \"";
        sql2 += Name.c_str();
        sql2 += "\", \"";
        sql2 += Date.c_str();
        sql2 += "\", \"";
        sql2 += Class.c_str();
        sql2 += "\");";

        //cout << "SQL2: " << sql2 << endl;
        mysql_query(conn2, sql2.c_str());

        fprintf(stderr, "%s\n", mysql_error(conn2));
        //cin.get();
        mysql_close(conn2);
    }
}

string getStem(string input, string table)
{
    string temp = "";
    int x;
    int slashes = 0;

    for (x = input.length() - 1; x >= 0; x--)
    {
        if (input[x] == '/')
        {
            break;
        }
    }

    for (int y = x + 1; y <= input.length() - 1; y++)
    {
        temp += input[y];
    }

    return temp;
}

string fixCharacterSyntax(string input)
{
    string temp = "";

    for (int x = 0; x <= input.length(); x++)
    {
        if (input[x] == '\'')
        {
            temp += "\'";
        }
        if (input[x] == '&' && input[x + 1] == 'l' && input[x + 2] == 't' && input[x + 3] == ';')
        {
            x += 4;
        }
        if (input[x] == '&' && input[x + 1] == 'g' && input[x + 2] == 't' && input[x + 3] == ';')
        {
            x += 4;
        }
        if (input[x] == '/' && input[x + 1] == 'p' && input[x + 2] == '&' && input[x + 3] == 'g' && input[x + 4] == 't' && input[x + 5] == ';')
        {
            x += 6;
        }
        if (input[x] == '&' && input[x + 1] == '#' && input[x + 2] == 'x' && input[x + 3] == 'A' && input[x + 4] == ';')
        {
            x += 5;
        }
        if (input[x] == '&' && input[x + 1] == 'q' && input[x + 2] == 'u' && input[x + 3] == 'o' && input[x + 4] == 't' && input[x + 5] == ';')
        {
            x += 6;
        }
        if (input[x] == 'a' && input[x + 1] == ' ' && input[x + 2] == 'h' && input[x + 3] == 'r' && input[x + 4] == 'e' && input[x + 5] == 'f' && input[x + 6] == '=')
        {
            x += 7;
        }
        if (input[x] == 'r' && input[x + 1] == 'e' && input[x + 2] == 'l' && input[x + 3] == '=' && input[x + 4] == '&' && input[x + 5] == 'q' && input[x + 6] == 'u' && input[x + 7] == 'o' && input[x + 8] == 't' && input[x + 9] == ';' && input[x + 10] == 'n' && input[x + 11] == 'o' && input[x + 12] == 'f' && input[x + 13] == 'o' && input[x + 14] == 'l' && input[x + 15] == 'l' && input[x + 16] == 'o' && input[x + 17] == 'w' && input[x + 18] == ' ' && input[x + 19] == 'n' && input[x + 20] == 'o' && input[x + 21] == 'r' && input[x + 22] == 'e' && input[x + 23] == 'f' && input[x + 24] == 'e' && input[x + 25] == 'r' && input[x + 26] == 'r' && input[x + 27] == 'e' && input[x + 28] == 'r')
        {
            x += 29;
        }
        if (input[x] == '/' && input[x + 1] == 'b' && input[x + 2] == 'l' && input[x + 3] == 'o' && input[x + 4] == 'c' && input[x + 5] == 'k' && input[x + 6] == 'q' && input[x + 7] == 'u' && input[x + 8] == 'o' && input[x + 9] == 't' && input[x + 10] == 'e' && input[x + 11] == '&' && input[x + 12] == 'g' && input[x + 13] == 't' && input[x + 14] == ';')
        {
            x += 15;
        }
        if (input[x] == '/' && input[x + 1] == 'e' && input[x + 2] == 'm' && input[x + 3] == '&' && input[x + 4] == 'g' && input[x + 5] == 't' && input[x + 6] == ';')
        {
            x += 7;
        }
        else
        {
            temp += input[x];
        }
    }

    //temp += "\'";

    return temp;
}

string ReplaceSpaces(string title)
{
    string output;

    for (int x = 0; x <= title.length(); x++)
    {
        if (title[x] == ' ')
        {
            output += '_';
        }
        else if (title[x] == '-')
        {
            // Check if the first three characters are a hyphen
            if (x == 0 || title[x + 1] == '-')
            {

            }
            else
            {
                if (title[x + 1] == ' ')
                {

                }
                else
                {
                    output += '_';
                }
            }
        }
        else
        {
            output += title[x];
        }
    }

    return output;
}

string ToLowercase(string sentence)
{
    string temp;

    for (int x = 0; x <= sentence.length(); x++)
    {
        temp += tolower(sentence[x]);
    }

    return temp;
}

string removeQuotes(string query)
{
    string temp;

    for (int x = 0; x <= query.length(); x++)
    {
        if (query[x] == '\'')
        {

        }
        else if (query[x] == '\"')
        {

        }
        else
        {
            temp += query[x];
        }
    }

    return temp;
}