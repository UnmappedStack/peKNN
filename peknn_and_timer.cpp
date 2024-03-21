#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;
using namespace std::chrono;

// This is literally just a KNN normal thingy for now

float euclidean2d(float x1, float y1, float x2, float y2) {
  float xdiff = abs(x1 - x2) * 2;
  float ydiff = abs(y1 - y2) * 2;
  return ydiff + xdiff;
}

float basic2d(float x1, float y1, float x2, float y2) {
  float xdiff = abs(x1 - x2);
  float ydiff = abs(y1 - y2);
  return ydiff + xdiff;
}
vector<int> smallestIndexes(vector<float> vec, int x) {
    vector<int> result;
    
    // Create a copy of the original vector along with indices
    vector<pair<float, int>> indexedVec;
    for (int i = 0; i < vec.size(); ++i) {
        indexedVec.push_back(make_pair(vec[i], i));
    }
    
    // Sort the indexed vector based on the first element (float values)
    sort(indexedVec.begin(), indexedVec.end());
    
    // Take the first x elements from the sorted vector
    for (int i = 0; i < x; ++i) {
        result.push_back(indexedVec[i].second);
    }
    
    return result;
}
void normalknn() {
  // Generate some sample data
  vector<float> xs = {6,8,3,1,5,7,9,7,4,4,6,8,3,1};
  vector<float> ys = {6,4,2,6,7,8,3,2,6,7,8,5,2,1};
  vector<string> labels = {"blue", "green", "red", "purple", "blue", "green", "red", "purple","blue", "green", "red", "purple", "red", "purple"};
  // And the test data
  float testX = 7;
  float testY = 4;
  // Get the distances from each training example
  vector<float> distances;
  for (int i = 0; i < xs.size(); i++) {
    distances.push_back(euclidean2d(testX, testY, xs[i], ys[i]));
  }
  // Choose K
  int k = ceil(sqrt(xs.size()));
  // Get the K smallest elements and their indexes
  vector<int> smallestIndexesVec = smallestIndexes(distances, k);
  // Get their labels in the training data for each smallest index
  vector<string> smallestLabels;
  for (int j = 0; j < k; j++) {
    smallestLabels.push_back(labels[smallestIndexesVec[j]]);
    cout << labels[smallestIndexesVec[j]] << endl;
  }
}

void optimisedknn() {
  // Generate some sample data
  vector<float> xs = {6,8,3,1,5,7,9,7,4,4,6,8,3,1};
  vector<float> ys = {6,4,2,6,7,8,3,2,6,7,8,5,2,1};
  vector<string> labels = {"blue", "green", "red", "purple", "blue", "green", "red", "purple","blue", "green", "red", "purple", "red", "purple"};
  // And the test data
  float testX = 7;
  float testY = 4;
  // Determine K
  int k = ceil(sqrt(xs.size()));
  // Determine the pre-elim max (P)
  int p = ceil(xs.size() / 2);
  // Get the P smallest with the basic distances
  vector<float> distancesFirstElim;
  for (int i = 0; i < xs.size(); i++) {
    distancesFirstElim.push_back(basic2d(testX, testY, xs[i], ys[i]));
  }
  // Get the K smallest elements and their indexes
  vector<int> smallestIndexesVecFirstElim = smallestIndexes(distancesFirstElim, p);
  // Get their labels and values in the training data for each smallest index
  vector<string> smallestLabels1;
  vector<float> smallestXs;
  vector<float> smallestYs;
  for (int j = 0; j < p; j++) {
    smallestLabels1.push_back(labels[smallestIndexesVecFirstElim[j]]);
    smallestXs.push_back(xs[smallestIndexesVecFirstElim[j]]);
    smallestYs.push_back(ys[smallestIndexesVecFirstElim[j]]);
  }
  // Now get the smallest K from those ones
  // Get the K distances
  vector<float> distances;
  for (int i = 0; i < smallestXs.size(); i++) {
    distances.push_back(euclidean2d(testX, testY, smallestXs[i], smallestYs[i]));
  }
  // Get the K smallest values and their indexes
  vector<int> smallestIndexesVec = smallestIndexes(distances, k);
  vector<string> smallestLabels;
  // Get their labels for each smallest index
  for (int j = 0; j < k; j++) {
    smallestLabels.push_back(labels[smallestIndexesVec[j]]);
    cout << smallestLabels1[smallestIndexesVec[j]] << endl;
  }
}

void timeNormal() {
  vector<int> values(10000);
 
    // Generate Random values
    auto f = []() -> int { return rand() % 10000; };
 
    // Fill up the vector
    generate(values.begin(), values.end(), f);
 
    // Get starting timepoint
    auto start = high_resolution_clock::now();
 
    // Call the function, here sort()
    normalknn();
 
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
 
    // Get duration. Substart timepoints to 
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
 
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
}

void timeOptimised() {
  vector<int> values(10000);
 
    // Generate Random values
    auto f = []() -> int { return rand() % 10000; };
 
    // Fill up the vector
    generate(values.begin(), values.end(), f);
 
    // Get starting timepoint
    auto start = high_resolution_clock::now();
 
    // Call the function, here sort()
    optimisedknn();
 
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
 
    // Get duration. Substart timepoints to 
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
 
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
}

int main() {
  timeNormal();
  timeOptimised();
  return 0;
}
