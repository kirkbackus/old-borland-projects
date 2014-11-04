#ifndef __SDL_TIMER_H
#define __SDL_TIMER_H

class Timer
{
    private:

    int startTicks;
    int pausedTicks;

    bool paused;
    bool started;

    public:

    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();

    bool is_started();
    bool is_paused();
};

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    started = true;
    paused = false;
    startTicks = GetTickCount();
}

void Timer::stop()
{
    started = false;
    paused = false;
}

void Timer::pause()
{
    if(started && !paused)
    {
        paused = true;
        pausedTicks = GetTickCount() - startTicks;
    }
}

void Timer::unpause()
{
    if(paused) {
        paused = false;
        startTicks = GetTickCount() - pausedTicks;
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    if(started) {
        if(paused) return pausedTicks;
        else return GetTickCount() - startTicks;
    }
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

#endif
