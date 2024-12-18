#include "functions.h"

long convertToUnixTime(const char* datetime) {
    struct tm tm_time = {0};
    int day, month, year, hour, minute, second;

    if (sscanf(datetime, "%d.%d.%d %d:%d:%d", &day, &month, &year, &hour, &minute, &second) != 6) {
        return INVALID_INPUT;
    }

    tm_time.tm_mday = day;
    tm_time.tm_mon = month - 1;
    tm_time.tm_year = year - 1900;
    tm_time.tm_hour = hour;
    tm_time.tm_min = minute;
    tm_time.tm_sec = second;

    return mktime(&tm_time);
}

Stop* createStop(float x, float y, char* stopTime, char* leaveTime, int isInitial) {
    Stop* newStop = (Stop*)malloc(sizeof(Stop));
    strcpy(newStop->stopTime, stopTime);
    strcpy(newStop->leaveTime, leaveTime);
    newStop->x = x;
    newStop->y = y;
    newStop->isInitial = isInitial;
    newStop->next = NULL;
    return newStop;
}

return_code strAddStr(char* str1, const char* str2) {
    while (*str1 != '\0') {
        str1++;
    }
    *str1++ = ' ';
    
    while (*str2 != '\0') {
        *str1++ = *str2++;
    }
    
    *str1 = '\0';

    return OK;
}

return_code addStopToRoute(Route* route, Stop* stop) {
    if (route->stops == NULL) {
        route->stops = stop;
    } else {
        Stop* temp = route->stops;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = stop;
    }
    return OK;
}

Route* createRoute(char* vehicleNumber) {
    Route* newRoute = (Route*)malloc(sizeof(Route));
    strcpy(newRoute->vehicleNumber, vehicleNumber);
    newRoute->stops = NULL;
    newRoute->next = NULL;
    return newRoute;
}


return_code addRouteToList(RouteList* list, Route* route) {
    if (list->head == NULL) {
        list->head = route;
    } else {
        Route* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = route;
    }
    return OK;
}


return_code readFile(RouteList* list, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("couldnt open file %s\n", filename);
        return FILE_OPENNING_ERROR;
    }

    char vehicleNumber[20];
    char stopTime[20], leaveTime[20], time1[10], time2[10];
    int isInitial;
    float x, y;

    while (fscanf(file, "%s %f %f %s %s %s %s %d", vehicleNumber, &x, &y, stopTime, time1, leaveTime, time2, &isInitial) != EOF) {
        strAddStr(stopTime, time1);
        strAddStr(leaveTime, time2);
        Route* route = list->head;
        while (route != NULL && strcmp(route->vehicleNumber, vehicleNumber) != 0) {
            route = route->next;
        }

        long stopTimeInUnix = convertToUnixTime(stopTime);
        long leaveTimeInUnix = convertToUnixTime(leaveTime);

        if (stopTimeInUnix > leaveTimeInUnix) {
            printf("for vechile number %s stop time > leave time\n", vehicleNumber);
            return INVALID_INPUT;
        }

        if (route == NULL) {
            route = createRoute(vehicleNumber);
            addRouteToList(list, route);
        }

        Stop* stop = createStop(x, y, stopTime, leaveTime, isInitial);
        addStopToRoute(route, stop);
    }

    fclose(file);
}


int compareTime(const char* time1, const char* time2) {
    return strcmp(time1, time2);
}

return_code sortStops(Route* route) {
    if (route->stops == NULL) return DEREFERENCING_NULL_POINTER_ATTEMPT;

    Stop* sorted = NULL;

    Stop* current = route->stops;
    while (current != NULL) {
        Stop* next = current->next;

        if (sorted == NULL || compareTime(current->stopTime, sorted->stopTime) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            Stop* temp = sorted;
            while (temp->next != NULL && compareTime(temp->next->stopTime, current->stopTime) < 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
        
    }

    route->stops = sorted;
    return OK;
}

float CalcWay(Stop* s1, Stop* s2) {
    float x1 = s1->x;
    float y1 = s1->y;
    float x2 = s2->x;
    float y2 = s2->y;
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

}

Route* findMaxRoute(RouteList* list) {
    Route* max = NULL;
    int maxStops = 0;

    Route* route = list->head;
    while (route != NULL) {
        int startCount = 0;
        Stop* stop = route->stops;
        while (stop != NULL) {
            if (stop->isInitial == 1) {
                startCount++;
            }
            stop = stop->next;
        }

        if (startCount > maxStops) {
            maxStops = startCount;
            max = route;
        }

        route = route->next;
    }

    return max;
}

Route* findMinRoute(RouteList* list) {
    Route* max = NULL;
    int minStops = INT_MAX;

    Route* route = list->head;
    while (route != NULL) {
        int startCount = 0;
        Stop* stop = route->stops;
        while (stop != NULL) {
            if (stop->isInitial == 1) {
                startCount++;
            }
            stop = stop->next;
        }

        if (startCount < minStops) {
            minStops = startCount;
            max = route;
        }

        route = route->next;
    }

    return max;
}

Route* findLongestRoute(RouteList* list) {
    Route* longest = NULL;
    int maxStops = 0;

    Route* route = list->head;
    while (route != NULL) {
        int stopCount = 0;
        Stop* stop = route->stops;
        while (stop != NULL) {
            stopCount++;
            stop = stop->next;
        }

        if (stopCount > maxStops) {
            maxStops = stopCount;
            longest = route;
        }

        route = route->next;
    }

    return longest;
}

Route* findShortestRoute(RouteList* list) {
    Route* shortest = NULL;
    int minStops = INT_MAX;

    Route* route = list->head;
    while (route != NULL) {
        int stopCount = 0;
        Stop* stop = route->stops;
        while (stop != NULL) {
            stopCount++;
            stop = stop->next;
        }

        if (stopCount < minStops) {
            minStops = stopCount;
            shortest = route;
        }

        route = route->next;
    }

    return shortest;
}

Route* findShortestWay(RouteList* list) {
    Route* shortest = NULL;
    float minWay = INT_MAX;

    Route* route = list->head;
    while (route != NULL) {
        float way = 0;
        Stop* stop1 = route->stops;
        if (stop1 != NULL && stop1->next != NULL) {
            Stop* stop2 = stop1->next;

            while (stop1 != NULL && stop2 != NULL) {
                way += CalcWay(stop1, stop2);
                stop1 = stop2;
                stop2 = stop2->next;
            }
        }
        if ((way - minWay) < EPS) {
            minWay = way;
            shortest = route;
        }
        route = route->next;
    }

    return shortest;
}


Route* findLongestWay(RouteList* list) {
    Route* longest = NULL;
    float maxWay = -1;

    Route* route = list->head;
    while (route != NULL) {
        float way = 0;
        Stop* stop1 = route->stops;
        if (stop1 != NULL && stop1->next != NULL) {
            Stop* stop2 = stop1->next;

            while (stop2 != NULL) { 
                way += CalcWay(stop1, stop2);
                stop1 = stop2;
                stop2 = stop2->next;
            }
        }
        if ((way - maxWay) >EPS) { 
            maxWay = way;
            longest = route;
        }
        route = route->next;
    }

    return longest;
}

Route* findRouteWithLongestStop(RouteList* list) {
    Route* longestStopRoute = NULL;
    float maxStopDuration = -1;

    Route* route = list->head;
    while (route != NULL) {
        Stop* stop = route->stops;
        while (stop != NULL) {
            long stopTime = convertToUnixTime(stop->stopTime);
            long leaveTime = convertToUnixTime(stop->leaveTime);
            float duration = leaveTime - stopTime;
            if ((duration - maxStopDuration) > EPS) {
                maxStopDuration = duration;
                longestStopRoute = route;
            }

            stop = stop->next;
        }
        route = route->next;
    }

    return longestStopRoute;
}

Route* findRouteWithShortestStop(RouteList* list) {
    Route* shortestStopRoute = NULL;
    float minStopDuration = INT_MAX;

    Route* route = list->head;
    while (route != NULL) {
        Stop* stop = route->stops;
        while (stop != NULL) {
            long stopTime = convertToUnixTime(stop->stopTime);
            long leaveTime = convertToUnixTime(stop->leaveTime);
            if (stopTime == -1 || leaveTime == -1) {
                stop = stop->next;
                continue;
            }

            float duration = (float)(leaveTime - stopTime);
            if ((duration - minStopDuration) < EPS) {
                minStopDuration = duration;
                shortestStopRoute = route;
            }

            stop = stop->next;
        }
        route = route->next;
    }

    return shortestStopRoute;
}

Route* findRouteWithLongestStopTime(RouteList* list) {
    Route* longestStopRoute = NULL;
    float maxStopDuration = -1;

    Route* route = list->head;
    while (route != NULL) {
        Stop* stop = route->stops;
        float sumStop = 0.0;
        
        while (stop != NULL) {
            long stopTime = convertToUnixTime(stop->stopTime);
            long leaveTime = convertToUnixTime(stop->leaveTime);
            
            if (stopTime == -1 || leaveTime == -1) {
                printf("err\n");
                stop = stop->next;
                continue;
            }
            
            float duration = (float)(leaveTime - stopTime);
            sumStop += duration;

            stop = stop->next;
        }

        if (sumStop > maxStopDuration) {
            maxStopDuration = sumStop; 
            longestStopRoute = route;
        }
        route = route->next;
    }

    return longestStopRoute;
}


return_code printRouteList(RouteList* r) {
    Route* currentRoute = r->head;
    while (currentRoute != NULL) {
        char* vehicle = currentRoute->vehicleNumber;
        printf("number %s\n", vehicle);
        
        Stop* stop = currentRoute->stops;
        while (stop != NULL) {
            printf("Х:%.2f Y:%.2f stop time: %s departure time: %s mark: %d\n", stop->x, stop->y, stop->stopTime, stop->leaveTime, stop->isInitial);
            stop = stop->next;
        }
        
        currentRoute = currentRoute->next;
    }
    
    return OK;
}

return_code freeRouteList(RouteList* list) {
    Route* currentRoute = list->head;
    while (currentRoute != NULL) {
        Route* tempRoute = currentRoute;
        currentRoute = currentRoute->next;

        Stop* currentStop = tempRoute->stops;
        while (currentStop != NULL) {
            Stop* tempStop = currentStop;
            currentStop = currentStop->next;
            free(tempStop); 
        }

        free(tempRoute);
    }
    
    list->head = NULL;
    return OK;
}

return_code processFile(RouteList* list, int count, char* files[]) {
    for (int i = 0; i < count; i++) {
        return_code rc = readFile(list, files[i]);
        if (rc != OK) {
            return rc;
        }
    }
    return OK;
}
