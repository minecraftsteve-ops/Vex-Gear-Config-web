/*
 * PROJECT 1: Robot Gear System Optimizer - ADVANCED SOLUTION
 * 
 * This program provides comprehensive analysis of all gear combinations
 * with bonus features including optimization analysis, statistics,
 * and engineering insights for robot competition teams.
 * 
 * Features:
 * - Complete 147 combination analysis
 * - Speed optimization (fastest/slowest setups)
 * - Balanced configuration finder (closest to target RPM)
 * - Perfect ratio analysis (whole number ratios)
 * - Comprehensive statistics and recommendations
 */

 #include <iostream>
 #include <iomanip>
 #include <cmath>
 using namespace std;
 
 // Struct to store gear combination data
 struct GearSetup {
     int inputRPM;
     int drivingGear;
     int drivenGear;
     double gearRatio;
     double outputRPM;
 };
 
 // Function prototypes
 double calculateGearRatio(int drivingGear, int drivenGear);
 double calculateOutputRPM(int inputRPM, int drivingGear, int drivenGear);
 void findOptimalSetups(const GearSetup setups[], int count);
 void analyzeStatistics(const GearSetup setups[], int count);
 void findPerfectRatios(const GearSetup setups[], int count);
 void findBalancedSetup(const GearSetup setups[], int count, double targetRPM);
 bool isWholeNumber(double value, double tolerance = 0.001);
 
 int main() {
     cout << "🤖 ROBOT GEAR SYSTEM OPTIMIZER - ADVANCED ANALYSIS 🤖" << endl;
     cout << "=======================================================" << endl;
     cout << "Professional Engineering Analysis for Competition Teams" << endl << endl;
     
     // Available components
     int inputRPMs[] = {100, 200, 600};
     int gearSizes[] = {12, 24, 36, 48, 60, 72, 80};
     
     int rpmCount = 3;
     int gearCount = 7;
     int totalCombinations = rpmCount * gearCount * gearCount;
     
     // Array to store all gear setups
     GearSetup allSetups[147];
     int setupIndex = 0;
     
     cout << "🔧 GENERATING ALL GEAR COMBINATIONS..." << endl;
     cout << "Processing " << totalCombinations << " configurations..." << endl << endl;
     
     // Generate all combinations and store in array
     for (int r = 0; r < rpmCount; r++) {
         for (int d = 0; d < gearCount; d++) {
             for (int n = 0; n < gearCount; n++) {
                 int inputRPM = inputRPMs[r];
                 int drivingGear = gearSizes[d];
                 int drivenGear = gearSizes[n];
                 
                 // Calculate gear properties
                 double gearRatio = calculateGearRatio(drivingGear, drivenGear);
                 double outputRPM = calculateOutputRPM(inputRPM, drivingGear, drivenGear);
                 
                 // Store in array
                 allSetups[setupIndex] = {inputRPM, drivingGear, drivenGear, gearRatio, outputRPM};
                 setupIndex++;
             }
         }
     }
     
     // Display sample combinations (first 10 and last 10)
     cout << "📋 SAMPLE COMBINATIONS (first 10):" << endl;
     cout << "Input RPM | Driving | Driven | Ratio | Output RPM" << endl;
     cout << "----------|---------|--------|-------|----------" << endl;
     
     for (int i = 0; i < 10; i++) {
         cout << setw(9) << allSetups[i].inputRPM << " | ";
         cout << setw(7) << allSetups[i].drivingGear << "T | ";
         cout << setw(6) << allSetups[i].drivenGear << "T | ";
         cout << setw(5) << fixed << setprecision(2) << allSetups[i].gearRatio << " | ";
         cout << setw(10) << setprecision(1) << allSetups[i].outputRPM << endl;
     }
     
     cout << "\n... (137 more combinations) ..." << endl;
     cout << "\nLast 3 combinations:" << endl;
     for (int i = 144; i < 147; i++) {
         cout << setw(9) << allSetups[i].inputRPM << " | ";
         cout << setw(7) << allSetups[i].drivingGear << "T | ";
         cout << setw(6) << allSetups[i].drivenGear << "T | ";
         cout << setw(5) << fixed << setprecision(2) << allSetups[i].gearRatio << " | ";
         cout << setw(10) << setprecision(1) << allSetups[i].outputRPM << endl;
     }
     
     cout << "\n" << string(55, '=') << endl;
     
     // Perform advanced analysis
     cout << "\n🏆 OPTIMIZATION ANALYSIS:" << endl;
     findOptimalSetups(allSetups, totalCombinations);
     
     cout << "\n" << string(55, '=') << endl;
     
     cout << "\n⚖️ BALANCED ROBOT ANALYSIS:" << endl;
     findBalancedSetup(allSetups, totalCombinations, 300.0);
     
     cout << "\n" << string(55, '=') << endl;
     
     cout << "\n🎯 PERFECT RATIO ANALYSIS:" << endl;
     findPerfectRatios(allSetups, totalCombinations);
     
     cout << "\n" << string(55, '=') << endl;
     
     cout << "\n📊 COMPREHENSIVE STATISTICS:" << endl;
     analyzeStatistics(allSetups, totalCombinations);
     
     cout << "\n" << string(55, '=') << endl;
     
     cout << "\n🚀 ANALYSIS COMPLETE!" << endl;
     cout << "Total combinations analyzed: " << totalCombinations << endl;
     cout << "Your robot is ready for competition! 🏁" << endl;
     
     return 0;
 }
 
 // Calculate gear ratio
 double calculateGearRatio(int drivingGear, int drivenGear) {
     return (double)drivenGear / drivingGear;
 }
 
 // Calculate output RPM
 double calculateOutputRPM(int inputRPM, int drivingGear, int drivenGear) {
     double gearRatio = calculateGearRatio(drivingGear, drivenGear);
     return inputRPM / gearRatio;
 }
 
 // Find fastest and slowest setups
 void findOptimalSetups(const GearSetup setups[], int count) {
     GearSetup fastest = setups[0];
     GearSetup slowest = setups[0];
     
     for (int i = 1; i < count; i++) {
         if (setups[i].outputRPM > fastest.outputRPM) {
             fastest = setups[i];
         }
         if (setups[i].outputRPM < slowest.outputRPM) {
             slowest = setups[i];
         }
     }
     
     cout << "⚡ FASTEST SETUP (Maximum Speed):" << endl;
     cout << "   Input: " << fastest.inputRPM << " RPM | Gears: " 
          << fastest.drivingGear << "T → " << fastest.drivenGear << "T" << endl;
     cout << "   Ratio: " << fixed << setprecision(2) << fastest.gearRatio 
          << ":1 | Output: " << setprecision(1) << fastest.outputRPM << " RPM" << endl;
     cout << "   → Best for: Speed challenges, racing, quick traversal" << endl;
     
     cout << "\n🐌 SLOWEST SETUP (Maximum Torque):" << endl;
     cout << "   Input: " << slowest.inputRPM << " RPM | Gears: " 
          << slowest.drivingGear << "T → " << slowest.drivenGear << "T" << endl;
     cout << "   Ratio: " << fixed << setprecision(2) << slowest.gearRatio 
          << ":1 | Output: " << setprecision(1) << slowest.outputRPM << " RPM" << endl;
     cout << "   → Best for: Heavy lifting, climbing, pushing objects" << endl;
 }
 
 // Find setup closest to target RPM
 void findBalancedSetup(const GearSetup setups[], int count, double targetRPM) {
     GearSetup balanced = setups[0];
     double smallestDifference = abs(setups[0].outputRPM - targetRPM);
     
     for (int i = 1; i < count; i++) {
         double difference = abs(setups[i].outputRPM - targetRPM);
         if (difference < smallestDifference) {
             smallestDifference = difference;
             balanced = setups[i];
         }
     }
     
     cout << "⚖️ MOST BALANCED SETUP (closest to " << targetRPM << " RPM):" << endl;
     cout << "   Input: " << balanced.inputRPM << " RPM | Gears: " 
          << balanced.drivingGear << "T → " << balanced.drivenGear << "T" << endl;
     cout << "   Ratio: " << fixed << setprecision(2) << balanced.gearRatio 
          << ":1 | Output: " << setprecision(1) << balanced.outputRPM << " RPM" << endl;
     cout << "   Difference from target: " << setprecision(1) << smallestDifference << " RPM" << endl;
     cout << "   → Best for: All-around performance, versatile robot" << endl;
 }
 
 // Analyze perfect ratios
 void findPerfectRatios(const GearSetup setups[], int count) {
     int perfectCount = 0;
     
     cout << "🎯 PERFECT RATIO SETUPS (whole number ratios):" << endl;
     
     for (int i = 0; i < count; i++) {
         if (isWholeNumber(setups[i].gearRatio)) {
             perfectCount++;
             if (perfectCount <= 10) { // Show first 10 examples
                 cout << "   " << setups[i].inputRPM << " RPM | " 
                      << setups[i].drivingGear << "T → " << setups[i].drivenGear << "T | "
                      << "Ratio: " << fixed << setprecision(0) << setups[i].gearRatio << ":1 | "
                      << "Output: " << setprecision(1) << setups[i].outputRPM << " RPM" << endl;
             }
         }
     }
     
     if (perfectCount > 10) {
         cout << "   ... and " << (perfectCount - 10) << " more perfect ratios" << endl;
     }
     
     cout << "\n🎯 PERFECT RATIO SUMMARY:" << endl;
     cout << "   Total perfect ratios: " << perfectCount << " out of " << count << endl;
     cout << "   Percentage: " << fixed << setprecision(1) 
          << (double)perfectCount / count * 100 << "%" << endl;
     cout << "   → Perfect ratios provide predictable, easy-to-calculate speeds" << endl;
 }
 
 // Comprehensive statistics
 void analyzeStatistics(const GearSetup setups[], int count) {
     double totalOutput = 0;
     double maxOutput = setups[0].outputRPM;
     double minOutput = setups[0].outputRPM;
     
     for (int i = 0; i < count; i++) {
         totalOutput += setups[i].outputRPM;
         if (setups[i].outputRPM > maxOutput) maxOutput = setups[i].outputRPM;
         if (setups[i].outputRPM < minOutput) minOutput = setups[i].outputRPM;
     }
     
     double averageOutput = totalOutput / count;
     double speedRange = maxOutput - minOutput;
     
     // Count by speed categories
     int highSpeed = 0, mediumSpeed = 0, lowSpeed = 0;
     for (int i = 0; i < count; i++) {
         if (setups[i].outputRPM > 500) highSpeed++;
         else if (setups[i].outputRPM > 100) mediumSpeed++;
         else lowSpeed++;
     }
     
     // Count by input RPM
     int count100 = 0, count200 = 0, count600 = 0;
     for (int i = 0; i < count; i++) {
         if (setups[i].inputRPM == 100) count100++;
         else if (setups[i].inputRPM == 200) count200++;
         else count600++;
     }
     
     cout << "📈 SPEED DISTRIBUTION:" << endl;
     cout << "   Fastest setup: " << fixed << setprecision(1) << maxOutput << " RPM" << endl;
     cout << "   Slowest setup: " << setprecision(1) << minOutput << " RPM" << endl;
     cout << "   Average speed: " << setprecision(1) << averageOutput << " RPM" << endl;
     cout << "   Speed range: " << setprecision(1) << speedRange << " RPM" << endl;
     
     cout << "\n🎯 SPEED CATEGORIES:" << endl;
     cout << "   High Speed (500+ RPM): " << highSpeed << " setups (" 
          << setprecision(1) << (double)highSpeed/count*100 << "%)" << endl;
     cout << "   Medium Speed (100-500 RPM): " << mediumSpeed << " setups (" 
          << setprecision(1) << (double)mediumSpeed/count*100 << "%)" << endl;
     cout << "   Low Speed (<100 RPM): " << lowSpeed << " setups (" 
          << setprecision(1) << (double)lowSpeed/count*100 << "%)" << endl;
     
     cout << "\n🔧 INPUT RPM DISTRIBUTION:" << endl;
     cout << "   100 RPM motor: " << count100 << " combinations (49 each)" << endl;
     cout << "   200 RPM motor: " << count200 << " combinations (49 each)" << endl;
     cout << "   600 RPM motor: " << count600 << " combinations (49 each)" << endl;
     
     cout << "\n💡 ENGINEERING RECOMMENDATIONS:" << endl;
     if (highSpeed > 50) {
         cout << "   → Plenty of high-speed options for racing challenges" << endl;
     }
     if (lowSpeed > 30) {
         cout << "   → Good torque options available for heavy-duty tasks" << endl;
     }
     cout << "   → " << averageOutput << " RPM average provides balanced performance" << endl;
     cout << "   → " << speedRange << " RPM range offers maximum flexibility" << endl;
 }
 
 // Check if a number is close to a whole number
 bool isWholeNumber(double value, double tolerance) {
     return abs(value - round(value)) < tolerance;
 } 