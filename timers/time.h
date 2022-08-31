#ifndef TIME_H
#define TIME_H
#include <stdlib.h>

typedef enum {
    TIMER_SINGLE_SHOT = 0,
    TIMER_PERIODIC
} t_timer;

typedef void (*time_handler)(size_t timer_id, void* user_data);

/**
 * Initialize the library once before using any other function. Called once even if using multiple timers.
 */
int initialize();

/**
 * Creates a timer and returns the id of the timer. Returned timer id would be used to stop the timer.
 * @param {unsigned int} interval - Timeout interval in milliseconds. 
 * @param {void*} handler - The callback function pointer. 
 * @param {t_timer} type - The time of timer (periodic or one shot).
 * @param {void*} user_data - User can set any data as a void pointer. Library will call with this data.
 *
 * @note
 *
 * If interval is 10, the timer will 
 * expire (call handler callback) after 10 milliseconds. In the case of a periodic timer, it will keep calling
 * the handler every 10 miliseconds.
 */
size_t start_timer(unsigned int interval, time_handler handler, t_timer type, void* user_data);

/**
 * Stops the particular timer buy the input timer id. Timer id is returned by start_timer()
 */
void stop_timer(size_t timer_id);

/**
 * Called when the timer library will no longer be required, stops and deletes all running timers.
 */
void finalize();
#endif
