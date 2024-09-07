class A : public Participant { // Stealcat
public:
    explicit A(int number) {}
    void StartNewGame() override {}
    Move MakeMove() override {
        return Move::STEAL;
    }
    void GetOpponentMove(Move) override {}
};
