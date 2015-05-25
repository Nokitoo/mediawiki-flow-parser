Mediawiki Flow Parser
=====================

Convert a Mediawiki Flow to a terminal flow. (Readable by bots or humans)
API_PATH is the directory path of API.

Installation instructions
-------------------------

1. Install the cURL library:
```shell
    $ cd API_PATH/curl
    $ ./configure
    $ make
    $ sudo make install
```
2. Install the jansson library:
```shell
    $ cd API_PATH/jansson
    $ ./configure
    $ make
    $ sudo make install
```
3. Start the API with the url of flow as parameter:
```shell
    $ cd API_PATH
    $ make
    $ ./flow_parser "http://url_of_flow/"
```
4. Use of API:
```shell
   $ Type "exit" or press ^D to exit the API
```
Other
-----

The mediawiki flow page: http://www.mediawiki.org/wiki/Flow
This project is under MIT License see `LICENSE` file for more details.
