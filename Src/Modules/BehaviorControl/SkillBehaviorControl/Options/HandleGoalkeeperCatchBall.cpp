#include "SkillBehaviorControl.h"
#include "Tools/BehaviorControl/Interception.h"

option((SkillBehaviorControl) HandleGoalkeeperCatchBall)
{
  initial_state(notCatching)
  {
    transition
    {
      if(theGameState.isGoalkeeper() &&
         between<float>(theFieldInterceptBall.timeUntilIntersectsOwnYAxis,
                        theBehaviorParameters.goalkeeperCatchEnterTimeUntilYAxis.min,
                        theBehaviorParameters.goalkeeperCatchEnterTimeUntilYAxis.max) &&
         theFieldBall.ballWasSeen(100) &&
         theFieldBall.isRollingTowardsOwnGoal &&
         theFieldBall.positionRelative.squaredNorm() < sqr(theBehaviorParameters.goalkeeperCatchMaxDistance) &&
         (theBehaviorParameters.goalkeeperCatchMinBallSpeed <= 0.f ||
          theFieldBall.velocityRelative.squaredNorm() >= sqr(theBehaviorParameters.goalkeeperCatchMinBallSpeed)))
        goto preparingCatch;
    }
  }

  state(preparingCatch)
  {
    transition
    {
      if(!(between<float>(theFieldInterceptBall.timeUntilIntersectsOwnYAxis,
                          theBehaviorParameters.goalkeeperCatchHoldTimeUntilYAxis.min,
                          theBehaviorParameters.goalkeeperCatchHoldTimeUntilYAxis.max) &&
           theFieldBall.ballWasSeen(100) &&
           theFieldBall.isRollingTowardsOwnGoal &&
           theFieldBall.positionRelative.squaredNorm() < sqr(theBehaviorParameters.goalkeeperCatchMaxDistance) &&
           (theBehaviorParameters.goalkeeperCatchMinBallSpeed <= 0.f ||
            theFieldBall.velocityRelative.squaredNorm() >= sqr(theBehaviorParameters.goalkeeperCatchMinBallSpeed))))
        goto notCatching;
      if(state_time >= 100)
        goto doingCatch;
    }
    action
    {
      LookAtBall();
      KeyFrameArms({.motion = ArmKeyFrameRequest::keeperStand});
      Stand(/*{.energySavingWalk = false}*/); // TODO We do not want the keeper to stand still, for example in case the keeper is currently fighting for the ball.
    }
  }

  state(doingCatch)
  {
    transition
    {
      if(action_done || !theFieldInterceptBall.interceptBall)
        goto notCatching;
    }
    action
    {
      //calculate isNearPost
      const auto [isNearLeftPost, isNearRightPost] = theLibPosition.isNearPost(theRobotPose);

      unsigned interceptionMethods = bit(Interception::stand) | bit(Interception::walk);
      if(theLibPosition.isInOwnPenaltyArea(theRobotPose.translation))
      {
        if(!isNearLeftPost)
          interceptionMethods |= bit(Interception::jumpLeft);
        if(!isNearRightPost)
          interceptionMethods |= bit(Interception::jumpRight);
      }

      InterceptBall({.interceptionMethods = interceptionMethods,
                     .allowDive = theBehaviorParameters.keeperJumpingOn});
    }
  }
}
