class A : public Participant { // Copycat
public:
    explicit A(int number) {}
    void StartNewGame() override {
        last.reset();
    }
    Move MakeMove() override {
        if (last.has_value()) {
            return last.value();
        }
        return Move::SPLIT;
    }
    void GetOpponentMove(Move move) override {
        last.emplace(move);
    }
private:
    optional<Move> last;
};
