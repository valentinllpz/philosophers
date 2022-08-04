# Philosophers

![demo](demo.gif)

This [42](https://42.fr/en/homepage/) project is an introduction to [multithreading](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture)) and processes, and how to work on a shared memory space in C.
The goal here is to use [mutual exclusion](https://en.wikipedia.org/wiki/Mutual_exclusion) and [semaphores](https://en.wikipedia.org/wiki/Semaphore_(programming)) to avoid concurrency issues.

### The simulation 

Philosophers are sitting at a round table with a big spaghetti plate in the middle and **one fork** for each of them. They are either **eating**, **thinking** or **sleeping**. They need **two forks** to eat, so they need to borrow one from their neighboor. Once done eating, they drop the forks to start sleeping. A philosopher is thinking whenever he is not eating or sleeping.
Communicating between them is forbidden, and they should avoid dying at any cost if they are not suppposed to.

## 🧭 Usage

1. Clone this repo and access to the `philo` folder with `cd`
2. Run `make` to build the image
3. Use `./philo_one` to launch it. Arguments should be (in this order) a `number_of_philosophers` `time_to_die` `time_to_eat` `time_to_sleep` and optionally `number_of_times_each_philosopher_must_eat`.

Example: `./philo_one 3 800 200 500 10`


## 📚 Ressources

- [C Mutex examples](https://www.thegeekstuff.com/2012/05/c-mutex-examples/)
- [How to create and join threads in C (video)](https://youtu.be/uA8X5zNOGw8)
- [What is a mutex in C? (video)](https://youtu.be/oq29KUy29iQ)
