# B-Human Code Release

This is the official 2025 B-Human code release. Documentation can be found [here](https://docs.b-human.de/coderelease2025/).

B-Human is a research project. We provide the software as is. We release it as a snapshot of our internal repository on a yearly basis. You can build on this software, but you have to make do with the documentation we released. You may report bugs or problems with newer releases of operating systems or the tools used by opening a GitHub issue. We might give hints on how to solve these problems if we also ran into them since the code release. Do not write emails to the team or any of its members directly. They will not be answered.

Before cloning this repository, you must read our [license terms](License.md) and the [instructions in our documentation](https://docs.b-human.de/coderelease2025/getting-started/initial-setup/).

Previous code releases are tagged with "coderelease&lt;year&gt;", where &lt;year&gt; is the year in which the code was released (starting with 2013).

## walkingEngineCommon.cfg 参数说明

本章节说明 `Config/Robots/Default/walkingEngineCommon.cfg` 中每一个参数对象及其内部字段含义，便于调参时快速定位功能影响。单位约定通常为：
- 角度：`deg`
- 时间：`ms` 或相位比例（0~1）
- 距离：毫米（mm）
- 速度/加速度：与步行模型一致的内部单位（通常可理解为每秒相关量）

### 全局参数（对象外）

- `minPhaseForStopWithWrongGroundContact`：在步态相位达到该阈值后，才允许因错误地面接触触发停止，避免过早误判。
- `clipAtBallDistanceX`：沿 x 方向对与球距离进行裁剪的阈值，用于限制近球场景下的控制量。
- `clipAtBallDistance`：对球距离的总体裁剪阈值，限制与球相关的步态修正幅度。
- `standHighTorsoPitch`：高站姿下躯干前后俯仰目标角。
- `standHighInterpolationDuration`：切换到高站姿时的插值时长。
- `standInterpolationVelocity`：站姿插值的最大角速度限制。
- `maxStandInterpolationDuration`：站姿过渡允许的最大持续时间。
- `standHighNotMovingTime`：机器人静止达到该时间后才进入/保持高站姿。
- `minTimeForEarlySwitch`：允许提前切换支撑脚/步态阶段的最小时间。
- `maxWalkDirectionForFootPrediction`：启用落脚预测时可接受的最大行走方向偏角。
- `useFootSupportSwitchPrediction`：是否启用支撑脚切换预测。
- `blockStoppingWithStepAdjustment`：是否在步幅调整过程中阻止立即停走，以保持稳定。
- `useJointPlayScaling`：是否启用关节间隙（机械松旷）相关缩放补偿。

### `commonSpeedParameters`

- `maxAcceleration`：步速增加时的最大加速度限制。
  - `x`：前后方向最大加速度。
  - `y`：左右方向最大加速度。
- `maxDeceleration`：减速时的最大减速度限制。
  - `x`：前后方向最大减速度。
  - `y`：左右方向最大减速度。
- `fastFeetAdjustment`：高速状态下足端位置快速修正增益/幅度。
- `slowFeetAdjustment`：低速状态下足端位置慢速修正增益/幅度。
- `soleRotationOffsetSpeed`：足底旋转补偿速度范围。
  - `min`：最小补偿速度。
  - `max`：最大补偿速度。
- `soleRotationOffsetSpeedAfterKickTime`：踢球后经过该时间，开始/增强足底旋转补偿速度逻辑。
- `walkSpeedReductionFactor`：触发降速策略时的速度缩放因子。
- `reduceWalkingSpeedStepAdjustmentSteps`：步幅调整后持续降速的步数。
- `afterKickFeetHeightAdjustment`：踢球后额外足抬高补偿量。
- `maxSwingStretchLength`：摆动腿在前后方向的最大拉伸补偿。
- `maxSwingSideStretch`：摆动腿在侧向的最大拉伸补偿。
- `swingStretchAfterOvertime`：步态超时后摆动腿拉伸策略的触发时间。

### `kinematicParameters`

- `baseWalkPeriod`：基础步态周期。
- `sidewaysWalkHeightPeriodIncreaseFactor`：侧向行走时步高/周期关联的放大系数。
- `sidewaysHipShiftFactor`：侧向行走时髋部横移系数。
- `walkHipHeight`：行走髋高范围。
  - `min`：最小髋高。
  - `max`：最大髋高。
- `energyEfficientWalkSpeed`：节能模式下速度上限。
  - `maxSpeed.rotation`：最大转身角速度。
  - `maxSpeed.translation.x`：最大前后平移速度。
  - `maxSpeed.translation.y`：最大侧向平移速度。
  - `maxSpeedBackwards`：最大后退速度。
- `noEfficientWalkSpeed`：非节能（性能优先）模式下速度上限。
  - `maxSpeed.rotation`：最大转身角速度。
  - `maxSpeed.translation.x`：最大前后平移速度。
  - `maxSpeed.translation.y`：最大侧向平移速度。
  - `maxSpeedBackwards`：最大后退速度。
- `hipHeightChangeSpeed`：髋高变化速度范围。
  - `min`：最低变化速度（可为下降方向）。
  - `max`：最高变化速度。
- `baseFootLift`：基础抬脚高度。
- `torsoOffset`：躯干姿态/位置的基础偏置。
- `legLengthClipThreshold`：腿长计算的裁剪阈值，避免极端值。
- `yHipOffset`：髋部在 y 方向的固定偏移。

### `emergencyStep`

- `emergencyStepSize`：紧急步的步长/步幅。
- `emergencyStepHeightFactor`：紧急步抬脚高度放大系数。
- `emergencyMaxGyroMean`：触发紧急步时可接受的陀螺仪均值阈值。
- `emergencyMaxGyroDeviation`：陀螺仪波动（标准差/偏差）阈值。
- `emergencyMaxZGyroDeviation`：绕 z 轴角速度波动阈值。
- `emergencyAfterStepDuration`：紧急步完成后的保护持续时间。

### `armParameters`

- `armShoulderRoll`：手臂基础肩横摆（roll）角。
- `armShoulderRollIncreaseFactor`：肩横摆随步态/平衡增加的放大因子。
- `armShoulderPitchFactor`：肩俯仰联动系数。
- `comTiltFactor`：根据质心倾斜调整摆臂的比例系数。
- `armInterpolationTime`：手臂目标角插值时间。
- `armShoulderPitch`：手臂基础肩俯仰角。
- `armElbowYaw`：手肘偏航基础角。

### `stepSizeParameters`

- `insideTurnRatio`：内侧腿转向时步幅缩放比例。
- `reduceTranslationFromRotation`：开始因转向削减平移的角度阈值。
  - `x`：前后平移削减阈值。
  - `y`：侧向平移削减阈值。
- `noTranslationFromRotation`：转向超过该阈值时，平移分量降为零。
  - `x`：前后平移归零阈值。
  - `y`：侧向平移归零阈值。
- `noTranslationYFromRotationFastInner`：快速转向内侧时侧向平移归零阈值。
- `noTranslationYFromRotationFastOuter`：快速转向外侧时侧向平移归零阈值。
- `reduceTranslationYFromRotationFast`：快速转向时开始削减侧向平移的阈值。
- `minXTranslationStep`：x 方向最小平移步长。
- `minXForwardTranslationFast`：快速模式下前向最小有效步长。
- `minXBackwardTranslationFastRange`：快速后退最小步长范围。
  - `min`：较缓条件下阈值。
  - `max`：激进条件下阈值。
- `translationPolygonSafeRange`：平移步在安全多边形内的限制区间（约束对角大步）。
  - `min`：下限。
  - `max`：上限。
- `noFastTranslationPolygonStepsNumber`：禁用快速平移多边形策略的连续步数。

### `balanceParameters`

- `gyroLowPassRatio`：陀螺仪低通滤波系数。
- `gyroForwardBalanceFactor`：前倾方向陀螺反馈平衡系数。
- `gyroBackwardBalanceFactor`：后仰方向陀螺反馈平衡系数。
- `gyroSidewaysBalanceFactor`：侧倾方向陀螺反馈平衡系数。
- `gyroHipKneeBalanceFactor`：通过髋/膝补偿的陀螺平衡系数。
- `gyroHipKneeKickBalanceFactor`：踢球相关场景下髋/膝平衡系数。
- `slowdownTorsoOffset`：触发减速前允许的躯干偏置量。
- `slowdownFactor`：减速时的缩放系数。
- `minTorsoRotation`：触发躯干旋转补偿的最小角度。
- `allowSlowDownWhenWalkingBackwards`：后退行走时是否允许自动减速。
- `sideTorsoRange`：侧向躯干补偿角度范围。
  - `min`：最小补偿角。
  - `max`：最大补偿角。
- `sideComRange`：侧向质心补偿范围。
  - `min`：最小补偿量。
  - `max`：最大补偿量。
- `gyroSideTorsoBalance`：陀螺驱动的侧向躯干平衡系数。
- `maxGyroAnkleBalance`：踝关节可承担的最大陀螺补偿量。

### `walkStepAdjustmentParams`

- `maxVelX`：允许步幅调整的 x 方向最大速度。
- `minVelX`：允许步幅调整的 x 方向最小速度。
- `removeSpeedX`：超过/低于该条件时移除某些 x 方向速度补偿。
- `comLowPassRatio`：质心估计低通滤波系数。
- `desiredFootAreaSmall`：小步态情况下期望足底受力区域。
  - `min`：下限。
  - `max`：上限。
- `desiredFootAreaBig`：大步态情况下期望足底受力区域。
  - `min`：下限。
  - `max`：上限。
- `desiredFootAreaForwardOvertime`：前向超时时的期望足底区域目标。
- `overtimeRange`：判定步态超时的范围阈值。
- `footAreaWalkSpeedScale`：足底区域对步速的缩放影响范围。
  - `min`：最小缩放。
  - `max`：最大缩放。
- `unstableWalkThreshold`：判定行走不稳定的阈值。
- `reduceWalkingSpeedTimeWindow`：降速策略的时间窗口。
- `useFullSwingSole`：是否在摆动相使用完整足底补偿。
- `swingAcc`：摆动腿加速度相关阈值/目标。
- `supportAcc`：支撑腿加速度相关阈值/目标。
- `useAccelerations`：是否显式使用加速度量参与步幅调整。

### `soleRotationParameter`

- `minTorsoRotation`：触发足底旋转补偿的最小躯干旋转。
- `maxTorsoRotation`：足底旋转补偿考虑的最大躯干旋转。
- `soleCompensationBackwardReduction`：后退时足底补偿衰减比例。
- `soleCompensationSpeed`：足底补偿变化速度。
  - `x`：绕前后轴相关补偿速度。
  - `y`：绕侧向轴相关补偿速度。
- `maxRollAdjustment`：横滚补偿最大角度。
- `measuredErrorFactor`：实测误差注入补偿的比例因子。
- `reductionTimeFactor`：补偿随时间衰减系数。
- `measuredErrorTimeScaling`：实测误差的时间缩放范围。
  - `min`：最小缩放。
  - `max`：最大缩放。
- `timeScaling`：通用补偿时间缩放范围。
  - `min`：最小缩放。
  - `max`：最大缩放。
- `timeScalingRoll`：横滚补偿时间缩放范围。
  - `min`：最小缩放。
  - `max`：最大缩放。
- `sideSizeXRotationScaling`：侧向步幅与 x 轴旋转耦合缩放范围。
  - `min`：最小缩放基准。
  - `max`：最大缩放基准。
- `removeYCompensationAtStart`：起步阶段移除 y 向补偿的阈值角。
- `tiltErrorDiffOffset`：倾斜误差差分偏移范围。
  - `min`：最小偏移。
  - `max`：最大偏移。
- `tiltErrorDiffScaling`：倾斜误差差分缩放系数。
- `gyroScaling`：陀螺值映射到补偿的缩放区间。
  - `min`：区间下限。
  - `max`：区间上限。
- `torsoRange`：躯干角度有效区间。
  - `min`：下限。
  - `max`：上限。
- `deltaRange`：误差差值有效区间。
  - `min`：下限。
  - `max`：上限。
- `comXRange`：质心 x 向有效区间。
  - `min`：下限。
  - `max`：上限。
- `maxStepRatioToStart`：开始应用该补偿的步态比例范围。
  - `min`：最早起始比例。
  - `max`：最晚起始比例。
- `minGyro`：启用该补偿需要达到的最小陀螺阈值。
- `minSideStepSize`：启用侧向补偿的最小侧步大小。
- `deltaRangeSecondStep`：第二步补偿使用的误差差值区间。
  - `min`：下限。
  - `max`：上限。
- `scalingClipRange`：最终缩放值裁剪范围。
  - `min`：最小裁剪值。
  - `max`：最大裁剪值。
- `minMaxSumScaling`：多缩放项求和后的允许范围。
  - `min`：下限。
  - `max`：上限。

### `parabolicFootHeightParameters`

- `maxHeightAfterTime`：抛物线抬脚轨迹达到最大高度对应的时间点。
- `maxHeightAfterTimePercent`：最大高度出现时间在单步中的比例位置。

### `walkStiffnessParameters`

- `walkStiffness`：正常行走刚度。
- `pickedUpStiffness`：机器人被抱起/离地时使用的刚度。
- `lowStiffnessDelay`：降低刚度前的延迟时间。
- `standStiffnessDelay`：站立状态切换刚度前的延迟。
- `lowStiffnessLegs`：低刚度模式下腿部刚度。
- `lowStiffnessAnklePitch`：低刚度模式下踝俯仰刚度。
- `lowWalkStiffness`：低功耗/低负载行走刚度。

### `speedControlParams`

- `rotationSpeedHYP`：髋偏航俯仰（HYP）关节旋转速度调节范围。
  - `min`：低速端参数。
  - `max`：高速端参数。
- `rotationSpeedHip`：髋关节旋转速度调节范围。
  - `min`：低速端参数。
  - `max`：高速端参数。
- `rotationSpeedAnklePitch`：踝俯仰旋转速度调节范围。
  - `min`：低速端参数。
  - `max`：高速端参数。
- `rotationSpeedKnee`：膝关节旋转速度调节范围。
  - `min`：低速端参数。
  - `max`：高速端参数。
- `rotationSpeedRoll`：横滚相关旋转速度调节范围。
  - `min`：低速端参数。
  - `max`：高速端参数。
- `pitchRatioForward`：前向俯仰误差比例范围。
  - `min`：较保守比例。
  - `max`：较激进比例。
- `pitchRatioBackward`：后向俯仰误差比例范围。
  - `min`：较保守比例。
  - `max`：较激进比例。
- `rollRatio`：横滚误差比例范围。
  - `min`：较保守比例。
  - `max`：较激进比例。
- `rotationErrorRatioForwardWornOut`：关节磨损状态下前向旋转误差比例区间。
  - `min`：下限。
  - `max`：上限。
- `rotationErrorRatioForwardGood`：关节状态良好时前向旋转误差比例区间。
  - `min`：下限。
  - `max`：上限。
- `rotationErrorRatioBackward`：后向旋转误差比例区间。
  - `min`：下限。
  - `max`：上限。

### `walkDelayParameters`

- `minDelay`：步态控制最小延迟（通常约等于若干帧）。
- `heightOffset`：与步高相关的延迟偏移范围。
  - `min`：最小偏移。
  - `max`：最大偏移。
- `endHeightShift`：步末期额外高度平移补偿。
- `delayInterpolation`：延迟插值范围。
  - `min`：最小延迟插值。
  - `max`：最大延迟插值。
- `sideShift`：侧向位移补偿范围。
  - `min`：最小侧移。
  - `max`：最大侧移。
- `sideShiftDelayInterpolation`：侧移对应的延迟插值范围。
  - `min`：最小插值。
  - `max`：最大插值。
- `translationBuffer`：平移指令缓冲量。
- `kickTimeOffset`：踢球时序偏移范围。
  - `min`：较早时序偏移。
  - `max`：较晚时序偏移。
- `kickTimeBallDistanceScaling`：踢球时序随球距离缩放范围。
  - `min`：近距离缩放基准。
  - `max`：远距离缩放基准。

### `walkSpeedParamsWalkStep`

- `maxSpeed`：步态步模式的速度上限。
  - `rotation`：最大转身角速度。
  - `translation.x`：最大前后平移速度。
  - `translation.y`：最大侧向平移速度。
- `maxSpeedBackwards`：最大后退速度。

### `sideStabilizeParameters`

- `turnIncreaseRange`：转向增强区间。
  - `min`：开始增强阈值。
  - `max`：完全增强阈值。
- `increaseThreshold`：触发侧向稳定增强的阈值。
- `minOuterSide`：外侧支撑占比最小要求。
- `minOuterSideStop`：停止阶段外侧支撑占比最小要求。
- `sideHipShiftStepSizeRange`：侧向髋移与步长关联范围。
  - `min`：小步长侧髋移基准。
  - `max`：大步长侧髋移基准。
- `maxSideHipShift`：侧向髋移最大量。
- `maxSideHipShiftStepSize`：触发最大髋移对应的步长。
- `comInOuterInterpolationRange`：质心在内外支撑间插值区间。
  - `min`：区间下限。
  - `max`：区间上限。
- `heightRange`：高度缩放范围。
  - `min`：最低缩放。
  - `max`：最高缩放。
- `firstStepHeightRange`：首步高度范围系数。
- `lastLastWalkPhaseStepDuration`：倒数第二步阶段时长比例。
- `lastWalkPhaseStepDuration`：最后一步阶段时长比例。
- `delayRange`：侧向稳定延迟范围。
  - `min`：最小延迟。
  - `max`：最大延迟。
- `minHipShiftRatioForDelay`：考虑延迟时髋移比例下限。
- `maxNextSideStepSize`：下一侧步允许的最大步长。

### `walkHipShiftPhaseParameters`

- `shiftSpeed`：髋移阶段常规平移速度。
- `shiftSpeedStart`：髋移阶段起始速度。
- `comYStopConditionWalking`：行走中停止髋移的质心 y 条件。
  - `min`：下限。
  - `max`：上限。
- `comYStopConditionStarting`：起步阶段停止髋移的质心 y 阈值。
- `maxShift`：髋移最大比例范围。
  - `min`：最小比例。
  - `max`：最大比例。
- `comShiftScalingBackward`：后向时质心位移缩放范围。
  - `min`：下限。
  - `max`：上限。
- `comShiftScalingForward`：前向时质心位移缩放范围。
  - `min`：下限。
  - `max`：上限。
- `comShiftScalingWalkingBackward`：行走后向阶段质心位移缩放范围。
  - `min`：下限。
  - `max`：上限。
- `comShiftScalingWalkingForward`：行走前向阶段质心位移缩放范围。
  - `min`：下限。
  - `max`：上限。
- `deltaScaling`：误差差值对髋移的缩放范围。
  - `min`：下限。
  - `max`：上限。
- `minShiftStartWalking`：行走时开始髋移的最小阈值。
- `useHipShift`：是否启用该髋移阶段控制。

### `sideCatchWalkParameters`

- `allowedAdjustmentDuringTimeRatio`：允许侧向补偿的时间比例区间。
  - `min`：开始比例。
  - `max`：结束比例。
- `comYThreshold`：触发侧向捕捉步的质心 y 阈值区间。
  - `min`：下限。
  - `max`：上限。
- `maxAdjustment`：单步最大侧向补偿量。

### `supportCompensationParameters`

- `lowPassFilterSlow`：慢速低通滤波系数。
- `lowPassFilterFast`：快速低通滤波系数。
- `isActive`：是否启用支撑补偿模块。
- `scaling`：支撑补偿整体缩放系数。
- `timeScaling`：支撑补偿时间缩放范围。
  - `min`：最小缩放。
  - `max`：最大缩放。
