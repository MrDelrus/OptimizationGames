### General information

These sources can help you to test your own strategy. When you are ready to implement your idea, you need to do the following steps:

1. Write your own class, that inherits from class Participant.

2. Implement the methods. You are supposed not to use the global-scope or static methods/fields. Otherwise, the game won't be so interesting.

3. Run the test in `simulation/test.cpp`. If they are passed, your strategy is better than all baselines! 

4. You can try different strategies, and compare it using the code in `versus.cpp`.

##### `/simulation/test.cpp`

Paste your own class instead of class `A` (lines 19-27), then run the code.

##### `/simulation/versus.cpp`

Paste your own classes instead of classes `FirstCat` (lines 19-27) and `SecondCat` (lines 29-37), then run the code.

##### `/strategies/`

There you can find all the baseline strategies. Hope it will help you to create your cat!

### Recommendations

Use the G++17 compiler, as it did the author.

### References

The idea and basic strategies were taken from https://ncase.me/trust/