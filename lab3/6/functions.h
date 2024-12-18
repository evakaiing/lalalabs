#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

#define EPS 0.00000001
#define MAX_LEN_COMMAND 15

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT,
    FILE_PATH_LENGTH_ERROR,
    FILE_OPENNING_ERROR,
    ACCSESS_ERROR
} return_code;



typedef struct Stop {
    float x;
    float y;
    char stopTime[20];
    char leaveTime[20];
    int isInitial;
    struct Stop* next;
} Stop;

typedef struct Route {
    char vehicleNumber[20];
    Stop* stops;             
    struct Route* next;
} Route;


typedef struct RouteList {
    Route* head;
} RouteList;

long convertToUnixTime(const char* datetime);
Stop* createStop(float x, float y, char* stopTime, char* leaveTime, int isInitial);
return_code strAddStr(char* str1, const char* str2);
return_code addStopToRoute(Route* route, Stop* stop);
Route* createRoute(char* vehicleNumber);
return_code addRouteToList(RouteList* list, Route* route);
return_code readFile(RouteList* list, const char* filename);
int compareTime(const char* time1, const char* time2);
return_code sortStops(Route* route);
float CalcWay(Stop* s1, Stop* s2);
Route* findMaxRoute(RouteList* list);
Route* findMinRoute(RouteList* list);
Route* findLongestRoute(RouteList* list);
Route* findShortestRoute(RouteList* list);
Route* findShortestWay(RouteList* list);
Route* findLongestWay(RouteList* list);
Route* findRouteWithLongestStop(RouteList* list);
Route* findRouteWithShortestStop(RouteList* list);
Route* findRouteWithLongestStopTime(RouteList* list);
return_code printRouteList(RouteList* r);
return_code freeRouteList(RouteList* list);
return_code processFile(RouteList* list, int count, char* files[]);

