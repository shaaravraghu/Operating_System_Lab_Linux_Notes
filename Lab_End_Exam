// BANKER'S ALGORITHM WITH SAFE STATE IMPLEMENTATION

#include <iostream>
using namespace std;

bool check_safe_state(int resource_type, int number_of_process,
                      int need[number_of_process][resource_type],
                      int available[resource_type],
                      int allocation[number_of_process][resource_type]
                      bool finished[number_of_process]) {
  for (int i = 0; i < number_of_process; i++) {
    for (int j = 0; j < resource_type; j++) {
      if (need[i][j] > available[j] && !finished[i]) {
        return false;
      }
      available[j] += allocation[i][j];
      finished[i] = true;
    }
  }
  return true;
}

int main() {
  int resource_type;
  cin >> resource_type;

  int number_of_process;
  cin >> number_of_process;

  int available[resource_type];
  int max[number_of_process][resource_type];
  int allocation[number_of_process][resource_type];
  int need[number_of_process][resource_type];
  int request[number_of_process][resource_type];
  bool finished[number_of_process];

  for (int i = 0; i < resource_type; i++) {
    cin >> available[i];
  }

  for (int i = 0; i < number_of_process; i++) {
    for (int j = 0; j < resource_type; j++) {
      cin >> max[i][j];
    }
  }

  for (int i = 0; i < number_of_process; i++) {
    for (int j = 0; j < resource_type; j++) {
      cin >> allocation[i][j];
    }
  }

  for (int i = 0; i < number_of_process; i++) {
    for (int j = 0; j < resource_type; j++) {
      need[i][j] = max[i][j] - allocation[i][j];
    }
  }

  for (int i = 0; i < number_of_process; i++) {
    cin >> request[i];
  }

  for (int i = 0; i < number_of_process; i++) {
    finished[i] = false;
  }

  for (int i = 0; i < number_of_process; i++) {
    if (check_safe_state(resource_type, number_of_process, need, available, finished)) {
      for (int j = 0; j < resource_type; j++) {
        // starting banker's algorithm
        if ((request[j] < need[i][j]) && (request[j] < available[j]) && !finished[i]) {
          available[j] -= request[j];
          allocation[i][j] += request[j];
          need[i][j] -= request[j];
        }
      }
    }
    cout << endl;
  }

  return 0;
}
