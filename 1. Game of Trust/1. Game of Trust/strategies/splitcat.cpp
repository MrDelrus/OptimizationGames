class A : public Participant { // Splitcat
public:
    explicit A(int number) {}
    void StartNewGame() override {}
    Move MakeMove() override {
        return Move::SPLIT;
    }
    void GetOpponentMove(Move) override {}
};
