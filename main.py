#coding=utf-8
import urllib
import re
import json
import time

# 记录签到情况的set
check = set()

# 日期
class Date:
    year = 0
    month = 0
    day = 0
    hour = 0
    minute = 0
    second = 0
    def __init__(self, year, month, day, hour, minute, second, cflag):
        # 处理本地与服务器所在地的时差问题 +8h
        if cflag == 1:
            common = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
            leap = [0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
            hour += 8
            if hour > 24:
                hour -= 24
                day += 1
                if year % 400 == 0 or (year % 4 == 0 and year % 100 != 0):
                    if day > leap[month]:
                        day -= leap[month]
                        month += 1
                else:
                    if day > common[month]:
                        day -= common[month]
                        month += 1
                if month > 12:
                    year += 1
                    month -= 12
        self.year = year
        self.month = month
        self.day = day
        self.hour = hour
        self.minute = minute
        self.second = second


# 存储用户信息
class User:
    name = ''
    date = Date(0, 0, 0, 0, 0, 0, 0)
    def __init__(self, name, date):
        self.name = name
        self.date = date
    
# GitHub Api URL
gitHubCommitsApi = 'https://api.github.com/repos/aplusb/Let-the-bass-kick/commits'

# 获取json
def getJson(url):
    page = urllib.urlopen(url)
    html = page.read()
    return html

# 保存json, commits.json
def saveJSON(html, fileNeme):
    fileWrite = open(fileNeme, 'w')
    fileWrite.write(html)
    fileWrite.close()

# 处理json
def processJSON(commits):
    users = []
    pr = json.loads(commits)
    for each in pr:
        name = each["commit"]["author"]["name"]
        date = each["commit"]["author"]["date"]
        yy = int(date[:4])
        mm = int(date[5:7])
        dd = int(date[8:10])
        hh = int(date[11:13])
        mi = int(date[14:16])
        ss = int(date[17:19])
        users.append(User(name, Date(yy, mm, dd, hh, mi, ss, 1)))
    return users

# 获取当天信息
def getToday():
    ISOTIMEFORMAT = '%Y-%m-%dT%XZ'
    curDate = time.strftime(ISOTIMEFORMAT, time.localtime())
    yy = int(curDate[:4])
    mm = int(curDate[5:7])
    dd = int(curDate[8:10])
    hh = int(curDate[11:13])
    mi = int(curDate[14:16])
    ss = int(curDate[17:19])
    return Date(yy, mm, dd, hh, mi, ss, 0)

# 统计当天的commit情况
def checkTimes(users):
    today = getToday()
    for each in users:
        if  today.year == each.date.year and today.month == each.date.month and today.day == each.date.day:
            check.add(each.name)
    
# 展示当天签到情况
def show(users, check):
    for each in users:
        print '%-20s %s-%s-%s %s:%s:%s' % (each.name, str(each.date.year).zfill(4),
                                           str(each.date.month).zfill(2), str(each.date.day).zfill(2),
                                           str(each.date.hour).zfill(2), str(each.date.minute).zfill(2),
                                           str(each.date.second).zfill(2))
    print '----------------------Today checked----------------------'
    for each in check:
        print '%s' % each

# 读取之前的签到情况
def readStatus():
    fileRead = open('status.txt', 'r')
    ISOTIMEFORMAT = '%Y-%m-%dT%XZ'
    today = time.strftime(ISOTIMEFORMAT, time.localtime())
    curDate = fileRead.readline()
    done = 0
    # 判断是不是today保存过的签到情况，如果是则读取信息
    if int(curDate[:4]) == int(today[:4]) and int(curDate[5:7]) == int(today[5:7]) and int(curDate[8:10]) == int(today[8:10]):
        while not done:
            entry = fileRead.readline()
            # 去空行
            entry = entry.strip('\n')
            if entry != '':
                check.add(entry)
            else:
                done = 1
    fileRead.close()    
    
# 保存统计结果
def saveStatus():
    fileWrite = open('status.txt', 'w')
    # 打时间戳
    ISOTIMEFORMAT = '%Y-%m-%dT%XZ'
    today = time.strftime(ISOTIMEFORMAT, time.localtime())
    fileWrite.write(today)
    fileWrite.write('\n')
    # 保存信息
    for each in check:
        fileWrite.write(each)
        fileWrite.write('\n')
    fileWrite.close()


def __main__():
    commits = getJson(gitHubCommitsApi)
    fileName = 'commits.json'
    readStatus()
    saveJSON(commits, fileName)
    users = processJSON(commits)
    checkTimes(users)
    saveStatus()
    show(users, check)


__main__()
