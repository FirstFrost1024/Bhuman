#include "SkillBehaviorControl.h"

option((SkillBehaviorControl) HandleGameState)
{
  common_transition
  {
    if(theGameState.isInitial())
      goto initial;
    else if(theGameState.isReady())
      goto ready;
    else if(theGameState.isSet())
      goto set;
    else if(theGameState.isPlaying())
      goto playing;
    else if(theGameState.isFinished())
      goto finished;
    FAIL("Unknown game state.");
  }

  // The default state is "playing".
  initial_state(playing)
  {
    action
    {
      LookForward();
      Stand({.high = false});
    }
  }

  state(initial)
  {
    action
    {
      LookAtAngles({.pan = 0_deg,
                    .tilt = 0_deg,
                    .speed = 150_deg});
      Stand({.high = true});
    }
  }

  state(ready)
  {
    action
    {
      ArmContact();
      if(theStrategyStatus.role != PositionRole::toRole(PositionRole::goalkeeper))
        ArmObstacleAvoidance();
      if(theSkillRequest.skill == SkillRequest::walk)
        WalkToPointReady({.target = theSkillRequest.target,
                          .reduceWalkSpeedType = theGameState.kickOffSetupFromTouchlines ? ReduceWalkSpeedType::distanceBased : ReduceWalkSpeedType::timeBased}); // TODO maybe more under specific conditions?
      else
      {
        LookActive({.ignoreBall = true});
        Stand();
      }
    }
  }

  state(set)
  {
    action
    {
      LookForward();
      Stand({.high = false});
    }
  }

  state(finished)
  {
    action
    {
      LookForward();
      Stand({.high = false});
    }
  }
}
