#include <iostream>
#include <set>
#include <random>
#include <typeinfo>

class State{
public:
    virtual bool contains(int s) const{
        return false;
    }
};


class DiscreteState final: public State {
private:
    int const state;

public:
    //DiscreteState():state(0){}
    DiscreteState(int state): state(state) { }

    bool contains(int s) const override{
        return s == state;
    }
};
class SegmentState final: public State {
private:
    int const beg, end;

public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const override{
        return s >= beg && s <= end;
    }
};
class SetState final: public State  {
private:
    std::set<int> const states;

public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }

    bool contains(int s) const override{
        return states.count(s) > 0;
    }
};
class SegmentPassState final: public State  {
private:
    int const beg, end;
    std::set<int> const pass_states;

public:
    SegmentPassState(): beg(0), end(-1), pass_states() { }
    SegmentPassState(int beg, int end, std::set<int> const &src): beg(beg), end(end), pass_states(src) { }

    bool contains(int s) const override{
        return (pass_states.count(s) == 0) and (s >= beg && s <= end) ;
    }
};
class SegmentAddState final: public State  {
private:
    int const beg, end;
    std::set<int> const add_states;

public:
    SegmentAddState(): beg(0), end(-1), add_states() { }
    SegmentAddState(int beg, int end, std::set<int> const &src): beg(beg), end(end), add_states(src) { }

    bool contains(int s) const override{
        return (add_states.count(s) > 0) or (s >= beg && s <= end) ;
    }
};
class SegmentAddPassState final: public State  {
private:
    int const beg, end;
    std::set<int> const add_states;
    std::set<int> const pass_states;
public:
    SegmentAddPassState(): beg(0), end(-1), add_states(), pass_states() { }
    SegmentAddPassState(int beg, int end, std::set<int> const &src_pass, std::set<int> const &src_add ):
        beg(beg), end(end), add_states(src_add), pass_states(src_pass) { }

    bool contains(int s) const override{
        return (pass_states.count(s) == 0 ) and ((add_states.count(s) > 0) or (s >= beg && s <= end)) ;
    }
};
class UnionState final : public State {
private:
    State *state1;
    State *state2;
public:
    UnionState(State *state1, State *state2) :state1(state1), state2(state2) {}

    bool contains(int s) const override {
        return state1->contains(s) or state2->contains(s);
    }
};



class CrossState final: public State {
private:
State *state1;
State *state2;
public:
CrossState(State *state1, State *state2) :state1(state1), state2(state2) {}

bool contains(int s) const override{
return state1->contains(s) and state2->contains(s);
}
};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(State const &state) const{
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (state.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);

    }

};

int main(int argc, const char * argv[]) {
    /*DiscreteState d(1);
    SegmentState s(0,10);
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
    SegmentPassState sps(0, 20, {3, 7, 0, 1});
    SegmentAddState sas(0, 20, {-10, 50, 23, 18});
    SegmentAddPassState saps(0, 20, {12, 10, 9}, {50, 70, -60});
    UnionState us(&d, &sps);
    CrossState cs(&ss, &saps);
    ProbabilityTest pt(10,0,20,10);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;
    std::cout << pt(sps) << std::endl;
    std::cout << pt(sas) << std::endl;
    std::cout << pt(saps) << std::endl;
    std::cout << pt(us) << std::endl;
    std::cout << pt(cs) << std::endl;*/

    SegmentState s(0, 10);
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 70, 90, 99});
    ProbabilityTest pt(10, 0, 100, 10000);


    /*std::cout << "Probability from quantity of tests:" << std::endl;
    for (int i = 1; i <= 1000; i++) {
        ProbabilityTest pt(20, 0, 100, 1000 * i);
        std::cout << pt(s) << std::endl;
        std::cout << pt(ss) << std::endl;
    }*/

    std::cout << "Probability from bound:" << std::endl;
    for (int i = 1; i <= 1000; i++) {
        ProbabilityTest pt(50, 0, 1 * i, 1000);
        std::cout << pt(s) << std::endl;
        std::cout << pt(ss) << std::endl;
    }
    return 0;
}