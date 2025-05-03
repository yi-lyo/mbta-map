#!/usr/bin/env python3

import re
from typing import Union

# Station       Inbound     Outbound
# South Station 17           0
# Back Bay      16           1
# Ruggles       15           2
# Forest Hills* 14           3
# Hyde Park     13           4
# Readville     12           5
# Route 128     11           6
# Canton J      10           7
# Canton C*      9           8
# Stoughton*     8           9
# Sharon         7          10
# Mansfield      6          11
# Attleboro      5          12
# S Attleboro*   4          13
# Pawtucket      3          14
# Providence     2          15
# TF Green*      1          16
# Wickford J*    0          17

inbound_weekday_rawstr = '''10 Wickford Junction  - - - - - 6:02 - - 7:02 - - - 8:38 - - - - 11:57 - - - - - 2:25 - - - 4:35 - - - 6:46 - 7:42 - - -
9 TF Green Airport  - - - - - 6:16 - - 7:16 - - - 8:52 - - - - 12:11 - - - - - 2:39 - - - 4:49 - - - 7:00 - 7:56 - - -
8 Providence (Arr.)  - - - - - 6:31 - - 7:31 - - - 9:07 - - - - 12:26 - - - - - 2:55 - - - 5:04 - - - 7:15 - 8:11 - - -
8 Providence (Dep.)  4:12 - 5:10 - 6:00 6:32 - 7:10 7:32 - 8:08 - 9:08 - 10:15 - 11:12 12:27 - 1:15 - 2:10 - 2:56 - 3:56 - 5:05 - 6:12 - 7:16 - 8:12 - 10:15 11:25
8 Pawtucket/Central Falls  4:18 - 5:16 - 6:06 6:38 - 7:16 7:38 - 8:14 - 9:15 - 10:21 - 11:18 12:33 - 1:21 - 2:16 - 3:02 - 4:02 - 5:11 - 6:18 - 7:22 - 8:18 - 10:21 11:31
7 South Attleboro  4:23 - - - 6:11 - - 7:21 - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
7 Attleboro  4:34 - 5:29 - 6:22 6:51 - 7:32 7:51 - 8:27 - 9:28 - 10:34 - 11:31 12:46 - 1:34 - 2:30 - 3:15 - 4:18 - 5:24 - 6:31 - 7:35 - 8:31 - 10:34 11:44
6 Mansfield  4:44 - 5:39 - 6:32 7:01 - 7:42 8:01 - 8:37 - 9:41 - 10:44 - 11:43 12:56 - 1:44 - 2:40 - 3:25 - 4:28 - 5:34 - 6:41 - 7:45 - 8:41 - 10:44 11:57
4 Sharon  4:53 - 5:48 - 6:41 7:10 - 7:51 8:10 - 8:46 - 9:50 - 10:53 - 11:52 1:05 - 1:53 - 2:49 - 3:34 - 4:37 - 5:43 - 6:50 - 7:54 - 8:50 - 10:53 12:06
4 Stoughton  - 5:15 - 6:18 - - 7:15 - - 8:12 - 9:15 - 10:15 - 11:20 - - 1:22 - 2:15 - 3:05 - 4:05 - 5:00 - 6:00 - 7:18 - 8:05 - 9:58 - -
3 Canton Center  - 5:22 - 6:25 - - 7:22 - - 8:19 - 9:22 - 10:22 - 11:27 - - 1:29 - 2:22 - 3:12 - 4:12 - 5:07 - 6:07 - 7:25 - 8:12 - 10:05 - -
3 Canton Junction  4:58 5:25 5:53 6:28 6:46 - 7:25 7:56 - 8:22 8:51 9:25 9:55 10:25 10:58 11:30 11:57 1:10 1:32 1:58 2:25 - 3:15 3:39 4:15 4:42 5:10 5:48 6:10 6:55 7:28 - 8:15 8:55 10:08 10:58 12:11
2 Route 128  5:03 5:30 5:58 6:33 6:51 - 7:30 8:01 - 8:27 8:56 9:30 10:00 10:30 11:03 11:35 12:02 1:15 1:37 2:03 2:30 2:57 3:20 3:44 4:20 4:47 5:15 5:53 6:15 7:00 7:33 8:02 8:20 9:00 10:13 11:03 12:16
2 Readville  - - - 6:37 - - - - - - - - 10:04 - - - - - - - - - - - - 4:51 - - - - - 8:06 - - 10:17 - 12:20
1 Hyde Park  - 5:35 6:03 6:40 - - 7:35 - - 8:32 - 9:35 - 10:35 - 11:40 12:07 - 1:42 - 2:35 - 3:25 - 4:25 - 5:20 - 6:20 - 7:38 - 8:25 - 10:19 11:08 12:22
1A Ruggles  L 5:18 L 5:44 L 6:14 L 6:50 L 7:07 L 7:31 L 7:47 L 8:17 L 8:30 L 8:42 L 9:12 L 9:46 L 10:17 L 10:44 L 11:18 L 11:49 L 12:20 L 1:30 L 1:51 L 2:20 L 2:44 L 3:12 L 3:34 L 3:59 L 4:34 L 5:04 L 5:29 L 6:08 L 6:29 L 7:15 L 7:47 L 8:19 L 8:34 L 9:14 L 10:29 L 11:19 L 12:34
1A Back Bay  L 5:22 L 5:48 L 6:18 L 6:54 L 7:11 L 7:35 L 7:51 L 8:21 L 8:34 L 8:46 L 9:16 L 9:50 L 10:21 L 10:48 L 11:22 L 11:53 L 12:24 L 1:34 L 1:55 L 2:24 L 2:48 L 3:16 L 3:38 L 4:03 L 4:38 L 5:08 L 5:33 L 6:12 L 6:33 L 7:19 L 7:51 L 8:23 L 8:38 L 9:18 L 10:33 L 11:23 L 12:38
1A South Station  5:28 5:54 6:24 7:00 7:17 7:41 7:57 8:27 8:40 8:52 9:22 9:56 10:26 10:53 11:27 11:58 12:29 1:39 2:00 2:29 2:53 3:21 3:43 4:09 4:44 5:14 5:39 6:18 6:39 7:25 7:56 8:28 8:43 9:23 10:38 11:28 12:43'''


def parse_time(time_str : str, is_pm: bool) -> Union[int, None]:
    if time_str == "-":
        return None
    time_tup = time_str.split(":")
    assert len(time_tup) == 2
    minute_of_day = int(time_tup[0]) * 60 + int(time_tup[1])
    if is_pm:
        minute_of_day += 720
    return minute_of_day


def correct_time_switch(train_line : list[Union[int, None]]) -> None:
    max_incumbent = -1
    for i, time in enumerate(train_line):
        if time is None:
            continue
        if time > max_incumbent:
            max_incumbent = time
        else:
            diff = max_incumbent - time
            if (diff > 720) or (diff < 700): # Shouldn't be more than a 12 hour difference, nor should time between stations be more than 20 mins
                raise Exception(f'Unexplained time difference. max_incumbent: {max_incumbent}, time: {time}')
            train_line[i] += 720 # Correct for AM/PM switch
            max_incumbent = train_line[i]



def extract_time_table(rawstr : str, pm_col: int):
    lines = rawstr.split('\n')
    tokens = [s.split(' ') for s in lines]
    station_names_removed = [row[(row.index('\uf0e9') + 1):] for row in tokens]
    times = [[item for item in row if item != "L"] for row in station_names_removed]
    row_lengths = [len(row) for row in times]
    assert all(l == row_lengths[0] for l in row_lengths) # Ensure table is rectangular
    transposed = list(map(list, zip(*times))) # Each row represents a train, with columns representing stations
    parsed = [[parse_time(time, i >= pm_col) for time in train_line] for i, train_line in enumerate(transposed)]
    for train_line in parsed:
        correct_time_switch(train_line)
    return parsed


def flatten_for_c(table : list[list[Union[int, None]]]) -> list[int]:
    flattened_table : list[int] = []
    for train_line in table:
        for stop in train_line:
            flattened_table.append(0xFFFF if stop is None else stop)
    return flattened_table


def duplicate(l: list[int], index: int) -> None:
    l.insert(index, l[index])


def correct_station_asymmetry(l: list[int], i: int) -> None:
    if l[i] is None and l[i + 1] is not None:
        l[i] = l[i + 1]
    elif l[i + 1] is None and l[i] is not None:
        l[i + 1] = l[1]


inbound_weekday_table = extract_time_table(inbound_weekday_rawstr, 18)
for train_line in inbound_weekday_table:
    for i in range(0, 36, 2):
        if i == 4: # Providence
            continue
        if i == 28: # Forest Hills
            train_line.insert(i, None)
            train_line.insert(i, None)
            continue
        duplicate(train_line, i)
    correct_station_asymmetry(train_line, 4)
    assert len(train_line) == 36

weekday_inbound_c : list[int] = flatten_for_c(inbound_weekday_table)

print(weekday_inbound_c)
print(len(weekday_inbound_c))

outbound_weekday_rawstr='''1A South Station  4:20 5:25 6:30 7:00 7:30 8:00 8:25 8:57 9:25 10:02 10:25 11:18 12:00 12:20 1:05 1:20 2:05 2:20 2:55 3:20 3:52 4:00 4:20 4:52 5:00 5:37 5:52 6:22 7:05 7:18 8:00 8:35 9:00 9:35 10:45 11:05 11:55
1A Back Bay  4:25 5:30 6:35 7:05 7:35 8:05 8:30 9:02 9:30 10:07 10:30 11:23 12:05 12:25 1:10 1:25 2:10 2:25 3:00 3:25 3:57 4:05 4:25 4:57 5:05 5:42 5:57 6:27 7:10 7:23 8:05 8:40 9:05 9:40 10:50 - 12:00
1A Ruggles  4:28 5:33 6:38 7:08 7:38 8:08 8:33 9:05 9:33 10:10 10:33 11:26 12:08 12:28 1:13 1:28 2:13 2:28 3:03 3:28 4:01 4:08 4:28 5:01 5:08 5:46 6:00 6:30 7:13 7:26 8:08 8:43 9:08 9:43 10:53 - 12:03
1A Forest Hills  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 10:58 - 12:08
1 Hyde Park  - - - - - - - - 9:41 - - - 12:16 - 1:21 - 2:21 - - - - - - - - - - - 7:21 - 8:16 - 9:16 9:51 11:03 - 12:13
2 Readville  - - - - - - - - - - - - 12:18 - - - - - - - - - - - - - - - - 7:37 - - 9:18 9:53 - - 12:15
2 Route 128  4:39 5:44 6:49 7:18 7:49 8:18 8:44 9:15 9:47 10:21 10:44 11:37 12:22 12:39 1:26 1:39 2:26 2:39 3:14 3:39 - 4:19 4:39 - 5:19 5:57 6:11 6:41 7:26 7:41 8:21 8:54 9:22 9:57 11:08 11:37 12:19
3 Canton Junction  4:45 5:50 6:55 7:24 7:55 8:24 8:50 9:21 9:53 10:27 10:50 11:43 12:28 12:45 1:32 1:45 2:32 2:45 3:20 3:45 - 4:25 4:45 - 5:25 6:03 6:17 6:47 7:32 7:47 8:27 9:00 9:28 10:03 11:14 11:43 12:25
3 Canton Center  - 5:53 - 7:28 - 8:27 - 9:28 - 10:30 - - 12:31 - 1:35 - 2:35 - 3:24 - - 4:28 - - 5:29 - 6:21 - 7:35 - 8:30 - 9:31 - - 11:46 -
4 Stoughton  - 6:01 - 7:37 - 8:37 - 9:37 - 10:38 - - 12:39 - 1:43 - 2:43 - 3:34 - - 4:39 - - 5:40 - 6:31 - 7:44 - 8:38 - 9:39 - - 11:55 -
3 Sharon  4:51 - 7:01 - 8:01 - 8:56 - 9:59 - 10:56 11:49 - 12:51 - 1:51 - 2:51 - 3:51 4:17 - 4:51 5:17 - 6:09 - 6:53 - 7:53 - 9:06 - 10:09 11:20 - 12:31
5 Mansfield  4:59 - 7:09 - 8:09 - 9:04 - 10:07 - 11:04 11:57 - 12:59 - 1:59 - 2:59 - 3:59 4:25 - 4:59 5:25 - 6:18 - 7:01 - 8:01 - 9:14 - 10:17 11:28 - 12:39
7 Attleboro  5:07 - 7:17 - 8:17 - 9:12 - 10:15 - 11:12 12:05 - 1:07 - 2:07 - 3:07 - 4:07 4:34 - 5:07 5:34 - 6:28 - 7:09 - 8:09 - 9:22 - 10:25 11:36 - 12:47
7 South Attleboro  - - - - - - - - - - - 12:15 - - - - - 3:14 - - 4:44 - - - - 6:39 - - - - - - - - - - -
8 Pawtucket/Central Falls  5:16 - 7:26 - 8:26 - 9:21 - 10:24 - 11:21 12:19 - 1:16 - 2:16 - 3:18 - 4:16 4:48 - 5:16 5:43 - 6:43 - 7:21 - 8:21 - 9:31 - 10:34 11:45 - 12:56
8 Providence (Arr.)  5:30 - 7:43 - 8:40 - 9:35 - 10:36 - 11:35 12:33 - 1:28 - 2:28 - 3:29 - 4:30 5:00 - 5:31 5:52 - 6:54 - 7:36 - 8:33 - 9:45 - 10:51 12:01 - 1:12
8 Providence (Dep.)  5:45 - 7:45 - - - - - 10:37 - - - - 1:30 - - - 3:30 - - 5:01 - - 5:53 - 6:55 - - - - - - - - - - -
9 TF Green Airport  6:00 - 8:00 - - - - - 10:52 - - - - 1:45 - - - 3:44 - - 5:15 - - 6:07 - 7:10 - - - - - - - - - - -
10 Wickford Junction  6:18 - 8:15 - - - - - 11:13 - - - - 2:05 - - - 4:04 - - 5:35 - - 6:33 - 7:29 - - - - - - - - - - -'''

outbound_weekday_table = extract_time_table(outbound_weekday_rawstr, 12)
for train_line in outbound_weekday_table:
    for i in range(0, 36, 2):
        if i == 30: # Providence
            continue
        duplicate(train_line, i)
    correct_station_asymmetry(train_line, 30)
    assert len(train_line) == 36

outbound_weekday_c = flatten_for_c(outbound_weekday_table)

print(outbound_weekday_c)
print(len(outbound_weekday_c))

inbound_weekend_rawstr = '''8 Providence  5:15 8:15 9:45 11:45 1:45 3:45 5:55 7:55 9:25 11:25
8 Pawtucket/Central Falls  5:21 8:21 9:51 11:51 1:51 3:51 6:01 8:01 9:31 11:31
7 Attleboro  5:33 8:33 10:03 12:03 2:03 4:03 6:13 8:13 9:43 11:43
5 Mansfield  5:43 8:43 10:13 12:13 2:13 4:13 6:23 8:23 9:53 11:53
3 Sharon  5:52 8:52 10:22 12:22 2:22 4:22 6:32 8:32 10:02 12:02
3 Canton Junction  5:57 8:57 10:27 12:27 2:27 4:27 6:37 8:37 10:07 12:07
2 Route 128  6:03 9:03 10:33 12:33 2:33 4:33 6:43 8:43 10:13 12:13
2 Readville  6:07 9:07 10:37 12:37 2:37 4:37 6:47 8:47 10:17 12:17
1 Hyde Park  6:10 9:10 10:40 12:40 2:40 4:40 6:50 8:50 10:20 12:20
1A Ruggles  L 6:21 L 9:21 L 10:51 L 12:51 L 2:51 L 4:51 L 7:01 L 9:01 L 10:31 L 12:31
1A Back Bay  L 6:25 L 9:25 L 10:55 L 12:55 L 2:55 L 4:55 L 7:05 L 9:05 L 10:35 L 12:35
1A South Station  6:30 9:30 11:00 1:00 3:00 5:00 7:10 9:10 10:40 12:40'''

inbound_weekend_table = extract_time_table(inbound_weekend_rawstr, 4)
for train_line in inbound_weekend_table:
    assert len(train_line) == 12
    # Add missing stations
    train_line.insert(0, None) # Wickford Junction
    train_line.insert(1, None) # TF Green Airport
    train_line.insert(4, None) # South Attleboro
    train_line.insert(8, None) # Stoughton
    train_line.insert(9, None) # Canton Center
    train_line.insert(14, None) # Forest Hills
    for i in range(0, 36, 2):
        duplicate(train_line, i)
    assert len(train_line) == 36

inbound_weekend_c = flatten_for_c(inbound_weekend_table)

print(inbound_weekend_c)
print(len(inbound_weekend_c))

outbound_weekend_rawstr = '''1A South Station  6:45 7:55 10:15 12:15 2:15 3:45 5:45 7:55 9:55 11:55
1A Back Bay  6:50 8:00 10:20 12:20 2:20 3:50 5:50 8:00 10:00 12:00
1A Ruggles  6:53 8:03 10:23 12:23 2:23 3:53 5:53 8:03 10:03 12:03
1 Hyde Park  7:01 8:11 10:31 12:31 2:31 4:01 6:01 8:11 10:11 12:11
2 Readville  7:04 8:14 10:34 12:34 2:34 4:04 6:04 8:14 10:14 12:14
2 Route 128  7:08 8:18 10:38 12:38 2:38 4:08 6:08 8:18 10:18 12:18
3 Canton Junction  7:14 8:24 10:44 12:44 2:44 4:14 6:14 8:24 10:24 12:24
3 Sharon  7:19 8:29 10:49 12:49 2:49 4:19 6:19 8:29 10:29 12:29
5 Mansfield  7:27 8:37 10:57 12:57 2:57 4:27 6:27 8:37 10:37 12:37
7 Attleboro  7:37 8:47 11:07 1:07 3:07 4:37 6:37 8:47 10:47 12:47
8 Pawtucket/Central Falls  7:46 8:59 11:16 1:16 3:16 4:46 6:46 8:56 10:56 12:56
8 Providence  7:58 9:11 11:28 1:28 3:28 5:01 6:58 9:08 11:08 1:08'''

outbound_weekend_table = extract_time_table(outbound_weekend_rawstr, 3)
for train_line in outbound_weekend_table:
    assert len(train_line) == 12
    for i in [3, 8, 9, 13, 16, 17]:
        train_line.insert(i, None)
    for i in range(0, 36, 2):
        duplicate(train_line, i)
    assert len(train_line) == 36

outbound_weekend_c = flatten_for_c(outbound_weekend_table)

print(outbound_weekend_c)
print(len(outbound_weekend_c))
