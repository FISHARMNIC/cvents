# keyvents 
A key press event library for C  
A simple demonstration is found in `main.c`

---

## Creating Events
Events are represented with functions  
### Single Keypress Functions
* Normal events do not return a value and take no parameters 
* `void trigger() {...}`
### Global Keypress Functions
* Global events do not return a value but take a character
	* The character is the key that was pressed
* `void trigger(char ch) {...}`

## Setting Up Events
### `KEY_INIT_ENTER()`
* Execute this before setting up your events
### `KEY_INIT_EXIT()`
* Execute this after setting up your events

### `TERM_MT()`
* Reccommended to be used at the end of a multithreaded keypress function

### `use_key(char key, void *function, <optional> thread)`
* Binds a keypress to a function
* The function must be a single keypress function
* `thread` specifies if you want the event to run on a seperate thread (optional)
	* Use `USE_MT` or `NO_MT`
* Example: `use_key('a', key_a_event)`

### `use_global( void *function)`
* Binds any keypress to a function
* The function must be a global keypress function
* `thread` specifies if you want the event to run on a seperate thread (optional)
	* Use `USE_MT` or `NO_MT`
* Example: `use_global(global_event)`
