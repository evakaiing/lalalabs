#include "functions.h"

int main() {
    RouteList list = {NULL};

    char* files[] = {"input.txt", "input2.txt", "input3.txt", "krivoy_test.txt"};
    int fileCount = sizeof(files) / sizeof(files[0]);

    return_code rc_of_processing = processFile(&list, fileCount, files);

    Route* route = list.head;
    while (route != NULL) {
        sortStops(route);
        route = route->next;
    }
    printRouteList(&list);


    char stop[MAX_LEN_COMMAND] = "stop";
    char way[MAX_LEN_COMMAND] = "way";
    char r[MAX_LEN_COMMAND] = "route";
    char stopTime[MAX_LEN_COMMAND] = "stopTime";
    char stay[MAX_LEN_COMMAND] = "stay";
    char exitProg[MAX_LEN_COMMAND] = "q";


    while (1) {
        printf("stop - вывести машину, которая проехала больше/меньше всего остановок\n");
        printf("way - вывести машину, которая проехала самый длинный/короткий путь\n");
        printf("route - вывести машину, у которой больше/меньше всего маршрутов\n");
        printf("stopTime - вывести машину с самой долгой/короткой остановкой\n");
        printf("stay - вывести машину c самым большим временем простоя\n");
        printf("q - завершить программу\n");
        char command[MAX_LEN_COMMAND];
        scanf("%s", command);

        if (!strcmp(command, stop)) {
            Route* longestRoute = findLongestRoute(&list);
            if (longestRoute != NULL) {
                printf("машина с наибольшим кол-вом остановок %s\n", longestRoute->vehicleNumber);
            } else {
                return INVALID_INPUT;
            }

            Route* shortestRoute = findShortestRoute(&list);
            if (shortestRoute != NULL) {
                printf("машина с наименьшим кол-вом остановок %s\n\n", shortestRoute->vehicleNumber);
            } else {
                return INVALID_INPUT;
            }
        } else if (!strcmp(command, way)) {
            Route* minWay = findShortestWay(&list);
            if (minWay != NULL) {
                printf("машина с кротчайшим путем: %s\n\n", minWay->vehicleNumber);
            } else {
                return INVALID_INPUT;
            }

            Route* maxWay = findLongestWay(&list);
            if (maxWay != NULL) {
                printf("машина с длинейшим путем: %s\n\n", maxWay->vehicleNumber);
            } else {
                return INVALID_INPUT;
            }
        } else if (!strcmp(command, r)) {
            Route* maxRoute = findMaxRoute(&list);
            if (maxRoute != NULL) {
                printf("машина которая проехала больше всего маршрутов %s\n\n", maxRoute->vehicleNumber);
            } else {
                return INVALID_INPUT;
            }

            Route* minRoute = findMinRoute(&list);
            if (minRoute != NULL) {
                printf("машина которая проехала меньше всего маршрутов%s\n\n", minRoute->vehicleNumber);
            } else {
                return INVALID_INPUT;
            }
        } else if (!strcmp(command, stopTime)) {
            Route* longestStopRoute = findRouteWithLongestStop(&list);
            if (longestStopRoute != NULL) {
                printf("машина с самой длинной остановкой: %s\n\n", longestStopRoute->vehicleNumber);
            } else {
                return INVALID_INPUT;
            }

            Route* shortestStopRoute = findRouteWithShortestStop(&list);
            if (shortestStopRoute != NULL) {
                printf("машина с самой короткой остановкой: %s\n\n", shortestStopRoute->vehicleNumber);
            } else {
                return INVALID_INPUT;
            }
        } else if (!strcmp(command, stay)) {
            Route* longestStopTime = findRouteWithLongestStopTime(&list);
            if (longestStopTime != NULL) {
                printf("машина с самым большим временем простоя: %s\n\n", longestStopTime->vehicleNumber);
            } else {
                return INVALID_INPUT;
            }
        } else if (!strcmp(command, exitProg)) {
            freeRouteList(&list);
            break;
        } else {
            printf("incorrect command\n\n");
            return INVALID_INPUT;
        }
    }
    return OK;
}