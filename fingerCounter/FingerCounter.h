//
// Created by root on 8/17/21.
//

#ifndef FINGERCOUNTER_FINGERCOUNTER_H
#define FINGERCOUNTER_FINGERCOUNTER_H

#include <Arduino.h>
#include <EasyButton.h>

// #define BUTTON_PIN_RED 26
// #define BUTTON_PIN_BLUE 27
// #define BUTTON_PIN_CONFIG 28

enum class State
{
    SLEEP,
    IDLE,
    RUNNING
};


struct Points
{
    uint8_t bluePoints;
    uint8_t redPoints;
};

struct MatchData
{
    Points currentGamePoints;
    Points previousGamesPoints[16];
    bool isBlueFirstServ;
    bool isBlueServ;
    uint8_t servingTimes;
};

struct GameType
{
    char name_[16];
    uint8_t gamePoint_;
    uint8_t pointsDifference_;
    uint8_t criticalPoints_;
    uint8_t beforeCPSwitchPoints_;
    uint8_t afterCPSwitchPoints_;
};



class Match
{
public:
    Match();
    void clearMatchData();
    const char * getCurrentGameType();
    const Points & getCurrentPoints();
    const Points & getPreviousPoints();
    Points getGamePoints();
    bool getServ();
    // void blueButtonShortClick();
    // EasyButton::callback_t redButtonShortClick();
    // void blueButtonLongClick();
    // void redButtonLongClick();
    void blueRedButtonShortClick(bool isBlue);
    void blueRedButtonLongClick(bool isBlue);
    void configButtonShortClick();
    void configButtonLongClick();
    void setup();

    void showCurrentMatchData(const char* mark);

private:
    bool isSomeOneWin();
    void saveCurrentToPrevious();

    uint8_t getMaxServTimes();

    uint8_t currentGameTypeCount_;
    GameType* currentGameType_;
    MatchData matchData_;
    State currentState_;
};




class FingerCounter {
public:
    FingerCounter() = default;
private:
    State state_{State::SLEEP};

};


#endif //FINGERCOUNTER_FINGERCOUNTER_H
