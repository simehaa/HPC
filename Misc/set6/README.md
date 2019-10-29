# Exercise 1
There are *n* equal tasks and *p* equal workers, however *n* is not divisible by *p*, how to share the work in a fair way?
### Solution:
Each worker does at least *n/p* (integer division) amount of work. The remainder: *r = n%p < p*, can be split such that *r* out of *p* workers does one extra task each. The world is not a fair place.
# Exercise 2
There are 20 independent tasks which takes 1h, 2h, 3h, ... , 20h. The tasks can easily be split in 10 chunks of 21 hours: (1+20), (2+19), ... , (10+11). **Note**: if there are only 1 worker, the total time is 210 hours.
### Solution 1:
If there are two equal workers, then surely both workers can do 5 21-hour-chunks each. Total time = 105 hours. Speedup == 2.
### Solution 2:
If there are three equal workers:
* Worker 1: 20 + 15 + 14 + 9 + 8 + 3 + 1 = 70.
* Worker 2: 19 + 16 + 13 + 10 + 7 + 5 = 70.
* Worker 3: 18 + 17 + 12 + 11 + 6 + 4 + 2 = 70.

Total time = 70 hours. Speedup == 3.

# Exercise 3
4 equal workers on 15 tasks of 10 minutes each. However, first 1 task must be done, then 2 can be done, then 4, finally 8.
### Solution 1:
For 4 equal workers: Layers:
1. 10 min
2. 10 min
3. 10 min
4. 20 min

= 50 minutes.
### Solution 2:
3 equal workers.
Layers:
1. 10 min
2. 10 min
3. 20 min (two idle workers last 10 min: can begin layer 4)
4. (2 tasks done by the idle workers from layer 3, 6 remaining) 20 min.

= 60 minutes = 1h.

# Exercise 4
When splitting up a task into subtasks one goal is to have the least possible idle worker time.

# Exercise 5
### *8 X 1*: 1/12 = 0.833
### *4 X 2*: 0
### *3 X 3*: 0.0615
