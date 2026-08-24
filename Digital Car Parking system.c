#include <stdio.h>

#define MAX 5

int main() {
    int spots[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;
    int stack[MAX];
    int top = -1;

    int choice, car_id, spot_id;

    for (;;) {
        printf("\n====================================\n");
        printf("   PARKING LOT MANAGEMENT SYSTEM    \n");
        printf("====================================\n");
        printf("1. Park Car (Main Garage)\n");
        printf("2. Exit Car (Main Garage)\n");
        printf("3. Park Car (Valet Lane)\n");
        printf("4. Exit Car (Valet Lane)\n");
        printf("5. Search Car Location\n");
        printf("6. View Parking Lot Status\n");
        printf("7. Shut Down System\n");
        printf("Select option (1-7): ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter License Plate / Car ID: ");
            scanf("%d", &car_id);

            int empty_spot = -1;
            for (int i = 0; i < MAX; i++) {
                if (spots[i] == 0) {
                    empty_spot = i;
                    break;
                }
            }

            if (empty_spot != -1) {
                spots[empty_spot] = car_id;
                printf("SUCCESS: Car %d parked in Spot #%d.\n", car_id, empty_spot);
            } else {
                if (rear < MAX) {
                    queue[rear] = car_id;
                    rear++;
                    printf("GARAGE FULL: Car %d added to entrance waiting line.\n", car_id);
                } else {
                    printf("NOTICE: Both garage and waiting line are full!\n");
                }
            }
        }
        else if (choice == 2) {
            printf("Enter Spot Number to vacate (0 to %d): ", MAX - 1);
            scanf("%d", &spot_id);

            if (spot_id >= 0 && spot_id < MAX) {
                if (spots[spot_id] != 0) {
                    printf("Car %d has exited Spot #%d.\n", spots[spot_id], spot_id);
                    spots[spot_id] = 0;

                    if (front < rear) {
                        int next_car = queue[front];
                        front++;
                        spots[spot_id] = next_car;
                        printf("ENTRY GATE: Waiting car %d assigned to newly freed Spot #%d.\n",
next_car, spot_id);
                    }
                } else {
                    printf("Spot #%d is already empty.\n", spot_id);
                }
            } else {
                printf("Invalid spot number!\n");
            }
        }
        else if (choice == 3) {
            printf("Enter License Plate / Car ID for Valet: ");
            scanf("%d", &car_id);

            if (top < MAX - 1) {
                top++;
                stack[top] = car_id;
                printf("Valet: Car %d parked in valet lane.\n", car_id);
            } else {
                printf("Valet lane is full!\n");
            }
        }
        else if (choice == 4) {
            if (top >= 0) {
                printf("Valet: Car %d removed from valet lane.\n", stack[top]);
                top--;
            } else {
                printf("Valet lane is currently empty.\n");
            }
        }
        else if (choice == 5) {
            printf("Enter Car ID to locate: ");
            scanf("%d", &car_id);

            int active_ids[MAX];
            int active_spots[MAX];
            int count = 0;

            for (int i = 0; i < MAX; i++) {
                if (spots[i] != 0) {
                    active_ids[count] = spots[i];
                    active_spots[count] = i;
                    count++;
                }
            }

            if (count == 0) {
                printf("No cars currently parked in main garage.\n");
            } else {
                for (int i = 0; i < count - 1; i++) {
                    for (int j = 0; j < count - i - 1; j++) {
                        if (active_ids[j] > active_ids[j + 1]) {
                            int temp_id = active_ids[j];
                            active_ids[j] = active_ids[j + 1];
                            active_ids[j + 1] = temp_id;

                            int temp_spot = active_spots[j];
                            active_spots[j] = active_spots[j + 1];
                            active_spots[j + 1] = temp_spot;
                        }
                    }
                }

                int low = 0, high = count - 1, found_spot = -1;
                while (low <= high) {
                    int mid = (low + high) / 2;
                    if (active_ids[mid] == car_id) {
                        found_spot = active_spots[mid];
                        break;
                    }
                    if (active_ids[mid] < car_id) {
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }

                if (found_spot != -1) {
                    printf("SEARCH RESULT: Car %d is located at Spot #%d.\n", car_id, found_spot);
                } else {
                    printf("SEARCH RESULT: Car %d was not found in main garage.\n", car_id);
                }
            }
        }
        else if (choice == 6) {
            printf("\n--- MAIN GARAGE SPOTS ---\n");
            for (int i = 0; i < MAX; i++) {
                if (spots[i] == 0) {
                    printf("Spot #%d: [ Available ]\n", i);
                } else {
                    printf("Spot #%d: Car %d\n", i, spots[i]);
                }
            }

            printf("\n--- ENTRANCE WAITING LINE ---\n");
            if (front == rear) {
                printf("No cars waiting.\n");
            } else {
                for (int i = front; i < rear; i++) {
                    printf("Car %d  ", queue[i]);
                }
                printf("\n");
            }

            printf("\n--- VALET DRIVEWAY LANE ---\n");
            if (top == -1) {
                printf("Valet lane empty.\n");
            } else {
                for (int i = top; i >= 0; i--) {
                    printf("Car %d  ", stack[i]);
                }
                printf("\n");
            }
        }
        else if (choice == 7) {
            printf("Shutting down parking system. Goodbye!\n");
            break;
}
else {
printf("Invalid selection! Please enter a number between 1 and 7.\n");
}
}
return 0;
}
