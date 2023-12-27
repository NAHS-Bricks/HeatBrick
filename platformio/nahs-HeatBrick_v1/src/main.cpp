#include <Arduino.h>
#include <nahs-Bricks-OS.h>
// include all features of brick
#include <nahs-Bricks-Feature-Heat.h>
#include <nahs-Bricks-Feature-Latch.h>
#include <nahs-Bricks-Feature-Signal.h>
#include <nahs-Bricks-Feature-Temp.h>

void setup() {
  // Now register all the features under All
  // Note: the order of registration is the same as the features are handled internally by FeatureAll
  // Attention: for some reason the only working order for this Brick is: Latch, Heat, Temp, Signal
  FeatureAll.registerFeature(&FeatureLatch);
  FeatureAll.registerFeature(&FeatureHeat);
  FeatureAll.registerFeature(&FeatureTemp);
  FeatureAll.registerFeature(&FeatureSignal);
 
  // Set Brick-Specific stuff
  BricksOS.setSetupPin(D7);
  FeatureAll.setBrickType(6);

  // Set Brick-Specific (feature related) stuff
  Wire.begin();
  LatchExpander.begin(45);
  FeatureLatch.assignLatch(LatchExpander);
  FeatureLatch.assignLatchPin(0);
  FeatureLatch.assignLatchPin(1);
  FeatureLatch.assignLatchPin(2);
  FeatureLatch.assignLatchPin(3);
  FeatureHeat.setHeatPin(LatchExpander, 0);
  FeatureHeat.setTempPin(D6);
  FeatureTemp.setSensorsPin(D5);
  FeatureSignal.assignExpanderPin(LatchExpander, 1);
  FeatureSignal.assignExpanderPin(LatchExpander, 2);
  FeatureSignal.assignExpanderPin(LatchExpander, 3);

  // Finally hand over to BrickOS
  BricksOS.handover();
}

void loop() {
  // Not used on Bricks
}