### Rules

The rules are simple.

There are two different strategies that we are trying to compare.

We create a tournament for 20 cats, 10 of them will play strategy of the first player, and others will play another strategy. Each cat plays exactly once with any of the others. Then, we sum up the scores for all the first players' cats and compare it with the same value for the second player. The higher score, the better!

One game between two cats consists of next steps:


1. Each cat has time to prepare and set up something.

2. The simulation randomly picks the number of rounds (from 3 to 7). Cats do not know this value. In every round, we repeat the next two steps:

3. We ask cats for their moves.

4. We update the scores, and pass the result of the round to the cats. 

There are only two options for one move:

- **SPLIT** - you lose 1 point, but your opponent gets 3 points.

- **STEAL** - you skip this round.

It may seem, that second option is always better, but it is not absolutely true. Give it a try, using the code for testing!