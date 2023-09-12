#pragma once

/*
    Copyright(c) 2022 Tyler Crockett | Macdaddy4sure.com

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

#include <iostream>
#include <string>
#include <mysql.h>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace filesystem;

/*
* Stackexchange / Stackoverflow Data
* 1. Posts
*   a. Id
*   b. PostTypeId
*   c. AcceptedAnswerId
*   d. CreationDate
*   e. Score
*   f. ViewCount
*   g. Body
*   h. OwnerUserId
*   i. LastEditorUserId
*   j. LastEditDate
*   k. LastActivityDate
*   l. Title
*   m. Tags
*   n. AnserCount
*   o. CommentCount
*   p. FavoriteCount
*   q. CommunityOwnedDate
*   r. ContentLicense
* 2. Comments
*   a. Id
*   b. PostId
*   c. Score
*   d. Text
*   e. CreationDate
*   f. UserId
*   g. ContentLicense
* 3. PostLinks
*   a. Id
*   b. CreationDate
*   c. PostId
*   d. RelatedPostId
*   e. LinkTypeId
* 4. PostHistory
*   a. Id
*   b. PostHistoryTypeId
*   c. PostId
*   d. CreationDate
*   e. UserId
*   f. Text
*   g. ContentLicense
* 5. Users
*   a. Id
*   b. Reputation
*   c. CreationDate
*   d. DisplayName
*   e. LastAccessDate
*   f. WebsiteURL
*   g. Location
*   h. AboutMe
*   i. Views
*   j. UpVotes
*   k. DownVotes
*   l. AccountId
* 6. Tags
*   a. Id
*   b. TagName
*   c. Count
*   d. ExerptPostId
*   e. WikiPostId
* 7. Votes
*   a. Id
*   b. PostId
*   c. VoteTypeId
*   d. CreationDate
* 8. Badges
*   a. Id
*   b. UserId
*   c. Name
*   d. Date
*   e. Class
*   f. TagBased
*/

static void Settings();
static void Parser();
static void PostsParser(string folder_location);
static void CommentsParser(string folder_location);
static void PostLinksParser(string folder_location);
static void PostsHistoryParser(string folder_location);
static void UsersParser(string folder_location);
static void TagsParser(string folder_location);
static void VotesParser(string folder_location);
static void BadgesParser(string folder_location);
static void PostsMySQL(string site, string Id, string PostTypeId, string AcceptedAnswerId, string CreationDate, string Score, string ViewCount, string Body, string OwnerUserId, string LastEditorUserId, string LastEditDate, string LastActivityDate, string Title, string Tags, string AnswerCount, string CommentCount, string FavoriteCount, string ContentLicense);
static void CommentsMySQL(string site, string Id, string PostId, string Score, string Text, string CreationDate, string UserId, string ContentLicense);
static void PostsLinksMySQL(string site, string Id, string CreationDate, string PostId, string RelatedPostId, string LinkTypeId);
static void PostsHistoryMySQL(string site, string Id, string PostHistoryTypeId, string PostId, string reationDate, string UserId, string Text, string ContentLicense);
static void UsersMySQL(string site, string Id, string Reputation, string CreationDate, string DisplayName, string LastAccessDate, string Location, string AboutMe, string Views, string UpVotes, string DownVotes, string AccountId);
static void TagsMySQL(string site, string Id, string TagName, string Count, string ExcerptPostId, string WikiPostId);
static void VotesMySQL(string site, string Id, string PostId, string VoteTypeId, string UserId, string CreationDate);
static void BadgesMySQL(string site, string Id, string UserId, string Name, string Date, string Class);

static string fixCharacterSyntax(string input);
static string ReplaceSpaces(string title);
static string ToLowercase(string sentence);
static string removeQuotes(string query);
static string getStem(string input, string table);
//static string removeCharacters(string input);

static string mysql_hostname = "moon.crockett.ai";
static string mysql_database = "stackexchange";
static string mysql_username = "tyler";
static string mysql_password = "Anaheim92801%";
static string stackoverflow_location = "X:/_Downloads/stackexchange/";