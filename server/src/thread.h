#include <thread>

#ifndef __THREAD_H__
#define __THREAD_H__

class Thread {
    private:
        std::thread thread;
 
    public:
        Thread();
		
		//Inicia el funcionamiento del nuevo hilo
        void start();
		
		// Termina el funcionamiento del hilo, liberando sus recursos
        void join();
		
		// Accion a ejecutar en el hilo
        virtual void run() = 0;
        
        // Frenar el hilo
        virtual void stop() = 0;
        
        // Saber si el hilo ha finalizado su procesamiento o no.
        //virtual bool is_dead() const = 0 ;
        
        virtual ~Thread() noexcept;

        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        Thread(Thread&& other);

        Thread& operator=(Thread&& other);
};

#endif
