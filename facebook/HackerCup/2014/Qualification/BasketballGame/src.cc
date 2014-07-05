#include <iostream>
#include <set>
#include <functional>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <list>

#include "testcase.h"

#define UNUSED(arg) (void)(arg)

//#define DEBUG

using draft_number_t = unsigned int;
class Player
{
  friend class BasketballGame;
  public:
    static const draft_number_t nonumber = 0;
    Player(std::string &name, size_t shot_percentage, size_t height)
      : mName(name), mShotPercentage(shot_percentage), mHeight(height)
      , mDraftNo(nonumber), mPlayingTime(0) {}

    bool operator > (const Player &rhs) const {
      return this->mShotPercentage > rhs.mShotPercentage?true:
             (this->mShotPercentage == rhs.mShotPercentage && this->mHeight > rhs.mHeight)?true:false;
    }
    bool operator < (const Player &rhs) const {
      return this->mShotPercentage < rhs.mShotPercentage?true:
             (this->mShotPercentage == rhs.mShotPercentage && this->mHeight < rhs.mHeight?true:false);
    }
    bool operator == (const Player &rhs) const {
      return this->mName == rhs.mName
          && this->mShotPercentage == rhs.mShotPercentage
          && this->mHeight == rhs.mHeight
          && this->mDraftNo == rhs.mDraftNo
          && this->mPlayingTime == rhs.mPlayingTime;
    }

    operator std::string() const {
      std::ostringstream os;
        os << "(name : ";
        os.width(8);
        os << mName
#ifdef DEBUG
           << ", shot : "        << mShotPercentage
           << ", height : "      << mHeight
#endif
           << ", No : "          << mDraftNo
           << ", mPlayigTime : " << mPlayingTime
           << ")";
      return os.str();
    }

    draft_number_t number() const { return mDraftNo; }
    void number(const draft_number_t n) { mDraftNo=n; }

    std::string name() const { return mName; }

    void incPlayingTime(unsigned int offset=1) { mPlayingTime+=offset; }
    unsigned int playingTime() const { return mPlayingTime; }
	private:
		std::string    mName;
		size_t		     mShotPercentage;
		size_t		     mHeight;
    draft_number_t mDraftNo;
    unsigned int   mPlayingTime;
};
std::ostream &operator<<(std::ostream &os, const Player &p)
{
  return os << (std::string)p;
}

bool operator < (const std::reference_wrapper<Player> &p1, const std::reference_wrapper<Player> &p2) 
{
  return p1.get() < p2.get();
}

bool operator == (const std::reference_wrapper<Player> &p1, const std::reference_wrapper<Player> &p2) 
{
  return p1.get() == p2.get();
}

class Bench
{
  using Players = std::list<std::reference_wrapper<Player>>;
  public:
    void addPlayer(Player &p) { mPlayers.push_back(std::ref(p)); }
    void composeStarting(const size_t nPlayers) {
      for(size_t i=0;i<nPlayers;++i) enterPlayer(lowestPlayer());
    }
    void exchangePlayers() {
      for(auto &p:mPlaying) p.get().incPlayingTime();

      if(mPlayers.empty()) return;

      Player &lPlayer(longestPlayingPlayer());
      Player &sPlayer(shortestPlayingPlayer());
      substPlayer(sPlayer, lPlayer);
    }
    void dump(const bool aStartingPlayer = true, const bool aSubstPlayer = true) {
      if(aStartingPlayer) {
        Player &lPlayer(longestPlayingPlayer());
        for(auto &p:mPlaying) std::clog << "  " << p << (lPlayer==p.get()?"*":"") << std::endl;
      }
      if(aSubstPlayer) {
        Player &sPlayer(shortestPlayingPlayer());
        for(auto &p:mPlayers) std::clog << "    " << p << (sPlayer==p.get()?"*":"") << std::endl;
      }
    }
    const Players &activePlayers() const { return mPlaying; }
  private:
    Player& shortestPlayingPlayer() {
      return std::min_element(mPlayers.begin(), mPlayers.end(),
          [](const Player &p1, const Player &p2){
            return  p1.playingTime() <  p2.playingTime()?true:
                   (p1.playingTime() == p2.playingTime() && p1 > p2);
          }
        )->get();
    }
    Player& longestPlayingPlayer() {
      return std::max_element(mPlaying.begin(), mPlaying.end(),
          [](const Player &p1, const Player &p2){
            return p1.playingTime() < p2.playingTime()?true:
                   (p1.playingTime() == p2.playingTime() && p1 > p2);
          }
        )->get();
    }
    Player& lowestPlayer() {
      return std::max_element(mPlayers.begin(), mPlayers.end())->get();
    }
    void substPlayer(Player &in, Player &out) {
#ifdef DEBUG
        std::clog << "  Out : " << out.name() << ", In : " << in.name() << std::endl;
#endif
        mPlaying.push_back(in);
        mPlayers.push_back(out);

        mPlaying.remove(out);
        mPlayers.remove(in);
    }
    void enterPlayer(Player &p) {
        mPlayers.remove(p);
        mPlaying.push_back(p);
    }
    void leavePlayer(Player &p) {
        mPlaying.remove(p);
        mPlayers.push_back(p);
    }
  private:
    Players mPlaying;
    Players mPlayers;
};

class BasketballGame : public TestCase
{
  using base = TestCase;
  public:
    bool parseInput(InputFetcher& input) override {
      size_t nPlayer(input);
      input >> mTimeElapsed >> mPlayersPerTeam;
      assert(2 * mPlayersPerTeam <= nPlayer);
      assert(nPlayer <= 30);

      while(nPlayer--) {
        std::string name;
        input.nextline() >> name;
        size_t shot_percentage(input);
        size_t height(input);
        mPlayers.push_back(Player(name, shot_percentage, height));
      }
      input.nextline();

      return true;
    }
    void dump(std::ostream& os) const override {
      printBoundary(os, '=');
      os << "Number of Players : " << mPlayers.size()
         << ", mTimeElapsed : " << mTimeElapsed
         << ", mPlayersPerTeam : " << mPlayersPerTeam << std::endl;
      os << "Players)" << std::endl;
      for(const auto &p:mPlayers)
        os << "  " << p << std::endl;
    }
    bool run(unsigned int no) override {
      assignDraftNumber();

      makeTeams();

#ifdef DEBUG
      bool debug=no==1;
      if(debug) {
        printBoundary(std::clog, '=');
        std::clog << "Play #" << no << std::endl;
      }
#endif
      for(size_t elapsedTime = 0;elapsedTime<mTimeElapsed;++elapsedTime) {
#ifdef DEBUG
        if(debug) {
          printBoundary(std::clog, '-');
          int size=0;
          //auto &bench(mBench[0]);
          for(auto &bench:mBench)
          {
            std::clog << "Team #" << ++size << std::endl;
            bench.dump();
          }
          std::clog << elapsedTime << " elapsed" << std::endl;
          std::clog << "Exchanging..." << std::endl;
        }
#endif
        for(auto &bench:mBench) bench.exchangePlayers();
      }

#ifdef DEBUG
      if(debug) {
        printBoundary(std::clog, '-');
        std::clog << "Game Over!" << std::endl;
        int size=0;
        //auto &bench(mBench[0]);
        for(auto &bench:mBench)
        {
          std::clog << "Team #" << ++size << std::endl;
          bench.dump(true, false);
        }
      }
#endif
      std::cout << "Case #" << no << ":";
      std::list<Player> players;
      for(auto &bench:mBench) {
        for(auto p:bench.activePlayers()) {
          players.push_back(p);
        }
      }
      players.sort([](const Player &p1, const Player &p2) {
          return p1.name() < p2.name();
      });

      for(auto p:players)
        std::cout << " " << p.name();

      std::cout << std::endl;


      return false;
    }

  private:
    void makeTeams()
    {
      for(auto &p:mPlayers) mBench[p.number()%2==0].addPlayer(p);
      for(auto &bench:mBench) bench.composeStarting(mPlayersPerTeam);
    }

    void assignDraftNumber() {
      mPlayers.sort([](const Player &p1, const Player &p2) { return p1 > p2; });
      draft_number_t number=Player::nonumber;
      for(auto &p:mPlayers) p.number(++number);
    }
  private:
    std::list<Player>   mPlayers;
    unsigned int        mTimeElapsed;
    size_t              mPlayersPerTeam;

    std::array<Bench,2> mBench;
};

int main(int argc, char **argv)
{
	UNUSED(argc);UNUSED(argv);

  TestCaseContainer<BasketballGame> games;
  games.parseInput(std::cin);
  assert(1<=games.size() && games.size()<50);

  size_t i = 0;
  for(auto &g:games) {
#ifdef DEBUG
    g.dump(std::clog);
#endif
    g.run(++i);
  }

	return 0;
}
