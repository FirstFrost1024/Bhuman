#include "SkillBehaviorControl.h"

option((SkillBehaviorControl)HandlePlayingOptions)
{
  // The default state is "playing".
  initial_state(initial)
  {
    action
    {
      if(theGameState.isSet() || theGameState.isPlaying() || theGameState.isFinished())
      {
        LookForward();
        Stand({.high = false});
      }
      else if(!select_option(playingOptions))   //@playingOptions
        executeRequest();
    }
  }
}
