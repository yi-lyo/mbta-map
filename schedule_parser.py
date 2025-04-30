#!/usr/bin/env python3

import re
from typing import Union

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
            if (diff > 720) or (diff <= 700): # Shouldn't be more than a 12 hour difference, nor should time between stations be more than 20 mins
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


inbound_weekday_table = extract_time_table(inbound_weekday_rawstr, 18)
for train_line in inbound_weekday_table:
    # Correct for there being two Providences:
    prov_arr = train_line.pop(2)
    prov_dep = train_line.pop(2)
    time_to_use = None
    if prov_arr is not None:
        time_to_use = prov_arr
    elif prov_dep is not None:
        time_to_use = prov_dep
    train_line.insert(2, time_to_use)
    # Insert Forest Hills
    train_line.insert(14, None)
    assert len(train_line) == 18

print(inbound_weekday_table)
print(len(inbound_weekday_table))
print([len(row) for row in inbound_weekday_table])

weekday_inbound_c : list[int] = []
for train_line in inbound_weekday_table:
    for stop in train_line:
        weekday_inbound_c.append(-1 if stop is None else stop)

print(weekday_inbound_c)
print(len(weekday_inbound_c))
