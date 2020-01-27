/**
@brief Module gerant le chronometre (tiree du site LAZYFOO => http://lazyfoo.net)
@file Timer.h
*/
#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>


//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks; /*!< Temps en secondes au moment ou le chronometre est lance */

    //The ticks stored when the timer was paused
    int pausedTicks; /*!< Nombre de secondes passees au moment ou le chronometre est mit en pause/arrete */

    //The timer status
    bool paused; /*!< Indique si le chronometre est en pause */
    bool started; /*!< Indique si le chronometre est lance */

    public:
    //Initializes variables
    /**
    @brief constructeur par defaut
    */
    Timer();

    //The various clock actions
    /**
    @brief lance le chronometre
    */
    void start();

    /**
    @brief arrete le chronometre
    */
    void stop();

    /**
    @brief met le chronometre en pause
    */
    void pause();

    /**
    @brief relance le chronometre lorsqu'il etait en pause
    */
    void unpause();

    //Gets the timer's time
    /**
    @brief permet d'obtenir le nombre de ticks deroulees depuis le lancement du chronometre
    Si il est en pause, retourne le nombre de ticks entre le lancement et le moment ou il a ete mis sur pause
    Si il est sur stop, retourne 0
    @return entier
    */
    int get_ticks();

    //Checks the status of the timer
    /**
    @brief accesseur de started du chronometre
    @return booleen
    */
    bool is_started();

    /**
    @brief accesseur de paused du chronometre
    @return booleen
    */
    bool is_paused();

    //Temps écoulé en secondes
    /**
    @brief permet d'obtenir le nombre de secondes deroulees depuis le lancement du chronometre
    @return entier
    */
    int get_s();
};

#endif //TIMER_H
