# cvents 
A key press event library for C  
A simple demonstration is found in `main.c`

---

## Setting Up Events
Events are represented with functions  
### Single Keypress Functions
* Normal events do not return a value and take no parameters 
* `void trigger() {...}`
### Global Keypress Functions
* Global events do not return a value but take a character
	* The character is the key that was pressed
* `void trigger(char ch) {...}`

## Creating Events
### `KEY_INIT_ENTER()`
* Execute this before setting up your events
### `KEY_INIT_EXIT()`
* Execute this after setting up your events

### `use_key(char key, void *function)`
* Binds a keypress to a function
* The function must be a single keypress function
* Example: `use_key('a', key_a_event)`

### `use_global( void *function)`
* Binds any keypress to a function
* The function must be a global keypress function
* Example: `use_global(global_event)`
