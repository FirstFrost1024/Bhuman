/**
 * @file Representations/Configuration/BehaviorParameters/BehaviorParameters.h
 *
 * The file declares a struct that contains frequently used parameters of the behavior which can be modified.
 *
 * @author Andreas Stolpmann
 */

#pragma once

#include "Math/Angle.h"

STREAMABLE(BehaviorParameters,
{,
  (bool) keeperJumpingOn, /**< Use this configuration parameter to prevent keeper from jumping (and maybe hurting itself) - default == true */

  (float) goalkeeperCatchMaxDistance, /**< mm; max robot-ball distance to start goalkeeper catch preparation (smaller => only when ball is closer). */
  (float) goalkeeperCatchMinBallSpeed, /**< mm/s; min FieldBall.velocityRelative norm to start catch; 0 disables this filter (faster ball required when > 0). */
  (Rangef) goalkeeperCatchEnterTimeUntilYAxis, /**< s until ball crosses own Y axis: [min,max] window for notCatching -> preparingCatch (smaller max => react later). */
  (Rangef) goalkeeperCatchHoldTimeUntilYAxis, /**< s window while staying in preparingCatch (abort if prediction leaves this band). */

  (Angle) penaltyStrikerAngleToLeftPostOffset,  /**< (the greater the value, the closer to the center the robot will shoot) */
  (Angle) penaltyStrikerAngleToRightPostOffset,  /**< (the greater the value, the closer to the center the robot will shoot) */
  (bool) penaltyStrikerUseObstacles, /**< Whether the penalty striker should use the obstacle model to kick in the more free corner */

  (Angle) defaultLookDownAngle, /**< Use this default head tilt */

  (float) ballCatchMaxWalkDistance,

  (float) standRadius, /**< The range that is covered by just standing. */
  (Rangef) walkRadius, /**< The range that is covered by walking. */
  (Rangef) timeForInterceptionForMaxWalkRadius, /**< The ball needs this time until interception to allow for the max walk radius. */
  (float) genuflectRadius, /**< The range that is covered with the penalty keeper genuflect. */
  (float) genuflectStandRadius, /**< The range that is covered with a genuflect. */
  (float) jumpRadius, /**< The range that is covered with a keeper jump. */
  (float) timeForJump, /**< Time of a jump until the robot starts to hold a ball. */

  (int) noCommunicationAfterUnpenalizedTime, /**< Prevent communication when freshly unpenalized. */
  (int) noSkillRequestAfterUnpenalizedTime, /**< Prevent behavior calulcation when freshly unpenalized. Should be bigger than noCommunicationAfterUnpenalizedTime. */
  (int) lookAroundAfterUnpenalizedTime, /**< Look around after unpenalized. Should be bigger than lookAroundAfterUnpenalizedTime. */
});
