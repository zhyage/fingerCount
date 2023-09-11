//
// Created by root on 8/17/21.
//

#include "FingerCounter.h"


struct GameType gameList[] =
{
    {"PingPang", 11, 2, 10, 2, 1},
    {"YuMaoQiu", 21, 2, 20, 2, 1}
};

Match::Match()
    : currentGameTypeCount_(0)
    , currentGameType_(&gameList[currentGameTypeCount_])
    , currentState_(State::IDLE)
{
    clearMatchData();
}

void Match::clearMatchData()
{
    matchData_.currentGamePoints.bluePoints = 0;
    matchData_.currentGamePoints.redPoints = 0;
    for (int i = 0; i < 16; i++)
    {
        matchData_.previousGamesPoints[i].bluePoints = 0;
        matchData_.previousGamesPoints[i].redPoints = 0;
        matchData_.isBlueFirstServ = false;
        matchData_.isBlueServ = false;
        matchData_.servingTimes = 0;
    }
}

const char * Match::getCurrentGameType()
{
    return currentGameType_->name_;
}

const Points & Match::getCurrentPoints()
{
    return matchData_.currentGamePoints;
}

const Points & Match::getPreviousPoints()
{
    static uint8_t count = 0;
    Points& res = matchData_.previousGamesPoints[count];
    if (res.redPoints == 0 && res.bluePoints == 0) // invalid points
    {
        res = matchData_.currentGamePoints;
        count = 0;
        return res;
    }
    count = count + 1;
    if (count >= 16)
    {
        count = 0;
    }
    return res;
}

Points Match::getGamePoints()
{
    Points gamePoints{0, 0};
    for (int i = 0; i < 16; i++)
    {
        Points tmp = matchData_.previousGamesPoints[i];
        if (tmp.redPoints == 0 && tmp.bluePoints == 0) // invalid points
        {
            break;
        }
        if (tmp.bluePoints > tmp.redPoints)
        {
            gamePoints.bluePoints += 1;
        }
        else
        {
            gamePoints.redPoints += 1;
        }
    }
    return gamePoints;
}

bool Match::isSomeOneWin()
{
    if (matchData_.currentGamePoints.bluePoints == matchData_.currentGamePoints.redPoints)
    {
        return false;
    }
    uint8_t higher =
        matchData_.currentGamePoints.bluePoints > matchData_.currentGamePoints.redPoints ?
            matchData_.currentGamePoints.bluePoints : matchData_.currentGamePoints.redPoints;
    uint8_t lower =
        matchData_.currentGamePoints.bluePoints < matchData_.currentGamePoints.redPoints ?
            matchData_.currentGamePoints.bluePoints : matchData_.currentGamePoints.redPoints;

    if ( higher >= currentGameType_->gamePoint_ && (higher - lower) >= currentGameType_->pointsDifference_)
    {
        return true;
    }
    return false;
}

bool Match::getServ()
{
    return matchData_.isBlueServ;
}

uint8_t Match::getMaxServTimes()
{
    if ( matchData_.currentGamePoints.bluePoints >= currentGameType_->criticalPoints_
        && matchData_.currentGamePoints.redPoints >= currentGameType_->criticalPoints_)
    {
        return currentGameType_->afterCPSwitchPoints_;
    }
    return currentGameType_->beforeCPSwitchPoints_;
}

void Match::blueRedButtonShortClick(bool isBlue)
{
    if (currentState_ != State::RUNNING)
    {
        Serial.println(" not in RUNNING mode");
        return;
    }
    if (isSomeOneWin()) // current game already over, start a new game
    {
        matchData_.currentGamePoints.redPoints = 0;
        matchData_.currentGamePoints.bluePoints = 0;
    }

    if (isBlue)
    {
        matchData_.currentGamePoints.bluePoints += 1;
    }
    else
    {
        matchData_.currentGamePoints.redPoints += 1;
    }

    uint8_t maxServTimes = getMaxServTimes();

    matchData_.servingTimes += 1;
    if (matchData_.servingTimes >= maxServTimes)
    {
        matchData_.servingTimes = 0;
        matchData_.isBlueServ = !matchData_.isBlueServ;
    }

    if (isSomeOneWin())
    {
        // save currentGamePoints to previous
        // switch the first serv
        // switch the serv

        matchData_.servingTimes = 0;
        matchData_.isBlueServ = !matchData_.isBlueFirstServ;
        matchData_.isBlueFirstServ = matchData_.isBlueServ;
        saveCurrentToPrevious();
    }

    showCurrentMatchData("-----------short----------");
}

void Match::saveCurrentToPrevious()
{
    for (int i = 0; i < 16; i++)
    {
        Points& tmp = matchData_.previousGamesPoints[i];
        if (tmp.redPoints == 0 && tmp.bluePoints == 0)
        {
            tmp = matchData_.currentGamePoints;
            return;
        }
    }
    // all 16 are filled, clear it;
    matchData_.previousGamesPoints[0] = matchData_.currentGamePoints;
    for (int i = 1; i < 16; i++)
    {
        matchData_.previousGamesPoints[i] = {0, 0};
    }
}

void Match::blueRedButtonLongClick(bool isBlue)
{
    if (currentState_ == State::RUNNING) // just reset current game
    {
        matchData_.currentGamePoints = {0, 0};
        matchData_.servingTimes = 0;
        matchData_.isBlueServ = isBlue;
        matchData_.isBlueFirstServ = isBlue;
    }else if (currentState_ == State::IDLE) // reset all
    {
        currentState_ = State::RUNNING;
        clearMatchData();
        matchData_.isBlueServ = isBlue;
        matchData_.isBlueFirstServ = isBlue;
    }

    showCurrentMatchData("++++++++++long+++++++++++");
}

void Match::configButtonShortClick()
{
    if (currentState_ == State::RUNNING) // show all previous game points
    {
        Points res = getPreviousPoints();
        Serial.println("------------config short---------");
        Serial.println("previous game points : ");
        Serial.print("    blue : red ");
        Serial.print(static_cast<unsigned int>(res.bluePoints));
        Serial.print(" : ");
        Serial.println(static_cast<unsigned int>(res.redPoints));
    }
}

void Match::configButtonLongClick()
{
    if (currentState_ == State::RUNNING) // clear all and into IDLE
    {
        currentState_ = State::IDLE;
        clearMatchData();
    }
    else if(currentState_ == State::IDLE)
    {
        size_t gameTypeCount = sizeof(gameList)/sizeof(gameList[0]);
        if (currentGameTypeCount_ < gameTypeCount)
        {
            currentGameTypeCount_ += 1;
            currentGameType_ = &gameList[currentGameTypeCount_];
        }
        else
        {
            currentGameTypeCount_ = 0;
            currentGameType_ = &gameList[currentGameTypeCount_];
        }
    }
}


void Match::showCurrentMatchData(const char* mark)
{
    Serial.println(mark);
    Serial.print("game type : " );
    Serial.println(getCurrentGameType());
    Serial.println("game points : ");
    Serial.print("    BLUE : ");
    Serial.println(static_cast<unsigned int>(getGamePoints().bluePoints));
    Serial.print("    RED : ");
    Serial.println(static_cast<unsigned int>(getGamePoints().redPoints));
    Serial.println("current points : ");
    Serial.print("    blue : ");
    Serial.println(static_cast<unsigned int>(getCurrentPoints().bluePoints));
    Serial.print("    red : ");
    Serial.println(static_cast<unsigned int>(getCurrentPoints().redPoints));
    Serial.print("current serv : ");
    Serial.println((getServ()? "blue" : "red"));
}




